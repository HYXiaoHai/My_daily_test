#define _CRT_SECURE_NO_WARNINGS 1
#include"Client.h"
string Client::ServerName = "A";
int Client::ClientNum = 1;
void Client::ChangeServerName(string name)
{
	ServerName = name;
	std::cout << "服务器名称已更改为: " << ServerName << std::endl;
}

string Client::getServerName()
{
	return ServerName;
}
int Client::getClientNum()
{
	return ClientNum;
}