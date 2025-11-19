#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//double Divide(int a, int b)
//{
//	try
//	{
//		// 当b == 0时抛出异常 
//		if (b == 0)
//		{
//			string s("Divide by zero condition!");
//			throw s;
//		}
//		else
//		{
//			return ((double)a / (double)b);
//		}
//	}
//	catch (int errid)
//	{
//		cout << errid << endl;
//	}
//	return 0;
//}
//void Func()
//{
//	int len, time;
//	cin >> len >> time;
//	try
//	{
//		cout << Divide(len, time) << endl;
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	cout << __FUNCTION__ << ":" << __LINE__ << "⾏执⾏" << endl;
//}
//int main()
//{
//	while (1)
//	{
//		try
//		{
//			Func();
//		}
//		catch (const string& errmsg)
//		{
//			cout << errmsg << endl;
//		}
//	}
//	return 0;
//}

#include<thread>
//// ⼀般⼤型项⽬程序才会使⽤异常，下⾯我们模拟设计⼀个服务的⼏个模块 
//// 每个模块的继承都是Exception的派⽣类，每个模块可以添加⾃⼰的数据 
//// 最后捕获时，我们捕获基类就可以 
//class Exception
//{
//public:
//	Exception(const string& errmsg, int id)
//		:_errmsg(errmsg)
//		, _id(id)
//	{
//	}
//	virtual string what() const
//	{
//		return _errmsg;
//	}
//	int getid() const
//	{
//		return _id;
//	}
//protected:
//	string _errmsg;
//	int _id;
//};
//class SqlException : public Exception
//{
//public:
//	SqlException(const string& errmsg, int id, const string& sql)
//		:Exception(errmsg, id)
//		, _sql(sql)
//	{
//	}
//	virtual string what() const
//	{
//		string str = "SqlException:";
//		str += _errmsg;
//		str += "->";
//		str += _sql;
//		return str;
//	}
//private:
//	const string _sql;
//};
//class CacheException : public Exception
//{
//public:
//	CacheException(const string& errmsg, int id)
//		:Exception(errmsg, id)
//	{
//	}
//	virtual string what() const
//	{
//		string str = "CacheException:";
//		str += _errmsg;
//		return str;
//	}
//};
//class HttpException : public Exception
//{
//public:
//	HttpException(const string& errmsg, int id, const string& type)
//		:Exception(errmsg, id)
//		, _type(type)
//	{
//	}
//	virtual string what() const
//	{
//		string str = "HttpException:";
//		str += _type;
//		str += ":";
//		str += _errmsg;
//		return str;
//	}
//private:
//	const string _type;
//};
//void SQLMgr()
//{
//	if (rand() % 7 == 0)
//	{
//		throw SqlException("权限不⾜", 100, "select * from name = '张三'");
//	}
//	else
//	{
//		cout << "SQLMgr 调⽤成功" << endl;
//	}
//}
//void CacheMgr()
//{
//	if (rand() % 5 == 0)
//	{
//		throw CacheException("权限不⾜", 100);
//	}
//	else if (rand() % 6 == 0)
//	{
//		throw CacheException("数据不存在", 101);
//	}
//	else
//	{
//		cout << "CacheMgr 调⽤成功" << endl;
//	}
//	SQLMgr();
//}
//void HttpServer()
//{
//	if (rand() % 3 == 0)
//	{
//		throw HttpException("请求资源不存在", 100, "get");
//	}
//	else if (rand() % 4 == 0)
//	{
//		throw HttpException("权限不⾜", 101, "post");
//	}
//	else
//	{
//		cout << "HttpServer调⽤成功" << endl;
//	}
//	CacheMgr();
//}
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
//		catch (const Exception& e) // 这⾥捕获基类，基类对象和派⽣类对象都可以被捕获
//		{
//		cout << e.what() << endl;
//		}
//			catch (...)
//		{
//			cout << "Unkown Exception" << endl;
//		}
//	}
//	return 0;
//}
//// 下⾯程序模拟展⽰了聊天时发送消息，发送失败补货异常，但是可能在 
//// 电梯地下室等场景⼿机信号不好，则需要多次尝试，如果多次尝试都发 
//// 送不出去，则就需要捕获异常再重新抛出，其次如果不是⽹络差导致的 
//// 错误，捕获后也要重新抛出。 
//void _SeedMsg(const string& s)
//{
//	if (rand() % 2 == 0)
//	{
//		throw HttpException("⽹络不稳定，发送失败", 102, "put");
//	}
//	else if (rand() % 7 == 0)
//	{
//		throw HttpException("你已经不是对象的好友，发送失败", 103, "put");
//	}
//	else
//	{
//		cout << "发送成功" << endl;
//	}
//}
//void SendMsg(const string& s)
//{
//	// 发送消息失败，则再重试3次 
//	for (size_t i = 0; i < 4; i++)
//	{
//		try
//		{
//			_SeedMsg(s);
//			break;
//		}
//		catch (const Exception& e)
//		{
//			// 捕获异常，if中是102号错误，⽹络不稳定，则重新发送 
//			// 捕获异常，else中不是102号错误，则将异常重新抛出 
//			if (e.getid() == 102)
//			{
//				// 重试三次以后否失败了，则说明⽹络太差了，重新抛出异常 
//				if (i == 3)
//					throw;
//				cout << "开始第" << i + 1 << "重试" << endl;
//			}
//			else
//			{
//				throw;
//			}
//		}
//	}
//}
//int main()
//{
//	srand(time(0));
//	string str;
//	while (cin >> str)
//	{
//		try
//		{
//			SendMsg(str);
//		}
//		catch (const Exception& e)
//		{
//			cout << e.what() << endl << endl;
//		}
//		catch (...)
//		{
//			cout << "Unkown Exception" << endl;
//		}
//	}
//	return 0;
//}
//double Divide(int a, int b)
//{
//	// 当b == 0时抛出异常 
//	if (b == 0)
//	{
//		throw "Division by zero condition!";
//	}
//	return (double)a / (double)b;
//}
//void Func()
//{
//	// 这⾥可以看到如果发⽣除0错误抛出异常，另外下⾯的array没有得到释放。 
//	// 所以这⾥捕获异常后并不处理异常，异常还是交给外层处理，这⾥捕获了再 
//	// 重新抛出去。 
//	int* array = new int[10];
//	try
//	{
//		int len, time;
//		cin >> len >> time;
//		cout << Divide(len, time) << endl;
//	}
//	catch (...)
//	{
//		// 捕获异常释放内存 
//		cout << "delete []" << array << endl;
//		delete[] array;
//		throw; // 异常重新抛出，捕获到什么抛出什么 
//	}
//	cout << "delete []" << array << endl;
//	delete[] array;
//}
//int main()
//{
//	try
//	{
//		Func();
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "Unkown Exception" << endl;
//	}
//	return 0;
//}

double Divide(int a, int b)
{
	// 当b == 0时抛出异常 
	if (b == 0)
	{
		throw "Divide by zero condition!";
	}
	else
	{
		return (double)a / (double)b;
	}
}
void Func()
{
	// 这⾥可以看到如果发⽣除0错误抛出异常，另外下⾯的array和array2没有得到释放。 
	// 所以这⾥捕获异常后并不处理异常，异常还是交给外⾯处理，这⾥捕获了再重新抛出去。 
	// 但是如果array2new的时候抛异常呢，就还需要套⼀层捕获释放逻辑，这⾥更好解决⽅案 
	// 是智能指针，否则代码太戳了 
	int* array1 = new int[10];
	int* array2 = new int[10]; // 抛异常呢 
	try
	{
		int len, time;
		cin >> len >> time;
		cout << Divide(len, time) << endl;
	}
	catch (...)
	{
		cout << "delete []" << array1 << endl;
		cout << "delete []" << array2 << endl;
		delete[] array1;
		delete[] array2;
		throw; // 异常重新抛出，捕获到什么抛出什么 
	}
	// ...
	cout << "delete []" << array1 << endl;
	delete[] array1;
	cout << "delete []" << array2 << endl;
	delete[] array2;
}
int main()
{
	try
	{
		Func();
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "未知异常" << endl;
	}
	return 0;
}

//template<class T>
//class SmartPtr
//{
//public:
//	// RAII
//	SmartPtr(T* ptr)
//		:_ptr(ptr)
//	{
//	}
//	~SmartPtr()
//	{
//		cout << "delete[] " << _ptr << endl;
//		delete[] _ptr;
//	}
//	// 重载运算符，模拟指针的⾏为，⽅便访问资源 
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//	T& operator[](size_t i)
//	{
//		return _ptr[i];
//	}
//private:
//	T* _ptr;
//};
//double Divide(int a, int b)
//{
//	// 当b == 0时抛出异常 
//	if (b == 0)
//	{
//		throw "Divide by zero condition!";
//	}
//	else
//	{
//		return (double)a / (double)b;
//	}
//}
//void Func()
//{
//	// 这⾥使⽤RAII的智能指针类管理new出来的数组以后，程序简单多了 
//	SmartPtr<int> sp1 = new int[10];
//	SmartPtr<int> sp2 = new int[10];
//
//	for (size_t i = 0; i < 10; i++)
//	{
//		sp1[i] = sp2[i] = i;
//	}
//	int len, time;
//	cin >> len >> time;
//	cout << Divide(len, time) << endl;
//}
//int main()
//{
//	try
//	{
//		Func();
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "未知异常" << endl;
//	}
//	return 0;
//}
