#define _CRT_SECURE_NO_WARNINGS 1
//1. 声明一个基类Animal，有私有整型成员变量age，构造其（公有继承）派生类dog，在其成员函数SetAge(int n)中直接给age赋值，
//看看会有什么问题，把age改为公有成员变量，还会有什么问题吗？编程试试看。
//2. 声明一个基类BaseClass，有整型成员变量Number，构造其派生类DerivedClass，观察构造函数和析构函数的执行情况。

#include<iostream>
using namespace std;

//class Animal
//{
//	public:
//		int age;
//private:
//	int _age;
//};
//
//class dog :public Animal
//{
//public:
//	void SetAge(int n)
//	{
//		_age = n;
//		age = n;
//	}
//};
//class BaseClass
//{
//public:
//	BaseClass()
//	{
//		cout << "BaseClass" << endl;
//	}
//	~BaseClass()
//	{
//		cout << "~BaseClass" << endl;
//	}
//private:
//	int Number;
//};
//class DerivedClass :public BaseClass
//{
//public:
//};
//3. 声明一个车（Vehicle）基类，具有MaxSpeed、Weight等成员变量，Run、Stop等成员函数，
//由此派生出自行车（bicycle）类、汽车(motorcar)类。自行车类有高度（Height）等属性，汽车类有座位数(SeatNum) 等属性。
//从bicycle和motorcar派生出摩托车(motorcycle)类，在继承过程中，注意把vehicle设置为虚基类。如果不把vehicle设置为虚基类，
//会有什么问题？编程试试看。
class Vehicl
{
public:
	int MaxSpeed =1;
	int Weight=2;
	void Run()
	{
		cout << "Run()" << endl;
	}
	void Stop()
	{
		cout << "Stop()" << endl;
	}
};
class bicycle :virtual public Vehicl
{
	int Height = 3;
};
class motorcar :virtual public Vehicl
{
	int SeatNum =4;
};
class motorcycle :public bicycle, public motorcar
{

};
int main()
{
	Vehicl v;
	bicycle b;
	motorcar m;
	motorcycle m1;
	cout << v.Weight << endl;
	v.Run();
	cout << b.Weight << endl;
	b.Run();
	cout << m.Weight << endl;
	m.Run();
	cout << m1.Weight << endl;

	return 0;
}