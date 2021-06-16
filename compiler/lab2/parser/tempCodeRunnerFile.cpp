#include <iostream>
#include <windows.h>
#include <string.h>
#include <queue>
#include <fstream>

#include <math.h>
#include "stdio.h"
using namespace std;
int main()
{
    fstream fin("222.txt");
    //fin.open("222.txt",ios::out);
    if (fin.fail())
    {
        cout << 2 << endl;
    }
    int a;
    fin >> a;
    cout << a << endl;
    //fin<<"222"<<endl;
    fin.close(); 
    system("pause");
}
