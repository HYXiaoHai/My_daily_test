#pragma once
#include"HashTable.h"
namespace bit
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

namespace XiaoHai
{
	// unordered_map中存储的是pair<K, V>的键值对，K为key的类型，V为value的类型，HF哈希函数类型
	// unordered_map在实现时，只需将hashbucket中的接口重新封装即可
	template<class K, class V, class HF = HashFunc<K>>
	class unordered_map
	{
		// 通过key获取value的操作
		struct KeyOfValue
		{
			const K& operator()(const pair<K, V>& data)
			{
				return data.first;
			}
		};
		typedef HashBucket<K, pair<K, V>, KeyOfValue, HF> HT;
	public:
		typename typedef HT::Iterator iterator;
	public:
		iterator begin() { return _ht.begin(); }
		iterator end() { return _ht.end(); }
		////////////////////////////////////////////////////////////
		// capacity
		size_t size()const { return _ht.size(); }
		bool empty()const { return _ht.empty(); }
		///////////////////////////////////////////////////////////
		// Acess
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.Insert(pair<K, V>(key, V()));
			return ret.fisrt->second;
		}
		const V& operator[](const K& key)const
		{
			pair<iterator, bool> ret = _ht.Insert(pair<K, V>(key, V()));
			return ret.fisrt->second;
		}
		//////////////////////////////////////////////////////////
		// lookup
		iterator find(const K& key) { return _ht.Find(key); }
		// modify
		pair<iterator, bool> insert(const pair<K, V>& valye)
		{
			return _ht.Insert(valye);
		}

		iterator erase(iterator position)
		{
			return _ht.Erase(position);
		}
		////////////////////////////////////////////////////////////
		// bucket
		size_t bucket_count() { return _ht.BucketCount(); }
		size_t bucket_size(const K& key) { return _ht.BucketSize(key); }
	private:
		HT _ht;
	};
}