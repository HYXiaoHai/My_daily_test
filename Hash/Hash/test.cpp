#define _CRT_SECURE_NO_WARNINGS 1
#include"UnorderedSet.h"
#include"UnorderedMap.h"
int main()
{
	Xiaohai::test_set();
	return 0;
}


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
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};
	template<class K, class T, class KeyOfT, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashNode<T> Node;
	public:
		HashTable()
			:_tables(__stl_next_prime(1), nullptr)
			, _n(0)
		{
		}

		// 哈希桶的销毁
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		// 插入值为data的元素，如果data存在则不插入
		bool Insert(const T& data)
		{
			KeyOfT kot;
			if (Find(kot(data)))
				return false;
			Hash hs;
			if (_n == _tables.size())
			{
				vector<Node*>newtables(__stl_next_prime(_tables.size()+1));
				for (size_t i =0;i<_tables.size();i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t hashi = hs(kot(cur->_data)) % newtables.size();
						cur->_next = newtables[hashi];
						newtables[hashi] = cur;

						cur = next;

					}
					_tables[i] = nullptr;
				}
				_tables.swap(newtables);
			}
			size_t hashi = hs(kot(data)) % _tables.size();
			//头插
			Node* newNode = new Node(data);
			newNode->_next = _tables[hashi];
			_tables[hashi] = newNode;

			++_n;
			return true;
		}

		// 在哈希桶中查找值为key的元素，存在返回true否则返回false﻿
		bool Find(const K& key)
		{
			KeyOfT kot;
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}

		// 哈希桶中删除key的元素，删除成功返回true，否则返回false
		bool Erase(const K& key)
		{
			KeyOfT kot;
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prev = nullptr;
			while (cur)
			{
				if (kot(cur->_data) == key)
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
		vector<Node*> _tables;  // 指针数组
		size_t _n = 0;			// 表中存储数据个数
	};
}