#pragma once
#include"HashTable.h"
namespace Xiaohai
{
	template<class K, class V>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		bool insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

	private:
		HashTable<K, pair<const K, V>, MapKeyOfT> _t;
	};
	void test_map()
	{
		unordered_map<string, string> dict;
		dict.insert({ "sort", "排序" });
		dict.insert({ "left", "左边" });
		dict.insert({ "right", "右边" });
	/*	dict["left"] = "左边，剩余";
		dict["insert"] = "插⼊";
		dict["string"];*/
		//unordered_map<string, string>::iterator it = dict.begin();
		//while (it != dict.end())
		//{
		//	// 不能修改first，可以修改second 
		//	//it->first += 'x';
		//	it->second += 'x';
		//	cout << it->first << ":" << it->second << endl;
		//	++it;
		//}
		//cout << endl;
	}
}
