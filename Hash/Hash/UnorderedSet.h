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
		bool insert(const K& key)
		{
			return _t.Insert(key);
		}
	private:
		HashTable<K, K, SetKeyOfT> _t;
	};
	void test_set()
	{
		unordered_set<int> s;
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14, 3,3,15 };
		for (auto e : a)
		{
			s.insert(e);
		}

		/*for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;*/
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

