#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//template <class _Ty>
//remove_reference_t<_Ty>&& move(_Ty&& _Arg)
//{ // forward _Arg as movable
//	return static_cast<remove_reference_t<_Ty>&&>(_Arg);
//}

//using namespace std;
//int main()
//{
//	// 左值：可以取地址 
//	// 以下的p、b、c、*p、s、s[0]就是常⻅的左值 
//	int* p = new int(0);
//	int b = 1;
//	const int c = b;
//	*p = 10;
//	string s("111111");
//	s[0] = 'x';
//	double x = 1.1, y = 2.2;
//
//	// 左值引⽤给左值取别名 
//	int& r1 = b;
//	int*& r2 = p;
//	int& r3 = *p;
//	string& r4 = s;
//	char& r5 = s[0];
//
//	// 右值引⽤给右值取别名 
//	int&& rr1 = 10;
//	double&& rr2 = x + y;
//	double&& rr3 = fmin(x, y);
//	string&& rr4 = string("11111");
//
//	// 左值引⽤不能直接引⽤右值，但是const左值引⽤可以引⽤右值 
//	const int& rx1 = 10;
//	const double& rx2 = x + y;
//	const double& rx3 = fmin(x, y);
//	const string& rx4 = string("11111");
//
//	// 右值引⽤不能直接引⽤左值，但是右值引⽤可以引⽤move(左值) 
//	int&& rrx1 = move(b);
//	int*&& rrx2 = move(p);
//	int&& rrx3 = move(*p);
//	string&& rrx4 = move(s);
//	string&& rrx5 = (string&&)s;
//	// b、r1、rr1都是变量表达式，都是左值 
//	cout << &b << endl;
//	cout << &r1 << endl;
//	cout << &rr1 << endl;
//
//	// 这⾥要注意的是，rr1的属性是左值，所以不能再被右值引⽤绑定，除⾮move⼀下 
//	int& r6 = r1;
//	// int&& rrx6 = rr1;
//	int&& rrx6 = move(rr1);
//	return 0;
//}

//#include<iostream>
//using namespace std;
//void f(int& x)
//{
//	std::cout << "左值引⽤重载 f(" << x << ")\n";
//}
//void f(const int& x)
//{
//	std::cout << "到 const 的左值引⽤重载 f(" << x << ")\n";
//}
//void f(int&& x)
//{
//	std::cout << "右值引⽤重载 f(" << x << ")\n";
//}
//int main()
//{
//	int i = 1;
//	const int ci = 2;
//	f(i); // 调⽤ f(int&) 
//	f(ci); // 调⽤ f(const int&) 
//	f(3); // 调⽤ f(int&&)，如果没有 f(int&&) 重载则会调⽤ f(const int&) 
//	f(std::move(i)); // 调⽤ f(int&&) 
//	// 右值引⽤变量在⽤于表达式时是左值 
//	int&& x = 1;
//	f(x); // 调⽤ f(int& x) 
//	f(std::move(x)); // 调⽤ f(int&& x) 
//	return 0;
//}

#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
#include<string.h>
#include<algorithm>
using namespace std;
namespace XiaoHai
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str)-构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷⻉构造" << endl;
			reserve(s._capacity);
			for (auto ch : s)
			{
				push_back(ch);
			}
		}

		// 移动构造 
		string(string&& s)
		{
			cout << "string(string&& s) -- 移动构造" << endl;
			swap(s);
		}
		string& operator=(const string& s)
		{
			cout << "string& operator=(const string& s) -- 拷⻉赋值" <<
				endl;
			if (this != &s)
			{
				_str[0] = '\0';
				_size = 0;
				reserve(s._capacity);
				for (auto ch : s)
				{
					push_back(ch);
				}
			}
			return *this;
		}

		// 移动赋值 
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- 移动赋值" << endl;
			swap(s);
			return *this;
		}
		~string()
		{
			cout << "~string() -- 析构" << endl;
			delete[] _str;
			_str = nullptr;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				if (_str)
				{
					strcpy(tmp, _str);
					delete[] _str;
				}
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity *
					2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		const char* c_str() const
		{
			return _str;
		}
		size_t size() const
		{
			return _size;
		}
	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
	};
}
//int main()
//{
//	XiaoHai::string s1("xxxxx");
//	// 拷⻉构造 
//	XiaoHai::string s2 = s1;
//	// 构造+移动构造，优化后直接构造 
//	XiaoHai::string s3 = XiaoHai::string("yyyyy");
//	// 移动构造 
//	XiaoHai::string s4 = move(s1);
//	cout << "******************************" << endl;
//
//	return 0;
//}

namespace XiaoHai
{
	string addStrings(string num1, string num2)
	{
		string str;
		int end1 = num1.size() - 1, end2 = num2.size() - 1;
		int next = 0;
		while (end1 >= 0 || end2 >= 0)
		{
			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
			int ret = val1 + val2 + next;
			next = ret / 10;
			ret = ret % 10;
			str += ('0' + ret);
		}
		if (next == 1)
			str += '1';
		reverse(str.begin(), str.end());
		cout << "******************************" << endl;
		return str;
	}
}
//// 场景1 
//int main()
//{
//	XiaoHai::string XiaoHai = XiaoHai::addStrings("11111", "2222");
//	cout << ret.c_str() << endl;
//	return 0;
//}
//// 场景2 
//int main()
//{
//	XiaoHai::string ret;
//	ret = XiaoHai::addStrings("11111", "2222");
//	cout << ret.c_str() << endl;
//	return 0;
//}
//


// List.h
// 以下代码为了控制课件篇幅，把跟这⾥⽆关的接⼝都删除了 
namespace XiaoHai
{
	template<class T>
	struct ListNode
	{
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _data;
		ListNode(const T& data = T())
			:_next(nullptr)
			, _prev(nullptr)
			, _data(data)
		{
		}
		ListNode(T&& data)
			:_next(nullptr)
			, _prev(nullptr)
			, _data(move(data))
		{
		}
	};
	template<class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, Ref, Ptr> Self;
		Node* _node;
		ListIterator(Node* node)
			:_node(node)
		{
		}
		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		Ref operator*()
		{
			return _node->_data;
		}
		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}
	};
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		void empty_init()
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		list()
		{
			empty_init();
		}
		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void push_back(T&& x)
		{
			insert(end(), move(x));
		}
		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(x);
			Node* prev = cur->_prev;
			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
		iterator insert(iterator pos, T&& x)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(move(x));
			Node* prev = cur->_prev;
			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
	private:
		Node* _head;
	};
}
// Test.cpp
#include"List.h"
int main()
{
	bit::list<bit::string> lt;
	cout << "*************************" << endl;
	bit::string s1("111111111111111111111");
	lt.push_back(s1);
	cout << "*************************" << endl;
	lt.push_back(bit::string("22222222222222222222222222222"));
	cout << "*************************" << endl;
	lt.push_back("3333333333333333333333333333");
	cout << "*************************" << endl;
	lt.push_back(move(s1));
	cout << "*************************" << endl;
	return 0;
}

template <class _Ty>
_Ty&& forward(remove_reference_t<_Ty>& _Arg) noexcept
{ // forward an lvalue as either an lvalue or an rvalue
	return static_cast<_Ty&&>(_Arg);
}
void Fun(int& x) { cout << "左值引⽤" << endl; }
void Fun(const int& x) { cout << "const 左值引⽤" << endl; }
void Fun(int&& x) { cout << "右值引⽤" << endl; }
void Fun(const int&& x) { cout << "const 右值引⽤" << endl; }
template<class T>
void Function(T&& t)
{
	Fun(t);
	//Fun(forward<T>(t));
}
int main()
{
	// 10是右值，推导出T为int，模板实例化为void Function(int&& t) 
	Function(10); // 右值 
	int a;
	// a是左值，推导出T为int&，引⽤折叠，模板实例化为void Function(int& t) 
	Function(a); // 左值 
	// std::move(a)是右值，推导出T为int，模板实例化为void Function(int&& t) 
	Function(std::move(a)); // 右值 
	const int b = 8;
	// a是左值，推导出T为const int&，引⽤折叠，模板实例化为void Function(const int& 
	t)
	Function(b); // const 左值 
	// std::move(b)右值，推导出T为const int，模板实例化为void Function(const int&& 
	t)
	Function(std::move(b)); // const 右值 
	return 0;
}

//template <class ...Args>
//void Print(Args&&... args)
//{
//	cout << sizeof...(args) << endl;
//}
//int main()
//{
//	double x = 2.2;
//	Print(); // 包⾥有0个参数 
//	Print(1); // 包⾥有1个参数 
//	Print(1, string("xxxxx")); // 包⾥有2个参数 
//	Print(1.1, string("xxxxx"), x); // 包⾥有3个参数 
//	return 0;
//}
//// 原理1：编译本质这⾥会结合引⽤折叠规则实例化出以下四个函数 
//void Print();
//void Print(int&& arg1);
//void Print(int&& arg1, string&& arg2);
//void Print(double&& arg1, string&& arg2, double& arg3);
//// 原理2：更本质去看没有可变参数模板，我们实现出这样的多个函数模板才能⽀持 
//// 这⾥的功能，有了可变参数模板，我们进⼀步被解放，他是类型泛化基础 
//// 上叠加数量变化，让我们泛型编程更灵活。 
//void Print();
//template <class T1>
//void Print(T1&& arg1);
//template <class T1, class T2>
//void Print(T1&& arg1, T2&& arg2);
//template <class T1, class T2, class T3>
//void Print(T1&& arg1, T2&& arg2, T3&& arg3);
//// ...

//// 可变模板参数 
//// 参数类型可变 
//// 参数个数可变 
//// 打印参数包内容 
////template <class ...Args>
////void Print(Args... args)
////{
//// // 可变参数模板编译时解析 
//// // 下⾯是运⾏获取和解析，所以不⽀持这样⽤ 
//// cout << sizeof...(args) << endl;
//// for (size_t i = 0; i < sizeof...(args); i++)
//// {
//// cout << args[i] << " ";
//// }
//// cout << endl;
////}
//void ShowList()
//{
//	// 编译器时递归的终⽌条件，参数包是0个时，直接匹配这个函数 
//	cout << endl;
//}
//template <class T, class ...Args>
//void ShowList(T x, Args... args)
//{
//	cout << x << " ";
//	// args是N个参数的参数包 
//	// 调⽤ShowList，参数包的第⼀个传给x，剩下N-1传给第⼆个参数包 
//	ShowList(args...);
//}
//// 编译时递归推导解析参数 
//template <class ...Args>
//void Print(Args... args)
//{
//	ShowList(args...);
//}
//int main()
//{
//	Print();
//	Print(1);
//	Print(1, string("xxxxx"));
//	Print(1, string("xxxxx"), 2.2);
//	return 0;
//}
////template <class T, class ...Args>
////void ShowList(T x, Args... args)
////{
//// cout << x << " ";
//// Print(args...);
////}
//// Print(1, string("xxxxx"), 2.2);调⽤时 
//// 本质编译器将可变参数模板通过模式的包扩展，编译器推导的以下三个重载函数函数 
////void ShowList(double x)
////{
//// cout << x << " ";
//// ShowList();
////}
////
////void ShowList(string x, double z)
////{
//// cout << x << " ";
//// ShowList(z);
////}
////
////void ShowList(int x, string y, double z)
////{
//// cout << x << " ";
//// ShowList(y, z);
////}
////void Print(int x, string y, double z)
////{
//// ShowList(x, y, z);
////}
//template <class T>
//const T& GetArg(const T& x)
//{
//	cout << x << " ";
//	return x;
//}
//template <class ...Args>
//void Arguments(Args... args)
//{
//}
//template <class ...Args>
//void Print(Args... args)
//{
//	// 注意GetArg必须返回或者到的对象，这样才能组成参数包给Arguments 
//	Arguments(GetArg(args)...);
//}
//// 本质可以理解为编译器编译时，包的扩展模式 
//// 将上⾯的函数模板扩展实例化为下⾯的函数 
//// 是不是很抽象，C++11以后，只能说委员会的⼤佬设计语法思维跳跃得太厉害 
////void Print(int x, string y, double z)
////{
//// Arguments(GetArg(x), GetArg(y), GetArg(z));
////}
//int main()
//{
//	Print(1, string("xxxxx"), 2.2);
//	return 0;
//}

//#include<list>
//// emplace_back总体⽽⾔是更⾼效，推荐以后使⽤emplace系列替代insert和push系列 
//int main()
//{
//	list<bit::string> lt;
//	// 传左值，跟push_back⼀样，⾛拷⻉构造 
//	bit::string s1("111111111111");
//	lt.emplace_back(s1);
//	cout << "*********************************" << endl;
//	// 右值，跟push_back⼀样，⾛移动构造 
//	lt.emplace_back(move(s1));
//	cout << "*********************************" << endl;
//	// 直接把构造string参数包往下传，直接⽤string参数包构造string 
//	// 这⾥达到的效果是push_back做不到的 
//	lt.emplace_back("111111111111");
//	cout << "*********************************" << endl;
//	list<pair<bit::string, int>> lt1;
//	// 跟push_back⼀样 
//	// 构造pair + 拷⻉/移动构造pair到list的节点中data上 
//	pair<bit::string, int> kv("苹果", 1);
//	lt1.emplace_back(kv);
//	cout << "*********************************" << endl;
//	// 跟push_back⼀样 
//	lt1.emplace_back(move(kv));
//	cout << "*********************************" << endl;
//	////////////////////////////////////////////////////////////////////
//	// 直接把构造pair参数包往下传，直接⽤pair参数包构造pair 
//	// 这⾥达到的效果是push_back做不到的 
//	lt1.emplace_back("苹果", 1);
//	cout << "*********************************" << endl;
//	return 0;
//}
//// List.h
//namespace bit
//{
//	template<class T>
//	struct ListNode
//	{
//		ListNode<T>* _next;
//		ListNode<T>* _prev;
//		T _data;
//		ListNode(T&& data)
//			:_next(nullptr)
//			, _prev(nullptr)
//			, _data(move(data))
//		{
//		}
//		template <class... Args>
//		ListNode(Args&&... args)
//			: _next(nullptr)
//			, _prev(nullptr)
//			, _data(std::forward<Args>(args)...)
//		{
//		}
//	};
//	template<class T, class Ref, class Ptr>
//	struct ListIterator
//	{
//		typedef ListNode<T> Node;
//		typedef ListIterator<T, Ref, Ptr> Self;
//		Node* _node;
//		ListIterator(Node* node)
//			:_node(node)
//		{
//		}
//		// ++it;
//		Self& operator++()
//		{
//			_node = _node->_next;
//			return *this;
//		}
//		Self& operator--()
//		{
//			_node = _node->_prev;
//			return *this;
//		}
//		Ref operator*()
//		{
//			return _node->_data;
//		}
//		bool operator!=(const Self& it)
//		{
//			return _node != it._node;
//		}
//	};
//	template<class T>
//	class list
//	{
//		typedef ListNode<T> Node;
//	public:
//		typedef ListIterator<T, T&, T*> iterator;
//		typedef ListIterator<T, const T&, const T*> const_iterator;
//		iterator begin()
//		{
//			return iterator(_head->_next);
//		}
//		iterator end()
//		{
//			return iterator(_head);
//		}
//		void empty_init()
//		{
//			_head = new Node();
//			_head->_next = _head;
//			_head->_prev = _head;
//		}
//		list()
//		{
//			empty_init();
//		}
//		void push_back(const T& x)
//		{
//			insert(end(), x);
//		}
//		void push_back(T&& x)
//		{
//			insert(end(), move(x));
//		}
//		iterator insert(iterator pos, const T& x)
//		{
//			Node* cur = pos._node;
//			Node* newnode = new Node(x);
//			Node* prev = cur->_prev;
//			// prev newnode cur
//			prev->_next = newnode;
//			newnode->_prev = prev;
//			newnode->_next = cur;
//			cur->_prev = newnode;
//			return iterator(newnode);
//		}
//		iterator insert(iterator pos, T&& x)
//		{
//			Node* cur = pos._node;
//			Node* newnode = new Node(move(x));
//			Node* prev = cur->_prev;
//			// prev newnode cur
//			prev->_next = newnode;
//			newnode->_prev = prev;
//			newnode->_next = cur;
//			cur->_prev = newnode;
//			return iterator(newnode);
//		}
//		template <class... Args>
//		void emplace_back(Args&&... args)
//		{
//			insert(end(), std::forward<Args>(args)...);
//		}
//		// 原理：本质编译器根据可变参数模板⽣成对应参数的函数 
//		/*void emplace_back(string& s)
//		{
//		insert(end(), std::forward<string>(s));
//		}
//		void emplace_back(string&& s)
//		{
//		insert(end(), std::forward<string>(s));
//		}
//		void emplace_back(const char* s)
//		{
//		insert(end(), std::forward<const char*>(s));
//		}
//		*/
//		template <class... Args>
//		iterator insert(iterator pos, Args&&... args)
//		{
//			Node* cur = pos._node;
//			Node* newnode = new Node(std::forward<Args>(args)...);
//			Node* prev = cur->_prev;
//			// prev newnode cur
//			prev->_next = newnode;
//			newnode->_prev = prev;
//			newnode->_next = cur;
//			cur->_prev = newnode;
//			return iterator(newnode);
//		}
//	private:
//		Node* _head;
//	};
//}
//// Test.cpp
//#include"List.h"
//// emplace_back总体⽽⾔是更⾼效，推荐以后使⽤emplace系列替代insert和push系列 
//int main()
//{
//	bit::list<bit::string> lt;
//	// 传左值，跟push_back⼀样，⾛拷⻉构造 
//	bit::string s1("111111111111");
//	lt.emplace_back(s1);
//	cout << "*********************************" << endl;
//	// 右值，跟push_back⼀样，⾛移动构造 
//	lt.emplace_back(move(s1));
//	cout << "*********************************" << endl;
//	// 直接把构造string参数包往下传，直接⽤string参数包构造string 
//	// 这⾥达到的效果是push_back做不到的 
//	lt.emplace_back("111111111111");
//	cout << "*********************************" << endl;
//	bit::list<pair<bit::string, int>> lt1;
//	// 跟push_back⼀样 
//	// 构造pair + 拷⻉/移动构造pair到list的节点中data上 
//	pair<bit::string, int> kv("苹果", 1);
//	lt1.emplace_back(kv);
//	cout << "*********************************" << endl;
//	// 跟push_back⼀样 
//	lt1.emplace_back(move(kv));
//	cout << "*********************************" << endl;
//	////////////////////////////////////////////////////////////////////
//	// 直接把构造pair参数包往下传，直接⽤pair参数包构造pair 
//	// 这⾥达到的效果是push_back做不到的 
//	lt1.emplace_back("苹果", 1);
//	cout << "*********************************" << endl;
//	return 0;
//}

//class Person
//{
//public:
//	Person(const char* name = "", int age = 0)
//		:_name(name)
//		, _age(age)
//	{
//	}
//	/*Person(const Person& p)
//	:_name(p._name)
//	,_age(p._age)
//	{}*/
//	/*Person& operator=(const Person& p)
//	{
//	if(this != &p)
//	{
//	_name = p._name;
//	_age = p._age;
//	}
//	return *this;
//	}*/
//	/*~Person()
// {}*/
//private:
//	XiaoHai::string _name;
//	int _age;
//};
//int main()
//{
//	Person s1;
//	Person s2 = s1;
//	Person s3 = std::move(s1);
//	Person s4;
//	s4 = std::move(s2);
//	return 0;
//}

//class Person
//{
//public:
//	Person(const char* name = "", int age = 0)
//		:_name(name)
//		, _age(age)
//	{
//	}
//	Person(const Person& p)
//		:_name(p._name)
//		, _age(p._age)
//	{}
//	Person(Person&& p) = default;
//
//	//Person(const Person& p) = delete;
//private:
//	XiaoHai::string _name;
//	int _age;
//};
//int main()
//{
//	Person s1;
//	Person s2 = s1;
//	Person s3 = std::move(s1);
//	return 0;
//}

