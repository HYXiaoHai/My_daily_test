#define _CRT_SECURE_NO_WARNINGS 1
#include"Map.h"
#include"Set.h"

//void test_set()
//{
//	set<int>s;
//	s.insert(2);
//	s.insert(1);
//	s.insert(4);
//	s.insert(22);
//	s.insert(2222);
//	s.insert(11);
//	s.insert(98);
//
//	//set<int>::iterator it = s.begin();
//	//while (it!=s.end())
//	//{
//	//	cout << *it << " ";
//	//	++it;
//	//}
//	//cout << endl;
//	set<int>::iterator it = s.end();
//	while (it!=s.begin())
//	{
//		cout << *it << " ";
//		--it;
//	}
//	cout << endl;
//}

void test_map()
{
	map<string, string>dict;
	dict.insert({"sort","排序"});
	dict.insert({"left","左边"});
	dict.insert({"right","右边"});

	dict["left"] = "左";
	dict["insert"] = "插入";
	dict["string"] = "字符";

	map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first<<":" << it->second<<endl;
		++it;
	}
}
int main()
{
	//test_set();
	test_map();
	return 0;
}
//
//

// 说明：
// 1. 在完善迭代器前，请先确保红黑树实现成功
// 2. 迭代器实现好后，与红黑树结合起来，能够通过红黑树的迭代器遍历红黑树
// 3. 此处给的迭代器实现并不完整，缺少--操作，大家只需要将++实现即可，此处主要了解红黑树迭代器原理即可
//    要实现完整的迭代器需要对红黑树进行改造，有兴趣可参考侯捷《STL源码剖析》





// 注意：红黑树完整操作参考课堂代码
// 此处给红黑树添加迭代器，其他用不到的操作暂被拿掉，只留下红黑树构建的核心操作
