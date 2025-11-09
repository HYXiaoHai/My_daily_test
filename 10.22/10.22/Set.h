#pragma once
#include"RBTree.h"
template<class K>
class set
{
	struct SetKeyOfT
	{
		const K& operator()(const K& key)const
		{
			return key;
		}
	};
public:
	typedef typename RBTree<K, const K, SetKeyOfT>::Iterator iterator;

	iterator begin()
	{
		return _t.Begin();
	}

	iterator end()
	{
		return _t.End();
	}

	pair<iterator,bool> insert(const K& k)
	{
		return _t.Insert(k);

	}
private:
	RBTree<K, const K, SetKeyOfT>_t;
};