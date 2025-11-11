#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] =
	{
	 53, 97, 193, 389, 769,
	 1543, 3079, 6151, 12289, 24593,
	 49157, 98317, 196613, 393241, 786433,
	 1572869, 3145739, 6291469, 12582917, 25165843,
	 50331653, 100663319, 201326611, 402653189, 805306457,
	 1610612741, 3221225473, 4294967291
	};
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};
template<>
struct HashFunc<string>
{
	size_t operator()(const string& key)
	{
		size_t hash = 0;
		for (auto e : key)
		{
			hash *= 131;
			hash += e;
		}
		return hash;
	}
};
namespace hash_bucket
{
	
	template<class K,class V>
	struct HashNode
	{
		pair<K, V>_kv;
		HashNode<K, V>* _next;

		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			,_next(nullptr)
		{ }
	};


	template<class K,class V,class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V>Node;
	public:
		HashTable()
			:_tables(__stl_next_prime(1), nullptr)
			,_n(0)
		{}
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				//当前桶的节点重新映射挂到新表
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}
		
		bool insert(const pair<K,V>&kv)
		{
			if (Find(kv.first))
				return false;
			Hash hs;
			//负载因子==1扩容
			if (_n == _tables.size())
			{
				vector<Node*>newtables(__stl_next_prime(_tables.size()+1));
				for (size_t i =0;i<_tables.size();i++)
				{
					Node* cur = _tables[i];
					//当前桶的节点重新映射挂到新表
					while (cur)
					{
						Node* next = cur->_next;
						//插入到新表
						size_t hashi = hs(cur->_kv.first) % newtables.size();
						cur->_next = newtables[hashi];
						newtables[hashi] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newtables);
			}

			size_t hashi = hs(kv.first) % _tables.size();
			//头插
			Node* newNode = new Node(kv);
			newNode->_next = _tables[hashi];
			_tables[hashi] = newNode; 
			
			++_n;
			return true;
		}

		Node* Find(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prev = nullptr;
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

	private:
		//vector<list<pair<K, V>>>_tables;后续包装复杂
		vector<Node*> _tables;
		size_t _n;//实际存储的数据个数
	};
}

void test1()
{
	hash_bucket::HashTable<int, int>ht;
	int a[] = { 19,30,5,36,13,20,21,12,24,96 };
	for (auto e:a)
	{
		ht.insert({e,e});
	}
	ht.Erase(30);
	ht.Erase(19);
	ht.Erase(96);

	for (size_t i =10;i<200;i++)
	{
		ht.insert({ i,i });
	}
}
void test2()
{
	hash_bucket::HashTable<string, string>dict;
	dict.insert({ "insert","插入" });
	auto ptr = dict.Find("insert");
	if (ptr)
	{
		cout << ptr->_kv.second << endl;
	}
}

int main()
{
	//test1();
	test2();
	return 0;
}