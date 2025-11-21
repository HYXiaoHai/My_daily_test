#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<functional>
using namespace std;
//namespace XiaoHai
//{
//	template<class T>
//	class auto_ptr
//	{
//	public:
//		auto_ptr(T* ptr)
//			:_ptr(ptr)
//		{ }
//		auto_ptr(auto_ptr<T>&ap)
//			:_ptr(ap._ptr)
//		{
//			ap._ptr = nullptr;
//		}
//		auto_ptr<T>& operator = (auto_ptr<T>& ap)
//		{
//			if (*this != &ap)
//			{
//				if (_ptr)
//				{
//					delete _ptr;
//				}
//				_ptr = ap._ptr;
//				ap._ptr = nullptr;
//			}
//			return *this;
//		}
//		~auto_ptr()
//		{
//			if (_ptr)
//			{
//				delete _ptr;
//			}
//		}
//		T& operator*()
//		{
//			return *ptr;
//		}
//		T* operator()
//		{
//			return _ptr;
//		}
//	private:
//		T* _ptr;
//	};
//
//	template<class T>
//	class unique_ptr
//	{
//	public:
//		explicit unique_ptr(T&ptr)
//			:_ptr(ptr)
//		{
//		}
//		explicit unique_ptr(T* ptr)
//			:_ptr(ptr)
//		{
//		}
//		~unique_ptr()
//		{
//			if (_ptr)
//			{
//				cout << "delete:" << _ptr << endl;
//				delete _ptr;
//			}
//		}
//		// 像指针⼀样使⽤ 
//		T& operator*()
//		{
//			return *_ptr;
//		}
//		T* operator->()
//		{
//			return _ptr;
//		}
//		unique_ptr(const unique_ptr<T>& sp) = delete;
//		unique_ptr<T>& operator=(const unique_ptr<T>& sp) = delete;
//		unique_ptr(unique_ptr<T>&& sp)
//			:_ptr(sp._ptr)
//		{
//			sp._ptr = nullptr;
//		}
//		unique_ptr<T>& operator=(unique_ptr<T>&& sp)
//		{
//			delete _ptr;
//			_ptr = sp._ptr;
//			sp._ptr = nullptr;
//		}
//	private:
//		T* _ptr;
//	};
//
//	template<class T>
//	class shared_ptr
//	{
//	public:
//		shared_ptr(T*ptr)
//			:_ptr(ptr)
//			,_pcount(new int(1))
//		{
//
//		}
//		template<class D>
//		shared_ptr(T* ptr, D del)
//			: _ptr(ptr)
//			, _pcount(new int(1))
//			, _del(del)
//		{
//
//		}
//		shared_ptr(const shared_ptr<T>&sp)
//			:_ptr(sp._ptr)
//			,_pcount(sp._pcount)
//			,_del(sp._del)
//		{
//			++(*_pcount);
//		}
//		void release()
//		{
//			if (--(*_pcount) == 0)
//			{
//				_del(_ptr);
//				delete _pcount;
//				_ptr = nullptr;
//				_pcount = nullptr;
//			}
//		}
//		shared_ptr<T>& operator=(const shared_ptr<T>&sp)
//		{
//			if (_ptr != sp._ptr)
//			{
//				release();
//				_ptr = sp._ptr;
//				_pcount = sp._pcount;
//				++(*_pcount);
//				_del = sp._del;
//
//			}
//		}
//		~shared_ptr()
//		{
//			release();
//		}
//
//		T& operator*()
//		{
//			return *_ptr;
//		}
//		T* operator->()
//		{
//			return _ptr;
//		}
//
//	private:
//		T* _ptr;
//		int* _pcount;
//		function<void(T*)>_del = [](T* ptr) {delete ptr; };
//	};
//}

//double Func(int a, int b)
//{
//	if (b == 0)
//	{
//		int b = 1;
//		throw b;
//	}
//	return (double)a / (double)b;
//}
//void Funb()
//{
//	int* arry = new int[10];
//	int len, high;
//	cin >> len>> high;
//	try
//	{
//		Func(len, high);
//	}
//	catch (int a)
//	{
//		cout << a;
//	}
//}
//
//int main()
//{
//	try
//	{
//		Funb();
//	}
//	//catch (string erro)
//	//{
//	//	cout << erro << endl;
//	//}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "666" << endl;
//	}
//}

#include<thread>
// ⼀般⼤型项⽬程序才会使⽤异常，下⾯我们模拟设计⼀个服务的⼏个模块 
// 每个模块的继承都是Exception的派⽣类，每个模块可以添加⾃⼰的数据 
// 最后捕获时，我们捕获基类就可以 
class Ex
{
public:
	Ex(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{
	}
	virtual string what() const
	{
		return _errmsg;
	}
	int getid() const
	{
		return _id;
	}
protected:
	string _errmsg;
	int _id;
};
class SqlException : public Ex
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Ex(errmsg, id)
		, _sql(sql)
	{
	}
	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;
		return str;
	}
private:
	const string _sql;
};
class CacheException : public Ex
{
public:
	CacheException(const string& errmsg, int id)
		:Ex(errmsg, id)
	{
	}
	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};
class HttpException : public Ex
{
public:
	HttpException(const string& errmsg, int id, const string& type)
		:Ex(errmsg, id)
		, _type(type)
	{
	}
	virtual string what() const
	{
		string str = "HttpException:";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
private:
	const string _type;
};
void SQLMgr()
{
	if (rand() % 7 == 0)
	{
		throw SqlException("权限不⾜", 100, "select * from name = '张三'");
	}
	else
	{
		cout << "SQLMgr 调⽤成功" << endl;
	}
}
void CacheMgr()
{
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不⾜", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 101);
	}
	else
	{
		cout << "CacheMgr 调⽤成功" << endl;
	}
	SQLMgr();
}
void HttpServer()
{
	if (rand() % 3 == 0)
	{
		throw HttpException("请求资源不存在", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpException("权限不⾜", 101, "post");
	}
	else
	{
		cout << "HttpServer调⽤成功" << endl;
	}
	CacheMgr();
}
//int main()
//{
//	srand(time(0));
//	while (1)
//	{
//		this_thread::sleep_for(chrono::seconds(1));
//		try
//		{
//			HttpServer();
//		}
//		catch (const Ex& e) // 这⾥捕获基类，基类对象和派⽣类对象都可以被捕获
//		{
//			cout << e.what() << endl;
//		}
//		catch (...)
//		{
//			cout << "Unkown Exception" << endl;
//		}
//	}
//	return 0;
//}
//int main()
//{
//	// ⼀个简单的lambda表达式 
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

//int x = 0;
//// 捕捉列表必须为空，因为全局变量不⽤捕捉就可以⽤，没有可被捕捉的变量 
//auto func1 = []()
//	{
//		x++;
//	};
//int main()
//{
//	// 只能⽤当前lambda局部域和捕捉的对象和全局对象 
//	int a = 0, b = 1, c = 2, d = 3;
//	auto func1 = [a, &b]
//		{
//			// 值捕捉的变量不能修改，引⽤捕捉的变量可以修改 
//			//a++;
//			b++;
//			int ret = a + b;
//			return ret;
//		};
//	cout << func1() << endl;
//	// 隐式值捕捉 
//	// ⽤了哪些变量就捕捉哪些变量 
//	auto func2 = [=]
//		{
//			int ret = a + b + c;
//			return ret;
//		};
//	cout << func2() << endl;
//	// 隐式引⽤捕捉 
//	// ⽤了哪些变量就捕捉哪些变量 
//	auto func3 = [&]
//		{
//			a++;
//			c++;
//			d++;
//		};
//	func3();
//	cout << a << " " << b << " " << c << " " << d << endl;
//	// 混合捕捉1 
//	auto func4 = [&, a, b]
//		{
//			//a++;
//			//b++;
//			c++;
//			d++;
//			return a + b + c + d;
//		};
//	func4();
//	cout << a << " " << b << " " << c << " " << d << endl;
//	// 混合捕捉1 
//	auto func5 = [=, &a, &b]
//		{
//			a++;
//			b++;
//			/*c++;
//			d++;*/
//			return a + b + c + d;
//		};
//	func5();
//	cout << a << " " << b << " " << c << " " << d << endl;
//	// 局部的静态和全局变量不能捕捉，也不需要捕捉 
//	static int m = 0;
//	auto func6 = []
//		{
//			int ret = x + m;
//			return ret;
//		};
//	// 传值捕捉本质是⼀种拷⻉,并且被const修饰了 
//	// mutable相当于去掉const属性，可以修改了 
//	// 但是修改了不会影响外⾯被捕捉的值，因为是⼀种拷⻉ 
//	auto func7 = [=]()mutable
//		{
//			a++;
//			b++;
//			c++;
//			d++;
//			return a + b + c + d;
//		};
//	cout << func7() << endl;
//	cout << a << " " << b << " " << c << " " << d << endl;
//	return 0;
//}

//struct Goods
//{
//	string _name; // 名字 
//	double _price; // 价格 
//	int _evaluate; // 评价 
//	// ...
//	Goods(const char* str, double price, int evaluate)
//		:_name(str)
//		, _price(price)
//		, _evaluate(evaluate)
//	{
//	}
//};
//struct ComparePriceLess
//{
//	bool operator()(const Goods& gl, const Goods& gr)
//	{
//		return gl._price < gr._price;
//	}
//};
//struct ComparePriceGreater
//{
//	bool operator()(const Goods& gl, const Goods& gr)
//	{
//		return gl._price > gr._price;
//	}
//};
//int main()
//{
//	vector<Goods> v = { { "苹果", 2.1, 5 }, { "⾹蕉", 3, 4 }, { "橙⼦", 2.2, 3
//   }, { "菠萝", 1.5, 4 } };
//	// 类似这样的场景，我们实现仿函数对象或者函数指针⽀持商品中 
//	// 不同项的⽐较，相对还是⽐较⿇烦的，那么这⾥lambda就很好⽤了 
//	sort(v.begin(), v.end(), ComparePriceLess());
//	sort(v.begin(), v.end(), ComparePriceGreater());
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
//		return g1._price < g2._price;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
//		return g1._price > g2._price;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
//		return g1._evaluate < g2._evaluate;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) {
//		return g1._evaluate > g2._evaluate;
//		});
//	return 0;
//}

//class Rate
//{
//public:
//	Rate(double rate)
//		: _rate(rate)
//	{
//	}
//	double operator()(double money, int year)
//	{
//		return money * _rate * year;
//	}
//private:
//	double _rate;
//};
//int main()
//{
//	double rate = 0.49;
//	// lambda
//	auto r2 = [rate](double money, int year) {
//		return money * rate * year;
//		};
//	// 函数对象 
//	Rate r1(rate);
//	r1(10000, 2);
//	r2(10000, 2);
//	auto func1 = [] {
//		cout << "hello world" << endl;
//		};
//	func1();
//	return 0;
//}
// lambda
//#include<functional>
//int f(int a, int b)
//{
//	return a + b;
//}
//struct Functor
//{
//public:
//	int operator() (int a, int b)
//	{
//		return a + b;
//	}
//};
//class Plus
//{
//public:
//	Plus(int n = 10)
//		:_n(n)
//	{
//	}
//	static int plusi(int a, int b)
//	{
//		return a + b;
//	}
//	double plusd(double a, double b)
//	{
//		return (a + b) * _n;
//	}
//private:
//	int _n;
//};
//int main()
//{
//	// 包装各种可调⽤对象 
//	function<int(int, int)> f1 = f;
//	function<int(int, int)> f2 = Functor();
//	function<int(int, int)> f3 = [](int a, int b) {return a + b; };
//	cout << f1(1, 1) << endl;
//	cout << f2(1, 1) << endl;
//	cout << f3(1, 1) << endl;
//	// 包装静态成员函数 
//	// 成员函数要指定类域并且前⾯加&才能获取地址 
//	function<int(int, int)> f4 = &Plus::plusi;
//	cout << f4(1, 1) << endl;
//	// 包装普通成员函数 
//	// 普通成员函数还有⼀个隐含的this指针参数，所以绑定时传对象或者对象的指针过去都可以 
//	function<double(Plus*, double, double)> f5 = &Plus::plusd;
//	Plus pd;
//	cout << f5(&pd, 1.1, 1.1) << endl;
//	function<double(Plus, double, double)> f6 = &Plus::plusd;
//	cout << f6(pd, 1.1, 1.1) << endl;
//	cout << f6(pd, 1.1, 1.1) << endl;
//	function<double(Plus&&, double, double)> f7 = &Plus::plusd;
//	cout << f7(move(pd), 1.1, 1.1) << endl;
//	cout << f7(Plus(), 1.1, 1.1) << endl;
//	return 0;
//}
//class Solution {
//public:
//	int evalRPN(vector<string>& tokens) {
//		stack<int>s;
//		int left = 0;
//		int right = 0;
//		for (auto e : tokens)
//		{
//			if (e == "+" || e == "-" || e == "*" || e == "/")
//			{
//				right = s.top();
//				s.pop();
//				left = s.top();
//				s.pop();
//				switch (e[0])
//				{
//				case '+':s.push(left + right);
//					break;
//				case '-':s.push(left - right);
//					break;
//				case '*':s.push(left * right);
//					break;
//				case '/':s.push(left / right);
//					break;
//				default: break;
//
//				}
//			}
//			else
//			{
//				s.push(stoi(e));
//			}
//		}
//		return s.top();
//
//
//	}
//};

#include<functional>
using placeholders::_1;
using placeholders::_2;
using placeholders::_3;
int Sub(int a, int b)
{
	return (a - b) * 10;
}
int SubX(int a, int b, int c)
{
	return (a - b - c) * 10;
}
class Plus
{
public:
	static int plusi(int a, int b)
	{
		return a + b;
	}
	double plusd(double a, double b)
	{
		return a + b;
	}
};
int main()
{
	auto sub1 = bind(Sub, _1, _2);
	cout << sub1(10, 5) << endl;
	// bind 本质返回的⼀个仿函数对象 
	// 调整参数顺序（不常⽤） 
	// _1代表第⼀个实参 
	// _2代表第⼆个实参 
	// ...
	auto sub2 = bind(Sub, _2, _1);
	cout << sub2(10, 5) << endl;
	// 调整参数个数 （常⽤） 
	auto sub3 = bind(Sub, 100, _1);
	cout << sub3(5) << endl;
	auto sub4 = bind(Sub, _1, 100);
	cout << sub4(5) << endl;
	// 分别绑死第123个参数 
	auto sub5 = bind(SubX, 100, _1, _2);
	auto sub51 = bind(SubX, 100, _2, _1);
	cout << sub5(5, 1) << endl;
	cout << sub51(5, 1) << endl;
	cout << "--------------------------" << endl;
	auto sub6 = bind(SubX, _1, 100, _2);
	auto sub61 = bind(SubX, _2, 100, _1);
	cout << sub6(5, 1) << endl;
	cout << sub61(5, 1) << endl;
	cout << "--------------------------" << endl;

	auto sub7 = bind(SubX, _1, _2, 100);
	cout << sub7(5, 1) << endl;
	//// 成员函数对象进⾏绑死，就不需要每次都传递了 
	//function<double(Plus&&, double, double)> f6 = &Plus::plusd;
	//Plus pd;
	//cout << f6(move(pd), 1.1, 1.1) << endl;
	//cout << f6(Plus(), 1.1, 1.1) << endl;
	//// bind⼀般⽤于，绑死⼀些固定参数 
	//function<double(double, double)> f7 = bind(&Plus::plusd, Plus(), _1, _2);
	//cout << f7(1.1, 1.1) << endl;
	//// 计算复利的lambda 
	//auto func1 = [](double rate, double money, int year)->double {
	//	double ret = money;
	//	for (int i = 0; i < year; i++)
	//	{
	//		ret += ret * rate;
	//	}
	//	return ret - money;
	//	};
	//// 绑死⼀些参数，实现出⽀持不同年华利率，不同⾦额和不同年份计算出复利的结算利息 
	//function<double(double)> func3_1_5 = bind(func1, 0.015, _1, 3);
	//function<double(double)> func5_1_5 = bind(func1, 0.015, _1, 5);
	//function<double(double)> func10_2_5 = bind(func1, 0.025, _1, 10);
	//function<double(double)> func20_3_5 = bind(func1, 0.035, _1, 30);
	//cout << func3_1_5(1000000) << endl;
	//cout << func5_1_5(1000000) << endl;
	//cout << func10_2_5(1000000) << endl;
	//cout << func20_3_5(1000000) << endl;
	return 0;
}

