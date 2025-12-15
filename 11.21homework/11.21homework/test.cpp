#define _CRT_SECURE_NO_WARNINGS 1
//一、实验目的
//▫学习使用数组数据对象
//▫学习字符串数据的组织和处理
//▫学习标准C++库的使用
//▫掌握指针的使用
//▫练习通过Debug观察指针的内容机器所指对象的内容
//▫练习动态内存分配实现动态数组，并体会指针在其中的作用
//▫分别使用字符数组和标准C++库练习处理字符串的方法
//二、实验任务

#include<iostream>
#include<vector>
using namespace std;

//3×3矩阵转置
void task1()
{
	int arr1[3][3];
	cout << "输入数据" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cin >> arr1[i][j];
	}
	cout << "数据显示：" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << arr1[i][j] << " ";
		cout << endl;
	}
	cout << endl << "转置：" << endl;
	int arr2[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr2[j][i] = arr1[i][j];
		}
	}
	cout << "数据显示：" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << arr2[i][j] << " ";
		cout << endl;
	}
}

//2.使用动态内存分配生成动态数组来重新完成矩阵转置，使用指针实现函数的功能。
void zhuanzhi(int**arr1,int**arr2,const int _size)
{
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			arr2[j][i] = arr1[i][j];
		}
	}

}
void Print(int**arr,int _size)
{
	for (int i = 0;i<_size;i++)
	{
		for (int j = 0; j < _size; j++)
			cout << arr[i][j]<<" ";
		cout << endl;
	}
}
void task2()
{
	cout << "输入大小：";
	int _size;
	cin >> _size;
	
	int** arr1 = new int* [_size];
	int** arr2 = new int* [_size];
	for (int i =0;i<_size;i++)
	{
		arr1[i] = new int[_size];
		arr2[i] = new int[_size];
	}

	cout << "输入数据" << endl;
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++)
			cin >> arr1[i][j];
	}
	cout << "数据显示：" << endl;
	Print(arr1, _size);
	cout << endl << "转置：" << endl;
	zhuanzhi(arr1, arr2,_size);
	cout << "数据显示：" << endl;
	Print(arr2, _size);
	for (int i = 0;i<_size;i++)
	{
		delete arr1[i];
		delete arr2[i];
		arr1[i] = arr2[i] = nullptr;
	}
	delete arr1;
	delete arr2;
	arr1 = arr2 = nullptr;
}

//3.编程实现两个字符串的连接，使用字符数组保存字符串，不要使用系统函数。
void task3()
{
	const int MAX = 100;
	char result[MAX*2];
	char s1[MAX] = "abcd";
	char s2[MAX] = "1234";
	int i = 0;
	int j = 0;
	cout << s1 << "+" << s2<<endl;
	for (i = 0; i < strlen(s1); i++)
	{
		result[i] = s1[i];
	}
	for (int j = 0; j < strlen(s2); j++, i++)
	{
		result[i] = s2[j];
	}
	result[i] = '\0';
	cout << result << endl;
}
//4.使用string类声明字符串对象，重新实现字符串连接。
void task4()
{
	string s1;
	string s2;
	cout << "s1:";
	cin >> s1;
	cout << "s2:";
	cin >> s2;
	cout << s1<<"+"<<s2<< ":";
	cout << s1 + s2 << endl;
	return ;
}
//5.声明一个Employee类，包括姓名、街道、城市和邮编等属性，以及changeName()和display()等函数
// Display()显示姓名、街道等属性，changeName()改变对象的姓名属性，实现该类，并测试。
//6.声明包含5个元素的对象数组，每个都是Employee的对象。
class Employee
{
public:
	Employee(string name, string street, string city, string zipCode)
		:_name(name)
		, _street(street)
		,_city(city)
		,_zipCode(zipCode)
	{

	}
	void changeName(const string name)
	{
		cout << "更改姓名:" << _name;
		_name = name;
		cout << "->" << _name << endl;
	}
	void display()
	{
		cout <<"name:" << _name << endl;
		cout <<"street:" << _street << endl;
		cout <<"city:" << _city << endl;
		cout <<"zipCode:" << _zipCode << endl;
	}
private:
	string _name;
	string _street;
	string _city;
	string _zipCode;
};
void task56()
{
	Employee e1("张三", "人民路123号", "北京", "100000");
	Employee e2("李四", "中山路456号", "上海", "200000");
	Employee e3("王五", "解放路789号", "广州", "510000");
	Employee e4("赵六", "建设路321号", "深圳", "518000");
	Employee e5("钱七", "和平路654号", "杭州", "310000");
	vector<Employee>v = {
		e1,e2,e3,e4,e5
	};
	cout << "所有员工信息:" << endl;
	for (auto e:v)
	{
		e.display();
		cout << "----------------------" << endl;
	}
	cout << "测试changeName函数:" << endl;
	v[0].changeName("张小明");
	// 测试changeName函数
	v[0].display();
}
int main()
{
	cout << "task1" << endl;
	task1();
	cout << endl;
	cout << "task2" << endl;
	task2();
	cout << endl;
	cout << "task3" << endl;
	task3();
	cout << endl;
	cout << "task4" << endl;
	task4();
	cout << endl;
	cout << "task56" << endl;
	task56();

	return 0;
}