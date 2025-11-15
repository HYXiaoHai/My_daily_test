#pragma once
#include"HashTable.h"
namespace bit
{
	template<class K>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename HashTable<K, K, SetKeyOfT>::Iterator iterator;
		typedef typename HashTable<K, K, SetKeyOfT>::ConstIterator const_iterator;
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
		pair<iterator, bool> insert(const K& key)
		{
			return _t.Insert(key);
		}
	private:
		HashTable<K, K, SetKeyOfT> _t;
	};

	void Func(const unordered_set<int>& s)
	{
		auto it1 = s;

	}

	void test_set()
	{
		unordered_set<int> s;
		int a[] = { 4, 2, 6, 1, 3, 599, 1590, 7, 16, 14, 3,3,15 };
		for (auto e : a)
		{
			s.insert(e);
		}

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;
		//unordered_set<int>::iterator it = s.begin();
		//while (it != s.end())
		//{
		//	// 不⽀持修改 
		//	//*it += 1;

		//	cout << *it << " ";
		//	++it;
		//}
		//cout << endl;
	}
}

namespace XiaoHai
{
	// unordered_set中存储的是K类型，HF哈希函数类型
// unordered_set在实现时，只需将hashbucket中的接口重新封装即可
	template<class K, class HF = HashFunc<K>>
	class unordered_set
	{
		// 通过key获取value的操作
		struct KeyOfValue
		{
			const K& operator()(const K& data)
			{
				return data;
			}
		};
		typedef HashBucket<K, K, KeyOfValue, HF> HT;

	public:
		typename typedef HT::Iterator iterator;
	public:
		unordered_set() : _ht()
		{
		}
		////////////////////////////////////////////////////
		iterator begin() { return _ht.begin(); }
		iterator end() { return _ht.end(); }
		////////////////////////////////////////////////////////////
		// capacity
		size_t size()const { return _ht.size(); }
		bool empty()const { return _ht.empty(); }
		///////////////////////////////////////////////////////////
		// lookup
		iterator find(const K& key) { return _ht.Find(key); }
		size_t count(const K& key) { return _ht.Count(key); }
		/////////////////////////////////////////////////
		// modify
		pair<iterator, bool> insert(const K& valye)
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
		HashBucket<K, K, KeyOfValue, HF> _ht;
	};
}
