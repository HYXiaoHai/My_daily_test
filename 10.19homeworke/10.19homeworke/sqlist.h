#pragma once
#include<iostream>
#include<cassert>
using namespace std;
#define MaxSize 100
typedef int ElemType;
template<class T>
class SqList
{
public:
	SqList(int n = 0) 
		: _length(n)
	{
		// 可以选择初始化数组
		for (int i = 0; i < n && i < MaxSize; ++i) {
			_data[i] = T(); // 使用T的默认构造函数
		}
	}
	int GetLength()
	{
		return _length;
	}
	bool GetElem(int i, T& e)
	{
		if (i<0 || i>_length)
		{
			return 0;
		}
		else
		{
			e = _data[i - 1];
			return 1;
		}
	}
	int Locate(T x)
	{
		int i = 0;
		while (i < _length && _data[i] != x)
			i++; 
		if (i >= _length) return(0); 
		else return(i + 1); 

	}
	int InsElem(T x, int i)
	{
		int j;
		if (i<1 || i>_length + 1) //无效的参数i
			return 0;
		for (j = _length; j >= i; j--) //将位置为i的结点及之后的结点后移
			_data[j] = _data[j - 1];
		_data[i - 1] = x; //在位置i处放入x
		_length++; //线性表长度增1
		return 1;
	}
	int DelElem(int i)
	{
		int j;
		if (i<1 || i>_length) //无效的参数i
			return 0;
		for (j = i; j <_length; j++) //将位置为i的结点之后的结点前移
			_data[j - 1] = _data[j];
		_length--; //线性表长度减1
		return 1;
	}
	void DispList()
	{
		int i;
		for (i = 0; i < _length; i++)
			printf("%d ", _data[i]);
		printf("\n");
	}
private:
	T _data[MaxSize];
	int _length;
};

