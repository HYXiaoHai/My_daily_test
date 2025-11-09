#pragma once
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
//实现客户机（Client）类。声明字符型静态数据成员ServerName，保存其服务器名称；
//整型静态数据成员ClientNum，记录已定义的客户数量；定义静态函数ChangeServerName()改变服务器名称。

//在头文件client.h中声明类，在文件client.cpp中实现，在文件test.cpp中测试该类，
//观察相应成员变量取值的变化情况。
//提示：新建一个空项目Lab5_2，添加头文件client.h, 在其中声明类Client，注意使用编译预处理命令；
//再添加源程序文件client.cpp，在其中实现Client类，注意静态成员变量的使用方法；
//再添加Lab5_2.cpp，在其中定义main()，测试Client类，观察相应成员变量的取值变化情况。

class Client
{
public:
	static void ChangeServerName(string name);
	static string getServerName();              
	static int getClientNum(); 
private:
	static string ServerName;
	static int ClientNum;
};