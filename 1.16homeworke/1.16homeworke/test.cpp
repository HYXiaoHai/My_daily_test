#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>  // 用于write, read, lseek, close函数
using namespace std;
//1.考察fopen, fread, fwrite, fseek, fclose等函数的使用
//
//2.要求：
//
//2.1使用代码打开当前路径下的“bite”文件（如果文件不存在在创建文件），向文件当中写入“linux so easy!”.
//
//2.2 在从文件当中读出文件当中的内容， 打印到标准输出当中； 关闭文件流指针
//
//3.提交要求：提交代码截图， 提交代码执行之后的截图
int main()
{
	FILE* file = fopen("bite","w+");
	if (file == nullptr)
	{
		cout << "error" << endl;
	}
	const char* msg = "linux so easy!";
	size_t len = strlen(msg);  

	size_t n = fwrite(msg, sizeof(char), len, file);
	if (n == 0)
	{
		cout << "error" << endl;
	}

	if (fseek(file, 0, SEEK_SET) != 0)
	{
		cout << "error" << endl;
		fclose(file);
	}


	char buffer[128];
	size_t read = fread(buffer, sizeof(char), len, file); 
	if (read != len) {
		cout << "error" << endl;
		fclose(file);
	}
	buffer[read] = '\0';  
	printf("%s\n", buffer);
	fclose(file);
	return 0;
}

//int main()
//{
//	int fd = open("myfile", O_WRONLY | O_CREAT, 0644);
//	if (fd < 0) {
//		perror("open");
//		return 1;
//	}
//	const char* msg = "i like linux!";
//	int len = strlen(msg);
//	write(fd, msg, len);
//	close(fd);
//	return 0;
//
// }
int main(int argc, char* argv[])
{
	int pipefd[2];
	if (pipe(pipefd) == -1)
		ERR_EXIT("pipe error");
	pid_t pid;
	pid = fork();
	if (pid == -1)
		ERR_EXIT("fork error");
	if (pid == 0) {
		close(pipefd[0]);
		write(pipefd[1], "hello", 5);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	char buf[10] = { 0 };
	read(pipefd[0], buf, 10);
	printf("buf=%s\n", buf);
	return 0;
}

int main()
{
	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		ER_EXIT("error");
	}
	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		cout << error;
	}
	else if(pid == 0)
	{
		close(pipefd[0]);
		write(pipefd[1],"hello",5);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	char buf[10] = { 0 };
	read(pipefd[0], buf, 0);
	cout << buf << endl;
	return 0;

}
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define ERR_EXIT(m) \
do \
{ \
 perror(m); \
 exit(EXIT_FAILURE); \
} while(0)
int main(int argc, char* argv[])
{
	mkfifo("tp", 0644);
	int infd;
	infd = open("abc", O_RDONLY);
	if (infd == -1) ERR_EXIT("open");
	int outfd;
	outfd = open("tp", O_WRONLY);
	if (outfd == -1) ERR_EXIT("open");
	char buf[1024];
	int n;
	while ((n = read(infd, buf, 1024)) > 0)
	{
		write(outfd, buf, n);
	}
	close(infd);
	close(outfd);
	return 0;
}
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define ERR_EXIT(m) \
 do \
 { \
 perror(m); \
 exit(EXIT_FAILURE); \
 } while(0)

int main(int argc, char* argv[])
{
	int outfd;
	outfd = open("abc.bak", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfd == -1) ERR_EXIT("open");

	int infd;
	infd = open("tp", O_RDONLY);
	if (outfd == -1)
		ERR_EXIT("open");
	char buf[1024];
	int n;
	while ((n = read(infd, buf, 1024)) > 0)
	{
		write(outfd, buf, n);
	}
	close(infd);
	close(outfd);
	unlink("tp");
	return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define ERR_EXIT(m) \
do{\
 perror(m);\
 exit(EXIT_FAILURE);\
}while(0)
int main()
{
	umask(0);
	if (mkfifo("mypipe", 0644) < 0) {
		ERR_EXIT("mkfifo");
	}
	int rfd = open("mypipe", O_RDONLY);
	if (rfd < 0) {
		ERR_EXIT("open");
	}
	char buf[1024];
	while (1) {
		buf[0] = 0;
		printf("Please wait...\n");
		ssize_t s = read(rfd, buf, sizeof(buf) - 1);
		if (s > 0) {
			buf[s - 1] = 0;
			printf("client say# %s\n", buf);
		}
		else if (s == 0) {
			printf("client quit, exit now!\n");
			exit(EXIT_SUCCESS);
		}
		else {
			ERR_EXIT("read");
		}
	}
	close(rfd);
	return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define ERR_EXIT(m) \
do{\
 perror(m);\
 exit(EXIT_FAILURE);\
}while(0)
int main()
{
	int wfd = open("mypipe", O_WRONLY);
	if (wfd < 0) {
		ERR_EXIT("open");
	}
	char buf[1024];
	while (1) {
		buf[0] = 0;
		printf("Please Enter# ");
		fflush(stdout);
		ssize_t s = read(0, buf, sizeof(buf) - 1);
		if (s > 0) {
			buf[s] = 0;
			write(wfd, buf, strlen(buf));
		}
		else if (s <= 0) {
			ERR_EXIT("read");
		}
	}
	close(wfd);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main() {
	int fd;
	char message[] = "i am process A";

	// 创建命名管道
	if (mkfifo("myfifo", 0666) < 0) {
		perror("mkfifo");
	}

	// 打开管道（以写方式）
	fd = open("myfifo", O_WRONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	// 写入数据到管道
	if (write(fd, message, strlen(message) + 1) < 0) {
		perror("write");
		close(fd);
		exit(1);
	}
	// 删除命名管道
	unlink("myfifo");

	return 0;
}
int main() {
	int fd;
	char buffer[BUFFER_SIZE];


	// 打开管道（以读方式）
	fd = open("myfifo", O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	// 从管道读取数据
	ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0) {
		perror("read");
		close(fd);
		exit(1);
	}

	buffer[bytes_read] = '\0';

	// 关闭管道
	close(fd);

	return 0;
}