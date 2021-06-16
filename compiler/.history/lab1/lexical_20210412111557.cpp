#include <iostream>
#include <windows.h>
#include <string.h>
#include <queue>
#include <math.h>
#include "stdio.h" 
#define ll long long
#define inf 100000
#define clr1(a) memset(a,-1,sizeof(a))
# define clr(a) memset(a, 0, sizeof(a))
using namespace std;

//reserved word
static char reserveword[35][20]={
    "and","array","begin","bool","call","case",
    "char","constant","dim","do","else","end",
    "false","for","if","input","integer","not",
    "of","or","output","procedure","program","read",
    "real","repeat","set","stop","then","to","true",
    "until","var","while","write"
};
//operator
static char myoperator[22][10]={
    "(",")","*","*/","+",",","-",
    "..","/","/*",":",":=",";","<",
    "<=","<>","=",">",">=","[","]"
};
bool isDigit(char ch){
    if(ch>='0'&&ch<='9')
    return true;
    else
    {
        return false;
    }
    
}
bool isLetter(char ch){
    if((ch>='a'&&ch<='z')||(ch<='Z'&&ch>='A')||ch=='_')
    return true;
    else
    {
        return false;
    }
    
}
int isReserve(char *s){
    for(int i=0;i<35;++i){
        if(strcmp(reserveword[i],s)==0){
            return i+1;
        }
    }
    return -1;
}
//filter
void filter(char *s,int len){
    char tmp[10000];
    int p=0;
    for(int i=0;i<len;++i){
        //注释
        if(s[i]=='/'&&s[i+1]=='*'){
            i+=2;
            while(s[i]!='*'||s[i+1]!='/'){
                if(s[i]=='\0'&&s[i]=='\n'){
                    cout<<"Annotation error!";
                    exit(0);
                }
                i++;
            }
            i+=2;
        }
        //去除换行等
        if(s[i]!='\n'&&s[i]!='\t'&&s[i]!='\v'&&s[i]!='r'){
            tmp[p]=s[i];
            p++;
            //i++;
        }   
    }
    tmp[p]='\0';
    strcpy(s,tmp);
}
//scanner
void scannner(int &syn,char *project,char *token,int &p){
    int count=0;
    char ch;
    ch=project[p];
    while(cjh==" "){//white space
        ++p;
        ch=project[p];
    }
    for(int i=0;i<20;i++){
        token[i]='\0';
    }
    if(isLetter(project[p])){
        token[count++]=project[p++];
        while(isLetter(project[p]||isDigit(project[p]))){
            token[count++]=project[p++];
        }
        token[count]
    }
}
int main(){
   
    // string s="sss";
    // cout<<(s[1]=='\0');
   //system("pause");
   return 0;
}
