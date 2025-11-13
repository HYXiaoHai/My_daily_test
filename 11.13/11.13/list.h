                                                                                      #pragma once
#include<iostream>
#include<vector>
using namespace std;
namespace XiaoHai
{
	template<class T>
	struct list_node
	{
		T _data;
		list_node<T>* _next;  
		list_node<T>* _prev;

		list_node(const T& x = T())
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{ }
		list_node(T&& x = T())
			:_data(move(x))
			, _next(nullptr)
			, _prev(nullptr)
		{ 
			cout<<
		}
	};

	template<class T, class ref, class Ptr>
	struct Reverse_iterator
	{
		Iterator _it;
		typedef Reverse_iterator<Iterator, Ref, Ptr> Self;
		Reverse_iterator(Iterator it)
			:_it(it)
		{
		}

		Ref operator*()
		{
			iterator tmp(_it);
			--tmp;
			return *tmp;
		}
		Ptr operator->()
		{
			return &(operator*());
		}

		self operator++(int)
		{
			self tmp(_it);
			--_it;
			return *tmp;
		}
		self operator--(int)
		{
			self tmp(_it);
			++_it;
			return *tmp;
		}
		self operator++()
		{
			--_it;
			return *tmp;
		}
		self operator--()
		{
			++_it;
			return *tmp;
		}
		bool operator!=(const Self& s)
		{
			return _it != s._it;
		}
	};

	template<class T,class ref,class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> Node;
		typedef __list_iterator<T,ref,Ptr> self;
		Node* _node;
		__list_iterator(Node* node)
			:_node(node)
		{ }

		ref& operator*()
		{
			return _node->_data;
		}

		T* operator->()
		{
			return &_node->_data;
		}

		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		self& operator++(int)
		{
			__list_iterator<T>tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		self& operator--(int)
		{
			__list_iterator<T>tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		bool operator!=(const __list_iterator<T>& it)const
		{
			return _node != it._node;
		}
		bool operator ==(const __list_iterator<T>& it)const
		{
			return !(_node != it._node);
		}
	};

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T,const T&,const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}
		const_iterator begin() const
		{
			return iterator(_head->_next);
		}

		const_iterator end() const
		{
			return iterator(_head);
		}
		
		void empty_init()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		list()
		{
			empty_init();
		}

		//lt2(lt1)
		list(const list<T>&lt)
		{
			empty_init();
			for (const auto& e:lt)
			{
				push_back(e);
			}
		}

		list(initializer_list<int>il)
		{
			empty_init();
			for (const auto& e : il)
			{
				push_back(e);
			}
		}

		void swap(list<T>&lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		//lt1 = lt2
		list<T>& operator=(const list<T>* lt)
		{
			swap(lt);
			return *this;
		}

		/*list<T>& operator=(const list<T>* lt)
		{
			if (this != &lt)
			{
				clear();
				for (const auto& e : il)
				{
					push_back(e);
				}
			}
			return *this;
		}*/

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void push_back(T&& x)
		{
			insert(end(), move(x));
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		void push_front(T&& x)
		{
			insert(begin(), move(x));
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		void insert(iterator pos, const T& val)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(val);
			Node* prev = cur->_prev;

			//prev newnode cur
			prev->_next = newnode;
			newnode->_next = cur;
			cur->_prev = newnode;
			newnode->_prev = prev;
			++_size;
		}
		void insert(iterator pos, T&& val)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(val);
			Node* prev = cur->_prev;

			//prev newnode cur
			prev->_next = newnode;
			newnode->_next = cur;
			cur->_prev = newnode;
			newnode->_prev = prev;
			++_size;
		}

		iterator& erase(iterator pos)
		{
			Node* cur = pos._node;
			Node* next = cur->_next;
			Node* prev = cur->_prev;

			//prev (cur) next
			prev->_next = next;
			next->_prev = prev;
			delete cur;
			--_size;

			return iterator(next);
		}

		size_t size()
		{
			return _size;
		}

	private:
		Node* _head;
		size_t _size = 0;
	};
}

