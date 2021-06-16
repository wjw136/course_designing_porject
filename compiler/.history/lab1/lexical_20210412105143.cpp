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
}
//operator
static char operator[22][10]={
    "(",")","*","*/","+",",","-",
    "..","/","/*",":",":=",";","<",
    "<=","<>","=",">",">=","[","]"
}
bool isDigit(char ch){
    if(ch>='0'&&ch<='9')
    return true;
    else
    {
        return false;
    }
    
}
bool isLetter(char ch){
    if((ch>='a'&&ch<='z')||(ch<='Z'&&ch>="A")||ch='_')
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
        if(s[i]=='/'&&s[i+1]=='*'){
            i+=2;
            while(s[i]!='*'||s[i+1]!='/'){
                if(s[i]=='\0')
            }
        }
    }
}
int main(){
   

   system("pause");
   return 0;
}
