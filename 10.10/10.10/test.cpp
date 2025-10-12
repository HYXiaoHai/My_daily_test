#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cmath>
#include<cassert>
using namespace std;

int change(const int F)
{
	int C;
	return (F - 32) * 5 / 9;
}
int max1(const int x1, const int x2)
{
	return x1 > x2 ? x1 : x2;
}
int max1(const int x1, const int x2, const int x3)
{
	int max = x1 > x2 ? x1 : x2;
	max = max > x3 ? max : x3;
	return max;
}
double max1(const double x1,const double x2)
{
	return x1 > x2 ? x1 : x2;
}
double max1(const double x1, const double x2, const double x3)
{
	double max = x1 > x2 ? x1 : x2;
	max = max > x3 ? max : x3;
	return max;
}

int Fibonacci(int n)
{
	assert(n > 0);
	if (n == 0)return 0;
	if (n == 1 || n == 2)return 1;
	
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main()
{
	cout << change(36.6) << endl;
	cout << pow(max1(1, 2,5), max1(1, 2)) << endl;
	cout << max1(1.9, 2.0) << endl;
	cout << max1(1.3, 3.8,2.0) << endl;
	cout << Fibonacci(10) << endl;
	return 0;
}