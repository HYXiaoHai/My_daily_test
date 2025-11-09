#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
//void fn1();
//int x = 1, y = 2;
//int main() {
//	cout << "Begin..." << endl;
//	cout << "x=" << x << endl;
//	cout << "y=" << y << endl;
//	cout << "Evaluate x and y in main()..." << endl;
//	int x = 10, y = 20;
//	cout << "x=" << x << endl;
//	cout << "y=" << y << endl;
//	cout << "Step into fn1()..." << endl;
//	fn1();
//	cout << "Back in main" << endl;
//	cout << "x=" << x << endl;
//	cout << "y=" << y << endl;
//	return 0;
//}
//void fn1() {
//	int y = 200;
//	cout << "x=" << x << endl;
//	cout << "y=" << y << endl;
//}
#include "client.h"

using namespace std;
int main() 
{
    // 显示初始状态
    cout << "=== 初始状态 ===" << endl;
    cout << "服务器名称: " << Client::getServerName() << endl;
    cout << "客户数量: " << Client::getClientNum() << endl;
    cout << endl;

    // 创建第一个客户机对象
    cout << "=== 创建第一个客户机对象 ===" << endl;
    Client client1;
    cout << "服务器名称: " << Client::getServerName() << endl;
    cout << "客户数量: " << Client::getClientNum() << endl;
    cout << endl;

    // 改变服务器名称
    cout << "=== 改变服务器名称 ===" << endl;
    Client::ChangeServerName("B");
    cout << "当前服务器名称: " << Client::getServerName() << endl;
    cout << "当前客户数量: " << Client::getClientNum() << endl;
    cout << endl;

    // 创建更多客户机对象
    cout << "=== 创建更多客户机对象 ===" << endl;
    Client client2;
    Client client3;
    cout << "服务器名称: " << Client::getServerName() << endl;
    cout << "客户数量: " << Client::getClientNum() << endl;
    cout << endl;

    // 再次改变服务器名称
    cout << "=== 再次改变服务器名称 ===" << endl;
    Client::ChangeServerName("C");
    cout << "最终服务器名称: " << Client::getServerName() << endl;
    cout << "最终客户数量: " << Client::getClientNum() << endl;

    return 0;
}