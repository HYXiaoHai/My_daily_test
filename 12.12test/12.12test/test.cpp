#define _CRT_SECURE_NO_WARNINGS 1
//声明 Point类，有坐标_x，_y 两个成员变量；对Point 类重载“++”（自增）“--”（自减）运算符，
//实现对坐标值的改变。包括前置和后置。

//声明一个车(vehicle)基类，有 Run、Stop 等成员函数，由此派生出自行车（bicycle），汽车（motorcar）类，
//从 bicycle 和 motorcar 派生出摩托车（motorcycle））类，它们都有Run、Stop 等成员函数。观察虚函数作用。
#include<iostream>
using namespace std;

class Vehicle
{
public:
	virtual void Stop()
	{
		cout << "vehicle:Stop" << endl;
	}
	void Run()
	{
		cout << "vehicle:Run" << endl;

	}
};
class Bicycle :Vehicle
{
public:

	void Stop()override
	{
		cout << "bicycles:Stop" << endl;
	}
	void Run()
	{
		cout << "bicycles:Run" << endl;

	}
};
class Motorcar :Vehicle
{
public:

	void Stop()override
	{
		cout << "motorcar:Stop" << endl;
	}
	void Run()
	{
		cout << "motorcar:Run" << endl;

	}
};
class Motorcycle :public Bicycle, public Motorcar
{
public:

	void Stop()override
	{
		cout << "motorcycle:Stop" << endl;
	}
	void Run()
	{
		cout << "motorcycle:Run" << endl;
	}
};

class Point
{
public:
	int _x;
	int _y;

	Point(int x = 0, int y = 0) : _x(x), _y(y) {}
	Point& operator++(int)
	{
		Point tmp(_x, _y);
		_x++;
		_y++;
		return tmp;
	}
	Point& operator++()
	{
		_x++;
		_y++;
		return *this;
	}
	Point& operator--() 
	{
		--_x;
		--_y;
		return *this;
	}

	Point operator--(int)
	{
		Point temp = *this;
		--_x;
		--_y;
		return temp;
	}
	void show()
	{
		cout << _x << " " << _y << endl;
	}
};

void test01()
{
	Point p1(10, 20);
	cout << "原始点: ";
	p1.show();

	// 测试前置++
	++p1;
	cout << "前置++后: ";
	p1.show();

	// 测试后置++
	Point p2 = p1++;
	cout << "后置++返回的点: ";
	p2.show();
	cout << "后置++后的点: ";
	p1.show();

	// 测试前置--
	--p1;
	cout << "前置--后: ";
	p1.show();

	// 测试后置--
	Point p3 = p1--;
	cout << "后置--返回的点: ";
	p3.show();
	cout << "后置--后的点: ";
	p1.show();

}

void test02()
{

	Vehicle vehicle;
	Bicycle bicycle;
	Motorcar car;
	Motorcycle motorcycle;

	cout << "Vehicle: ";
	vehicle.Run();
	vehicle.Stop();

	cout << "\nBicycle: ";
	bicycle.Run();
	bicycle.Stop();

	cout << "\nCar: ";
	car.Run();
	car.Stop();

	cout << "\nMotorcycle: ";
	motorcycle.Run();
	motorcycle.Stop();


	Vehicle* ptr;

	ptr = &vehicle;
	cout << "Vehicle指针指向Vehicle对象: ";
	ptr->Run();
	ptr->Stop();
}


int main()
{
	//test01();
	test02();
	return 0;
}