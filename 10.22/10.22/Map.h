#pragma once
#include"RBTree.h"
template<class K,class V>
class map
{
	struct MapKeyOfT
	{
		const K& operator()(const pair<K, V>& kv)const
		{
			return kv.first;
		}
	};
public:
	typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::Iterator iterator;
	iterator begin()
	{
		return _t.Begin();
	}
	iterator end()
	{
		return _t.End();
	}
	pair<iterator, bool> insert(const pair<K, V>& kv)
	{
		return _t.Insert(kv);
	}
	V& operator[](const K& key)
	{
		pair<iterator,bool> ret = insert({ key,V()});
		return ret.first->scend;
	}

private:
	RBTree<K, const pair<K, V>, MapKeyOfT>_t;
};