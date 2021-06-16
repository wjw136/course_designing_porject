#include <iostream>
#include <windows.h>
#include <string.h>
#include <queue>
#include <math.h>
#include "stdio.h"
#include <fstream>
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
void filter(char *s, int len)
{
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
                    cout << "字符串(单引号) error!" << endl;
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
                    cout << "括号 error!" << endl;
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
                    cout << "[] error!" << endl;
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
    else if(ch == '<')
    {//可能是< <= <<
        ++p;
        if(project[p] == '=')//<=
        {
            syn = 54;
        }
        if(project[p] == '>')//<<
        {
            syn = 55;
        }
        else//<
        {
            --p;
            syn = 53;
        }
        ++p;
        return;
    }
        else if(ch == '>')
    {//可能是> >= >>
        ++p;
        if(project[p] == '=')//>=
        {
            syn = 58;
        }
        else//>
        {
            --p;
            syn = 57;
        }
        ++p;
        return;
    }
    else if(ch == ':')
    {//可能是: :=
        ++p;
        if(project[p] == '=')//>=
        {
            syn = 51;
        }
        else//>
        {
            --p;
            syn = 50;
        }
        ++p;
        return;
    }
    else if(ch == '.')
    {//可能是. ..
        ++p;
        if(project[p] == '.')//>=
        {
            syn = 47;
        }
        else//>
        {
            --p;
            syn = 47;
        }
        ++p;
        return;
    }
    else if(ch == '\0')//文件结束
    {
        syn = 0;
    }
    else if(ch=='\''){
        token[cnount++]=
        while(ch=='\''){
            token[count++]
        }
    }
    else {
    switch (project[p])
        {
        case '(':
                syn=39;
                break;
        case ')':
                syn=40;
                break;
        case '*':
                syn=41;
                break;
        case '+':
                syn=43;
                break;
        case ',':
                syn=44;
                break;
        case '-':
                syn=45;
                break;
        case '/':
                syn=48;
                break;
        case ';':
                syn=52;
                break;
        case '=':
                syn=56;
                break;
        case '[':
                syn=59;
                break;
        case ']':
                syn=60;
                break;
        //无法匹配
        default:
            cout<<" not proper symbol"<<endl;
            exit(0);    
        
        }
        
    }
}
int main()
{
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
            p=0;
            int syn = -1;
            char token[20] = {};
            //cout<<project<<endl;
            while(true){
                scanner(syn,project,token,p);
                cout<<syn<<":"<<token<<endl;
                if(syn==0) break;
            }
        }
        cout << "the program name: ";
    }
    return 0;
}
