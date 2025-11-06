#define _CRT_SECURE_NO_WARNINGS 1
#include"Map.h"
#include"Set.h"

void test_set()
{
	set<int>s;
	s.insert(2);
	s.insert(1);
	s.insert(4);
	s.insert(22);
	s.insert(2222);
	s.insert(11);
	s.insert(98);

	//set<int>::iterator it = s.begin();
	//while (it!=s.end())
	//{
	//	cout << *it << " ";
	//	++it;
	//}
	//cout << endl;
	set<int>::iterator it = s.end();
	while (it!=s.begin())
	{
		cout << *it << " ";
		--it;
	}
	cout << endl;
}

void test_map()
{
	map<string, string>dict;
	dict.insert({"sort","ÅÅĞò"});
	dict.insert({"left","×ó±ß"});
	dict.insert({"right","ÓÒ±ß"});

	map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first<<":" << it->second<<endl;
		++it;
	}
}
int main()
{
	test_set();
	return 0;
}