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

int main()
{
	string s = "abcde";
	for (auto& e : s)
	{
		e += 1;
	}
	for (auto& e : s)
	{
		cout << e << " ";
	}
	return 0;
}

// 由于引⽤折叠限定，f1实例化以后总是⼀个左值引⽤ 
template<class T>
void f1(T& x)
{

}
// 由于引⽤折叠限定，f2实例化后可以是左值引⽤，也可以是右值引⽤ 
// 万能引用
template<class T>
void f2(T&& x)
{
}
int main()
{
	typedef int& lref;
	typedef int&& rref;
	int n = 0;
	lref& r1 = n; // r1 的类型是 int& 
	lref&& r2 = n; // r2 的类型是 int& 
	rref& r3 = n; // r3 的类型是 int& 
	rref&& r4 = 1; // r4 的类型是 int&& 
	// 没有折叠->实例化为void f1(int& x) 
	f1<int>(n);
	f1<int>(0); // 报错 

	// 折叠->实例化为void f1(int& x)
	f1<int&>(n);
	f1<int&>(0); // 报错 

	// 折叠->实例化为void f1(int& x) 
	f1<int&&>(n);
	f1<int&&>(0); // 报错 左值引用

	// 折叠->实例化为void f1(const int& x) 
	f1<const int&>(n);
	f1<const int&>(0);

	// 折叠->实例化为void f1(const int& x) 
	f1<const int&&>(n);
	f1<const int&&>(0);

	// 没有折叠->实例化为void f2(int&& x) 
	f2<int>(n); // 报错 
	f2<int>(0);
	// 折叠->实例化为void f2(int& x) 
	f2<int&>(n);
	f2<int&>(0); // 报错 
	// 折叠->实例化为void f2(int&& x) 
	f2<int&&>(n); // 报错 
	f2<int&&>(0);
	return 0;
}

// 万能引用，实例化后可以是左值引⽤，也可以是右值引⽤ 
// 传左值就实例化左值引用的函数，传右值就实例化右值引用的函数
template<class T>
void Function(T&& t)
{
	int a = 0;
	T x = a;
	//x++;
	cout << &a << endl;
	cout << &x << endl << endl;
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
	// a是左值，推导出T为const int&，引⽤折叠，模板实例化为void Function(const int& t)
	// 所以Function内部会编译报错，x不能++ 
	Function(b); // const 左值 
	// std::move(b)右值，推导出T为const int，模板实例化为void Function(const int&& t)
	   // 所以Function内部会编译报错，x不能++ 
	Function(std::move(b)); // const 右值 
	return 0;
}