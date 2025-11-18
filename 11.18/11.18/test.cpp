#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
////struct Goods
////{
////	int _price;
////	int _evaluate;
////};
////auto priceLess = [](const Goods& gl, const Goods& gr)
////	{
////		return gl._price < gr._price;
////	};
#include<functional>
////int main()
////{
////	function<int(int, int)>f1 = [](int a, int b) {return a + b; };
////	function<int(int, int,int)>f2 = [](int a, int b,int c) {return a *(b+c); };
////	cout << f1(1, 1) << endl;
////	cout << f2(1,2,3) << endl;
////	return 0;
////}
////   0 1 2 3 4 5
//// 0
//// 1
//// 2
//// 3
//// 4
//// 5
//int num1(int i,int j,int m,int n)
//{
//	int pwm = i*n;
//	pwm += j;
//	return pwm;
//}
//int num2(int i,int j,int m,int n)
//{
//	int pwm = j*m;
//	pwm += i;
//	return pwm;
//}
//int main() {
//    int m = 3, n = 4;
//    int arr[3][4];
//    int num = 0;
//    cout << "行优先存储顺序：" << endl;
//    for (int i=0;i<m;i++)
//    {
//        for (int j = 0; j < n; j++)
//        {
//            arr[i][j] = num;
//            num++;
//        }
//    }
//    for (int i = 0; i < m; i++)
//    {
//        for (int j = 0; j < n; j++)
//        {
//            cout << arr[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//    // 测试几个特定位置
//    cout << "测试结果：" << endl;
//    cout << "测试位置:0,0:" << num1(0, 0, m, n) << endl;
//    cout << "测试位置:3,4:" << num1(3, 4, m, n) << endl;
//    cout << "测试位置:2,3:" << num1(2, 3, m, n) << endl;
//    cout << "测试位置:1,3:" << num1(1, 3, m, n) << endl;
//    cout << "测试位置:2,0:" << num1(2, 0, m, n) << endl;
//    cout << "测试位置:0,2:" << num1(0, 2, m, n) << endl;
//    cout << "------------------------------------------------" << endl;
//
//
//    cout << "列优先存储顺序：" << endl;
//    num = 0;
//    for (int j = 0; j < n; j++) {
//        for (int i = 0; i < m; i++) {
//            arr[i][j] = num;
//            num++;
//        }
//    }
//    for (int i = 0; i < m; i++)
//    {
//        for (int j = 0; j < n; j++)
//        {
//            cout << arr[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//    // 测试几个特定位置
//    cout << "测试结果：" << endl;
//    cout << "测试位置:0,0:"<<num1(0, 0, m, n) << endl;
//    cout << "测试位置:3,4:" << num1(3, 4, m, n) << endl;
//    cout << "测试位置:2,3:" << num1(2, 3, m, n) << endl;
//    cout << "测试位置:1,3:" << num1(1, 3, m, n) << endl;
//    cout << "测试位置:2,0:" << num1(2, 0, m, n) << endl;
//    cout << "测试位置:0,2:" << num1(0, 2, m, n) << endl;
//    cout << "------------------------------------------------" << endl;
//    return 0;
//}

using placeholders::_1;
using placeholders::_2;
using placeholders::_3;
int sub(int a,int b)
{
	return (a - b) * 10;
}
int main()
{
	cout << sub(10, 2) << endl;
	auto newSub = bind(sub, _1, _2);
	cout << sub(10, 2) << endl;

	return 0;
}

auto func1 = [](double rate, double money, int year)->double {
	double ret = money;
	for (int i = 0; i < year; i++)
	{
		ret += ret * money;
	}
	return ret - money;
	};

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
	cout << sub5(5, 1) << endl;
	auto sub6 = bind(SubX, _1, 100, _2);
	cout << sub6(5, 1) << endl;
	auto sub7 = bind(SubX, _1, _2, 100);
	cout << sub7(5, 1) << endl;
	// 成员函数对象进⾏绑死，就不需要每次都传递了 
	function<double(Plus&&, double, double)> f6 = &Plus::plusd;
	Plus pd;
	cout << f6(move(pd), 1.1, 1.1) << endl;
	cout << f6(Plus(), 1.1, 1.1) << endl;
	// bind⼀般⽤于，绑死⼀些固定参数 
	function<double(double, double)> f7 = bind(&Plus::plusd, Plus(), _1, _2);
	cout << f7(1.1, 1.1) << endl;
	// 计算复利的lambda 
	auto func1 = [](double rate, double money, int year)->double {
		double ret = money;
		for (int i = 0; i < year; i++)
		{
			ret += ret * rate;
		}
		return ret - money;
	};
	// 绑死⼀些参数，实现出⽀持不同年华利率，不同⾦额和不同年份计算出复利的结算利息 
	function<double(double)> func3_1_5 = bind(func1, 0.015, _1, 3);
	function<double(double)> func5_1_5 = bind(func1, 0.015, _1, 5);
	function<double(double)> func10_2_5 = bind(func1, 0.025, _1, 10);
	function<double(double)> func20_3_5 = bind(func1, 0.035, _1, 30);
	cout << func3_1_5(1000000) << endl;
	cout << func5_1_5(1000000) << endl;
	cout << func10_2_5(1000000) << endl;
	cout << func20_3_5(1000000) << endl;
	return 0;
}