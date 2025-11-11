#pragma once
#include"HashTable.h"
namespace Xiaohai
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

