#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<set>
#include<vector>
using namespace std;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
	vector<int>v;
	set<int>s1(nums1.begin(), nums1.end());
	set<int>s2(nums2.begin(), nums2.end());

	auto it1 = s1.begin();
	auto it2 = s2.begin();
	while (it1 != s1.end() && it2 != s2.end())
	{
		if (*it1 < *it2)
		{
			it1++;
		}
		else if (*it1 > *it2)
		{
			it2++;
		}
		else
		{
			v.push_back(*it1);
			it1++;
			it2++;
		}
	}
	return v;
}

int main()
{
	vector<int>num1 = { 6,6,4,4,0,0,8,1,2 };
	vector<int>num2 = {6};
	vector<int>res = intersection(num1, num2);
	for(auto e:res)
	{
		cout << e << " ";
	}
	cout << endl;
	return 0;
}
