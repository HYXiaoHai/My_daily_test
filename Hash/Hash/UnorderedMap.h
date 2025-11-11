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
		typedef typename HashTable<K, pair<const K, V>, MapKeyOfT>::Iterator iterator;
		typedef typename HashTable<K, pair<const K, V>, MapKeyOfT>::ConstIterator const_iterator;
		iterator begin()
		{
			return _t.Begin();
		}
		iterator end()
		{
			return _t.End();
		}
		const_iterator begin()const
		{
			return _t.Begin();
		}
		const_iterator end()const
		{
			return _t.End();
		}
		iterator find(const K& key)
		{
			return _t.Find(key);
		}
		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}
		V& operator[](const K& key)
		{
			pair<iterator, bool>ret = insert({ key,V() });
			return ret.first->second;
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
		dict["left"] = "左边，剩余";
		dict["insert"] = "插⼊";
		dict["string"] = "字符串";
		dict["string"] = "string";
		for (auto& [k, v] : dict)
		{
			//k += 'x';
			v += 'x';
			cout << k << ":" << v << endl;
		}


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
