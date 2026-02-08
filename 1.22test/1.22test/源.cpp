#define _CRT_SECURE_NO_WARNINGS 1
#ifndef _COMM_H_
#define _COMM_H_
# include <stdio.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# define PATHNAME "."
# define PROJ_ID 0x6666
int createShm(int size);
int destroyShm(int shmid);
int getShm(int size);
# endif

static int commShm(int size, int flags)
{
	key_t key = ftok(PATHNAME, PROJ_ID);
	if (key < 0) {
		perror("ftok");
		return -1;
	}
	int shmid = 0;
	if ((shmid = shmget(key, size, flags)) < 0) {
		perror("shmget");
		return -2;
	}
	return shmid;
}
int destroyShm(int shmid)
{
	if (shmctl(shmid, IPC_RMID, NULL) < 0) {
		perror("shmctl");
		return -1;
	}
	return 0;
}
int createShm(int size)
{
	return commShm(size, IPC_CREAT | IPC_EXCL | 0666);
}
int getShm(int size)
{
	return commShm(size, IPC_CREAT);
}

#include "comm.h"
int main()
{
	int shmid = createShm(4096);
	char* addr = shmat(shmid, NULL, 0);
	sleep(2);
	int i = 0;
	while (i++ < 26) {
		printf("client# %s\n", addr);
		sleep(1);
	}
	shmdt(addr);
	sleep(2);
	destroyShm(shmid);
	return 0;
}

#include "comm.h"
int main()
{
	int shmid = getShm(4096);
	sleep(1);
	char* addr = shmat(shmid, NULL, 0);
	sleep(2);
	int i = 0;
	while (i < 26) {
		addr[i] = 'A' + i;
		i++;
		addr[i] = 0;
		sleep(1);
	}
	shmdt(addr);
	sleep(2);
	return 0;
}
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
// mykill -signumber pid
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " -signumber pid" << std::endl;
		return 1;
	}
	int number = std::stoi(argv[1] + 1); // 去掉- 
	pid_t pid = std::stoi(argv[2]);
	int n = kill(pid, number);
	return n;
}

#include <iostream>
#include <unistd.h>
#include <signal.h>
void handler(int signumber)
{
	// 整个代码就只有这⼀处打印 
	std::cout << "获取了⼀个信号: " << signumber << std::endl;
}
// mykill -signumber pid
int main()
{
	signal(2, handler); // 先对2号信号进⾏捕捉 
	// 每隔1S，⾃⼰给⾃⼰发送2号信号 
	while (true)
	{
		sleep(1);
		raise(2);
	}
}

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <functional>
using func_t = std::function<void()>;
int gcount = 0;
std::vector<func_t> gfuncs;
// 把信号 更换 成为 硬件中断 
void hanlder(int signo)
{
	for (auto& f : gfuncs)
	{
		f();
	}
	std::cout << "gcount : " << gcount << std::endl;
	int n = alarm(1); // 重设闹钟，会返回上⼀次闹钟的剩余时间 
	std::cout << "剩余时间 : " << n << std::endl;
}
int main()
{
	//gfuncs.push_back([](){ std::cout << "我是⼀个内核刷新操作" << std::endl; 
});
//gfuncs.push_back([](){ std::cout << "我是⼀个检测进程时间⽚的操作，如果时间⽚到了，我会切换进程" << std::endl; }); 
//gfuncs.push_back([](){ std::cout << "我是⼀个内存管理操作，定期清理操作系统内
部的内存碎⽚" << std::endl; }); 
alarm(1); // ⼀次性的闹钟，超时alarm会⾃动被取消 
signal(SIGALRM, hanlder);
while (true)
{
	pause();
	std::cout << "我醒来了..." << std::endl;
	gcount++;
}
}
NAME
pause - wait for signal
SYNOPSIS
#include <unistd.h>
int pause(void);
DESCRIPTION
pause() causes the calling process(or thread) to sleep until a signal
is delivered that either terminates the process or causes the invoca‐
tion of a signal - catching function.
RETURN VALUE
pause() returns only when a signal was caught and the signal - catching
function returned.In this case, pause() returns - 1, and errno is set
to EINTR.


#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigcb(int signumber) {
	printf("信号: %d\n", signumber);
}

int main() {
	struct sigaction act = { 0 };
	act.sa_handler = sigcb;
	sigaction(SIGINT, &act, NULL);

	while (1) {
		sleep(1);  // 保持程序运行，等待信号
	}

	return 0;
}
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// 信号计数器
int sig2_count = 0;
int sig40_count = 0;

// 信号处理函数
void handler(int signumber) {
	if (signumber == 2) {
		printf("处理了2号信号)\n");
	}
	else if (signumber == 40) {
		printf("处理了40号信号\n");
	}
}

int main() {
	printf("PID: %d\n", getpid());
	signal(2, handler);
	signal(40, handler);

	sigset_t newmask, oldmask;

	sigemptyset(&newmask);

	sigaddset(&newmask, 2);
	sigaddset(&newmask, 40);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		perror("sigprocmask error");
		exit(1);
	}

	sleep(2);

	return 0;
}