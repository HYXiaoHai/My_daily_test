#pragma once
#include<vector>
#include<iostream>
using namespace std;

enum Status
{
	EXIST,
	EMPTY,
	DELETE
};


template<class K, class V>
struct HashData
{
	pair<K, V> _kv;
	Status _status = EMPTY;
};

template<class K, class V>
class HashTable
{
public:
	HashTable()
		:_tables(11)
		, _n(0)
	{
	}

	bool Insert(const pair<K, V>& kv)
	{

		//扩容 负载因子0.7
		if ((double)_n / (double)_tables.size() >= 0.7)
		{
			//vector<HashData<K, V>>newtables(_tables.size()*2);
			////遍历旧表将所有值映射到新表
			//for (auto& data: _tables)
			//{
			//	if (data._status == EXIST)
			//	{
			//		//...
			//	}
			//}
			//_tables.swap(newtables);

			HashTable<K, V>newHT;
			newHT._tables.resize(_tables.size() * 2);
			//遍历旧表将所有值映射到新表
			for (auto& data : _tables)
			{
				if (data._status == EXIST)
				{
					newHT.Insert(data._kv);
				}
			}
			_tables.swap(newHT._tables);
		}

		size_t hash0 = kv.first % _tables.size();
		size_t hashi = hash0;
		size_t i = 0;
		//线性探测
		while (_tables[hashi]._status == EXIST)
		{
			hashi = (hash0 + i) % _tables.size();
			++i;
		}

		_tables[hashi]._kv = kv;
		_tables[hashi]._status = EXIST;
		++_n;

		return true;
	}

	HashData<K, V>* Find(const K& key)
	{
		size_t hash0 = key % _tables.size();
		size_t hashi = hash0;
		size_t i = 1;
		while (_tables[hashi]._status != EMPTY)
		{
			if (_tables[hashi]._status == EXIST && _tables[hashi]._kv.first == key)
				return &_tables[hashi];

			hashi = (hash0 + i) % _tables.size();
			++i;
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		auto* ptr = Find(key);
		if (ptr)
		{
			ptr->_status = DELETE;
			--_n;
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	vector<HashData<K, V>>_tables;
	size_t _n = 0;
};

void TestHT1()
{
	HashTable<int, int>ht;
	int a[] = { 19,30,5,36,13,20,21,12,58};
	for (auto e : a)
	{
		ht.Insert({ e,e });
	}

	cout << ht.Find(5) << endl;
	cout << ht.Find(58) << endl;
	ht.Erase(5);
	cout << ht.Find(5) << endl;
	cout << ht.Find(58) << endl;

	for (auto e : a)
	{
		ht.Insert({ e,e }); 
	}
}