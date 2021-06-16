#include <iostream>
#include <windows.h>
#include <string.h>
#include <queue>
#include <math.h>
#include <map>
#include "stdio.h"
#define ll long long
#define inf 100000
#define clr1(a) memset(a, -1, sizeof(a))
#define clr(a) memset(a, 0, sizeof(a))
using namespace std;

class EE
{
public:
    int a;
    string b;
    EE(int a)
    {
        this->a = a;
    }
    bool operator<(const EE &b) const
    {
        //严格弱比较 严格是说在判断的时候会用"<"，而不是"<="，弱排序是因为，一旦"<"成立便认为存在"<"关系，返回ture，而忽略了"="关系和">"区别，把它们归结为false。
        return this->a < b.a;
    }
};

int main()
{
    cout << ":111" << endl;
    map<EE, string> test_set;
    test_set[EE(4)] = "1";
    test_set[EE(3)] = "2";
    for (auto &i : test_set)
    {
        cout << i.first.a << " " << i.second << endl;
    }

    system("pause");
    return 0;
}
