#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
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
//	cout << &c << endl;
//	cout << (void*)&s[0] << endl;
//	// 右值：不能取地址 
//	double x = 1.1, y = 2.2;
//	// 以下⼏个10、x + y、fmin(x, y)、string("11111")都是常⻅的右值 
//	10;
//	x + y;
//	fmin(x, y);
//	string("11111");
//	//cout << &10 << endl;
//	//cout << &(x+y) << endl;
//	//cout << &(fmin(x, y)) << endl; 
//	//cout << &string("11111") << endl;
//	return 0;
//}

struct Point
{
	int _x;
	int _y;
};
class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int year, int month, int day)" << endl;
	}
	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date& d)" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
// ⼀切皆可⽤列表初始化，且可以不加= 
//int main()
//{
//	// C++98⽀持的 
//	int a1[] = { 1, 2, 3, 4, 5 };
//	int a2[5] = { 0 };
//	Point p = { 1, 2 };
//	// C++11⽀持的 
//	// 内置类型⽀持 
//	int x1 = { 2 };
//	// ⾃定义类型⽀持 
//	// 这⾥本质是⽤{ 2025, 1, 1}构造⼀个Date临时对象 
//	// 临时对象再去拷⻉构造d1，编译器优化后合⼆为⼀变成{ 2025, 1, 1}直接构造初始化d1
//		// 运⾏⼀下，我们可以验证上⾯的理论，发现是没调⽤拷⻉构造的 
//		Date d1 = { 2025, 1, 1 };
//	// 这⾥d2引⽤的是{ 2024, 7, 25 }构造的临时对象 
//	const Date& d2 = { 2024, 7, 25 };
//	// 需要注意的是C++98⽀持单参数时类型转换，也可以不⽤{} 
//	Date d3 = { 2025 };
//	Date d4 = 2025;
//	// 可以省略掉= 
//	Point p1{ 1, 2 };
//	int x2{ 2 };
//	Date d6{ 2024, 7, 25 };
//	const Date& d7{ 2024, 7, 25 };
//	// 不⽀持，只有{}初始化，才能省略= 
//	// Date d8 2025;
//	vector<Date> v;
//	v.push_back(d1);
//	v.push_back(Date(2025, 1, 1));
//	// ⽐起有名对象和匿名对象传参，这⾥{}更有性价⽐ 
//	v.push_back({ 2025, 1, 1 });
//	return 0;
//}

//int main()
//{
//	string s = "abcde";
//	for (auto& e : s)
//	{
//		e += 1;
//	}
//	for (auto& e : s)
//	{
//		cout << e << " ";
//	}
//	return 0;
//}
//
//// 由于引⽤折叠限定，f1实例化以后总是⼀个左值引⽤ 
//template<class T>
//void f1(T& x)
//{
//
//}
//// 由于引⽤折叠限定，f2实例化后可以是左值引⽤，也可以是右值引⽤ 
//// 万能引用
//template<class T>
//void f2(T&& x)
//{
//}
//int main()
//{
//	typedef int& lref;
//	typedef int&& rref;
//	int n = 0;
//	lref& r1 = n; // r1 的类型是 int& 
//	lref&& r2 = n; // r2 的类型是 int& 
//	rref& r3 = n; // r3 的类型是 int& 
//	rref&& r4 = 1; // r4 的类型是 int&& 
//	// 没有折叠->实例化为void f1(int& x) 
//	f1<int>(n);
//	f1<int>(0); // 报错 
//
//	// 折叠->实例化为void f1(int& x)
//	f1<int&>(n);
//	f1<int&>(0); // 报错 
//
//	// 折叠->实例化为void f1(int& x) 
//	f1<int&&>(n);
//	f1<int&&>(0); // 报错 左值引用
//
//	// 折叠->实例化为void f1(const int& x) 
//	f1<const int&>(n);
//	f1<const int&>(0);
//
//	// 折叠->实例化为void f1(const int& x) 
//	f1<const int&&>(n);
//	f1<const int&&>(0);
//
//	// 没有折叠->实例化为void f2(int&& x) 
//	f2<int>(n); // 报错 
//	f2<int>(0);
//	// 折叠->实例化为void f2(int& x) 
//	f2<int&>(n);
//	f2<int&>(0); // 报错 
//	// 折叠->实例化为void f2(int&& x) 
//	f2<int&&>(n); // 报错 
//	f2<int&&>(0);
//	return 0;
//}

// 万能引用，实例化后可以是左值引⽤，也可以是右值引⽤ 
// 传左值就实例化左值引用的函数，传右值就实例化右值引用的函数
//template<class T>
//void Function(T&& t)
//{
//	int a = 0;
//	T x = a;
//	//x++;
//	cout << &a << endl;
//	cout << &x << endl << endl;
//}
//int main()
//{
//	// 10是右值，推导出T为int，模板实例化为void Function(int&& t) 
//	Function(10); // 右值 
//	int a;
//	// a是左值，推导出T为int&，引⽤折叠，模板实例化为void Function(int& t) 
//	Function(a); // 左值 
//	// std::move(a)是右值，推导出T为int，模板实例化为void Function(int&& t) 
//	Function(std::move(a)); // 右值 
//	const int b = 8;
//	// a是左值，推导出T为const int&，引⽤折叠，模板实例化为void Function(const int& t)
//	// 所以Function内部会编译报错，x不能++ 
//	Function(b); // const 左值 
//	// std::move(b)右值，推导出T为const int，模板实例化为void Function(const int&& t)
//	   // 所以Function内部会编译报错，x不能++ 
//	Function(std::move(b)); // const 右值 
//	return 0;
//}
//
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
//template <class T, class ...Args>
//void ShowList(T x, Args... args)
//{
// cout << x << " ";
// Print(args...);
//}
// Print(1, string("xxxxx"), 2.2);调⽤时 
// 本质编译器将可变参数模板通过模式的包扩展，编译器推导的以下三个重载函数函数 
//void ShowList(double x)
//{
// cout << x << " ";
// ShowList();
//}
//
//void ShowList(string x, double z)
//{
// cout << x << " ";
// ShowList(z);
//}
//
//void ShowList(int x, string y, double z)
//{
// cout << x << " ";
// ShowList(y, z);
//}
//void Print(int x, string y, double z)
//{
// ShowList(x, y, z);
//}

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
//	list<XiaoHai::string> lt;
//	// 传左值，跟push_back⼀样，⾛拷⻉构造 
//	XiaoHai::string s1("111111111111");
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

// List.h
namespace bit
{
	template<class T>
	struct ListNode
	{
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _data;
		ListNode(T&& data)
			:_next(nullptr)
			, _prev(nullptr)
			, _data(move(data))
		{
		}
		template <class... Args>
		ListNode(Args&&... args)
			: _next(nullptr)
			, _prev(nullptr)
			, _data(std::forward<Args>(args)...)
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
		// ++it;
		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		Self& operator--()
		{
			_node = _node->_prev;
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
		template <class... Args>
		void emplace_back(Args&&... args)
		{
			insert(end(), std::forward<Args>(args)...);
		}
		// 原理：本质编译器根据可变参数模板⽣成对应参数的函数 
		/*void emplace_back(string& s)
		{
		insert(end(), std::forward<string>(s));
		}
		void emplace_back(string&& s)
		{
		insert(end(), std::forward<string>(s));
		}
		void emplace_back(const char* s)
		{
		insert(end(), std::forward<const char*>(s));
		}
		*/
		template <class... Args>
		iterator insert(iterator pos, Args&&... args)
		{
			Node* cur = pos._node;
			Node* newnode = new Node(std::forward<Args>(args)...);
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
//int main() { // ⼀个简单的lambda表达式
//	auto add1 = [](int x, int y)->int {return x + y; };
//	cout << add1(1, 2) << endl;
//	// 1、捕捉为空也不能省略 
//	// 2、参数为空可以省略 
//	// 3、返回值可以省略，可以通过返回对象⾃动推导 
//	// 4、函数题不能省略 
//	auto func1 = []
//		{
//			cout << "hello bit" << endl;
//			return 0;
//		};
//	func1();
//	int a = 0, b = 1;
//	auto swap1 = [](int& x, int& y)
//		{
//			int tmp = x;
//			x = y;
//			y = tmp;
//		};
//	swap1(a, b);
//	cout << a << ":" << b << endl;
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
//	{
//	}
//	Person(Person&& p) = default;
//
//	//Person(const Person& p) = delete;
//private:
//	Xiaohai::string _name;
//	int _age;
//};
//int main()
//{
//	Person s1;
//	Person s2 = s1;
//	Person s3 = std::move(s1);
//	return 0;
//}

//class Example {
//public:
//	Example(int a, int b)
//		:_x(a)
//		,_y(b)
//	{
//		cout << "目标构造函数"<<endl;
//	}
//	Example(int a)
//		:Example(a, 0)
//	{
//		cout << "委托构造" << endl;
//	}
//	int _x;
//	int _y;
//};

//int main()
//{
//	Example(1, 2);
//	Example(1);
//}

//适用于：
//1.没有成员变量的派生类
//2.成员变量都有缺省值，并且我们就想用这个缺省值初始化
class Base {
public:
	Base(int x, double d)
		:_x(x)
		,_d(d)
	{ }
	Base(int x)
		:_x(x)
	{ }
	Base(double d)
		:_x(d)
	{ }
private:
	int _x;
	double _d;
};

//传统继承
class Derive :public Base {
public:
	Derive(int x) :Base(x) {}
	Derive(double d) :Base(d) {}
	Derive(int x,double d):Base(x,d){}
};

//继承构造
class Derive :public Base {
public:
	using Base::Base;

//protected:
//	int _i = 0;
//	string s;

};

int main()
{
	//Derive d;
	Derive d1(1);
	Derive d2(1.1);
	Derive d3(2,2.2);
	return 0;
}
