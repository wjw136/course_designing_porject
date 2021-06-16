#include <iostream>
#include <windows.h>
#include <string.h>
#include <queue>
#include <math.h>
#include "stdio.h"
#include <fstream>
#include <map>
#define ll long long
#define inf 100000
#define clr1(a) memset(a, -1, sizeof(a))
#define clr(a) memset(a, 0, sizeof(a))
using namespace std;

//reserved word
static char reserveword[35][20] = {
    "and", "array", "begin", "bool", "call", "case",
    "char", "constant", "dim", "do", "else", "end",
    "false", "for", "if", "input", "integer", "not",
    "of", "or", "output", "procedure", "program", "read",
    "real", "repeat", "set", "stop", "then", "to", "true",
    "until", "var", "while", "write"};
//operator
static char myoperator[22][10] = {
    "(", ")", "*", "*/", "+", ",", "-",
    "..", "/", "/*", ":", ":=", ";", "<",
    "<=", "<>", "=", ">", ">=", "[", "]"};
bool isDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    else
    {
        return false;
    }
}
bool isLetter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch <= 'Z' && ch >= 'A') || ch == '_')
        return true;
    else
    {
        return false;
    }
}
int isReserve(char *s)
{
    for (int i = 0; i < 35; ++i)
    {
        if (strcmp(reserveword[i], s) == 0)
        {
            return i + 1;
        }
    }
    return -1;
}
//filter
int row = 1;
void filter(char *s, int len)
{
    row = 1;
    char tmp[10000];
    int p = 0;
    for (int i = 0; i < len; ++i)
    {
        //注释
        if (s[i] == '/' && s[i + 1] == '*')
        {
            i += 2;
            while (s[i] != '*' || s[i + 1] != '/')
            {
                if (s[i] == '\0' || s[i] == '\n')
                {
                    cout << "Annotation error!" << endl;
                    exit(0);
                }
                i++;
            }
            i += 2;
        }
        //检查字符串
        if (s[i] == '\'')
        {
            tmp[p++] = s[i++];
            while (s[i] != '\'')
            {
                if (s[i] == '\n' || s[i] == '\0')
                {
                    printf("字符串(单引号) error!, row: %d\n", row);
                    exit(0);
                }
                tmp[p++] = s[i++];
            }
        }
        //检查括号
        if (s[i] == '(')
        {
            tmp[p++] = s[i++];
            while (s[i] != ')')
            {
                if (s[i] == '\0')
                {
                    printf("括号 error!, row: %d\n", row);
                    exit(0);
                }
                tmp[p++] = s[i++];
            }
        }
        //检查[]
        if (s[i] == '[')
        {
            tmp[p++] = s[i++];
            while (s[i] != ']')
            {
                if (s[i] == '\0')
                {
                    printf("[] error!, row: %d\n", row);
                    exit(0);
                }
                tmp[p++] = s[i++];
            }
        }
        //去除换行等
        if (s[i] != '\n' && s[i] != '\t' && s[i] != '\v' && s[i] != '\r')
        {
            tmp[p] = s[i];
            p++;
            //i++;
        }
        else
        {
            if (s[i] == '\n')
                row++;
            tmp[p++] = ' ';
        }
    }
    tmp[p] = '\0';
    strcpy(s, tmp);
}
//scanner
void scanner(int &syn, char *project, char *token, int &p)
{
    int count = 0;
    char ch;
    ch = project[p];
    while (ch == ' ')
    { //white space
        ++p;
        ch = project[p];
    }
    for (int i = 0; i < 20; i++)
    {
        token[i] = '\0';
    }
    if (isLetter(project[p]))
    {
        token[count++] = project[p++];
        //cout<<isLetter(project[p])<<endl;
        while (isLetter(project[p]) || isDigit(project[p]))
        {
            //cout<<project[p]<<endl;
            token[count++] = project[p++];
        }
        token[count] = '\0';
        syn = isReserve(token);
        if (syn == -1)
        {
            syn = 36;
        }
        return;
    }
    else if (isDigit(project[p]))
    {
        token[count++] = project[p++];
        while (isDigit(project[p]))
        {
            token[count++] = project[p++];
        }
        if (isLetter(project[p]))
        {
            cout << "symbol begin with digit wrong!" << endl;
            exit(0);
        }
        token[count] = '\0';
        syn = 37;
        return;
    }
    else if (ch == '<')
    { //可能是< <= <<
        token[count++] = project[p];
        ++p;
        if (project[p] == '=') //<=
        {
            token[count++] = project[p];
            syn = 54;
        }
        if (project[p] == '>') //<<
        {
            token[count++] = project[p];
            syn = 55;
        }
        else //<
        {
            --p;
            syn = 53;
        }
        ++p;
        return;
    }
    else if (ch == '>')
    { //可能是> >= >>
        token[count++] = project[p];
        ++p;
        if (project[p] == '=') //>=
        {
            token[count++] = project[p];
            syn = 58;
        }
        else //>
        {
            --p;
            syn = 57;
        }
        ++p;
        return;
    }
    else if (ch == ':')
    { //可能是: :=
        token[count++] = project[p];
        ++p;
        if (project[p] == '=') //>=
        {
            token[count++] = project[p];
            syn = 51;
        }
        else //>
        {
            --p;
            syn = 50;
        }
        ++p;
        return;
    }
    else if (ch == '.')
    { //可能是. ..

        token[count++] = project[p];
        ++p;
        if (project[p] == '.') //>=
        {
            syn = 47;
            token[count++] = project[p];
        }
        else //>
        {
            --p;
            syn = 46;
        }
        ++p;
        return;
    }
    else if (ch == '\0') //文件结束
    {
        syn = 0;
    }
    else if (ch == '\'')
    {
        token[count++] = project[p++];
        //cout<<project[p];
        while (project[p] != '\'')
        {
            token[count++] = project[p++]; //
        }
        token[count++] = project[p++];
        syn = 38;
    }
    else
    {
        switch (project[p])
        {
        case '(':
            syn = 39;
            break;
        case ')':
            syn = 40;
            break;
        case '*':
            syn = 41;
            break;
        case '+':
            syn = 43;
            break;
        case ',':
            syn = 44;
            break;
        case '-':
            syn = 45;
            break;
        case '/':
            syn = 48;
            break;
        case ';':
            syn = 52;
            break;
        case '=':
            syn = 56;
            break;
        case '[':
            syn = 59;
            break;
        case ']':
            syn = 60;
            break;
        //无法匹配
        default:
            //非法字符,提示并自动跳过
            syn = -2;
        }
        token[count++] = project[p++];
    }
}
map<string,int> mp;
int main()
{
    mp.clear();
    //cout << "我i";
    cout << "the program name: ";
    string s; //cin>>s;
    while (cin >> s)
    {
        ifstream fin(s + ".txt");
        if (!fin)
        {
            cout << "The program not exists!" << endl;
        }
        else
        {
            char project[10000];
            int p = 0;
            //fin.get(project[p++]);
            while (fin.peek() != EOF)
            {
                fin.get(project[p++]);
                //cout<<project[p-1]<<endl;
            }
            //cout << project << endl;
            project[p++] = '\0';
            fin.close();
            //cout << project << endl;
            filter(project, p - 1);
            //cout << project << endl;
            p = 0;
            int syn = -1;
            char token[20] = {};
            //cout<<project<<endl;
            int cnt = 0;
            int cnt1 = 0;
            while (true)
            {
                scanner(syn, project, token, p);
                //cout<<syn<<endl;
                if (syn == 0)
                    break;
                else if (syn == -2)
                {
                    printf("(非法字符, %s)\t", token);
                    cnt1++;
                }
                else if (syn == 36 || syn == 37)
                {   
                    cout<<mp.count()<endl;
                    int tmp=cnt;
                    if(mp.count(token)){
                        cnt=mp[token];
                        tmp=cnt;
                    }else{
                        cnt++;
                        tmp=cnt;
                        mp[token]=cnt;
                    }
                    printf("(%d, %d)\t", syn, tmp);
                    cnt1++;
                }
                else
                {   
                    //cout<<setw(10)
                    printf("(%d, ~)\t", syn);
                    cnt1++;
                }
                if (cnt1 % 5 == 0)
                {
                    cout << endl;
                }
            }
        }
        cout << endl << "the program name: ";
    }
    return 0;
}
