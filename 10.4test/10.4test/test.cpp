#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<map>
using namespace std;

void test01()
{

}

int main()
{
	// initializer_list构造及迭代遍历 
	map<string, string> dict = { {"left", "左边"}, {"right", "右边"},
   {"insert", "插⼊"},{ "string", "字符串" } };
	//map<string, string>::iterator it = dict.begin();

	auto it = dict.begin();
	while (it != dict.end())
	{
		//cout << (*it).first <<":"<<(*it).second << endl;
		// map的迭代基本都使⽤operator->,这⾥省略了⼀个-> 
		// 第⼀个->是迭代器运算符重载，返回pair*，第⼆个箭头是结构指针解引⽤取pair数据
		//cout << it.operator->()->first << ":" << it.operator->()-> second << endl;
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;

	//insert插⼊pair对象的4种⽅式，对⽐之下，最后⼀种最⽅便 
	pair<string, string> kv1("first", "第⼀个");
	dict.insert(kv1);
	dict.insert(pair<string, string>("second", "第⼆个"));
	dict.insert(make_pair("sort", "排序"));
	dict.insert({ "auto", "⾃动的" });

	//"left"已经存在，插⼊失败 
	dict.insert({ "left", "左边，剩余" });
	dict.insert({ "left", "*****" });//插入失败
	dict.insert({ "Left", "左边" });//插入成功 map的插入只看key

	auto it = dict.find("first");//查找
	it->second = "第二";
	dict["set"];//插入
	dict["set"] = "集合";//修改
	dict["begin"] = "开始";//插入+修改
	cout << dict["set"] << endl;//查找

	// 范围for遍历 
	for (const auto& e : dict)
	{
		cout << e.first << ":" << e.second << endl;
	}
	cout << endl;

	string str;
	while (cin >> str)
	{
		auto ret = dict.find(str);
		if (ret != dict.end())
		{
			cout << "->" << ret->second << endl;
		}
		else
		{
			cout << "⽆此单词，请重新输⼊" << endl;
		}
	}
	// erase等接⼝跟set完全类似，这⾥就不演⽰讲解了 
	return 0;
}