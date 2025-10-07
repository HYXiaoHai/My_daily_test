#define _CRT_SECURE_NO_WARNINGS 1
#include <algorithm>
#include <iostream>
#include<map>
#include <string>
#include <utility>
#include <vector>
using namespace std;
struct Compare
{
    bool operator()(const pair<string, int>& x, const pair<string, int>& y)const
    {
        return x.second > y.second || (x.second == y.second && x.first < y.first);
    }
};
void Build(string x,map<string,int>&m)
{
    if (x == "")
    {
        return;
    }
    string tmp;
    int i = 0;
    while (i < x.size())
    {
        if (x[i] == ' ')
        {
            m[tmp]++;
            tmp = "";
        }
        else
        {
            tmp += x[i];
        }
        i++;
    }
}

int main() {
    string x1;
    map<string, int>m1;
    while (cin>>x1)
    {
        m1[x1]++;
    }
    //Build(x1,m1);
    vector<pair<string, int>>v(m1.begin(), m1.end());
    sort(v.begin(), v.end(), Compare());
    for (auto& e : v)
    {
        cout << e.first << ":" << e.second << endl;
    }
    return 0;
}