#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
typedef int ElemType;
namespace queue
{
	typedef struct QNode
	{
		ElemType data;
		struct QNode* next;
	}QType;

	typedef struct qptr //链队结点类型
	{
		QType* front;
		QType* rear;
	} LinkQueue;

	void InitQueue(LinkQueue*& lq)
	{
		lq = (LinkQueue*)malloc(sizeof(LinkQueue));
		lq->rear = lq->front = NULL;
	}
	void DestroyQueue(LinkQueue*& lq)
	{
		QType* pre = lq->front, * p;
		if (pre != NULL)
		{
			if (pre == lq->rear)
				free(pre);
			else
			{
				p = pre->next;
				while (p != NULL)
				{
					free(pre);
					pre = p; p = p->next;
				}
				free(pre);
			}
			free(lq);
		}
	}
	int EnQueue(LinkQueue*& lq, ElemType x)
	{
		QType* s;
		s = (QType*)malloc(sizeof(QType));
		s->data = x; s->next = NULL;
		if (lq->front == NULL)
			lq->rear = lq->front = s;
		else
		{
			lq->rear->next = s;
			lq->rear = s;
		}
		return 1;
	}

	int DeQueue(LinkQueue*& lq, ElemType& x)
	{
		QType* p;
		if (lq->front == NULL)
			return 0;
		p = lq->front;
		x = p->data;
		if (lq->rear == lq->front) //原队只有一个结点,删除后队变空
			lq->rear = lq->front = NULL;
		else
			lq->front = lq->front->next;
		free(p);
		return 1;
	}
	int GetHead(LinkQueue* lq, ElemType& x)
	{
		if (lq->front == NULL)
			return 0;
		x = lq->front->data;
		return 1;
	}
	int QueueEmpty(LinkQueue* lq)
	{
		if (lq->front == NULL)
			return 1;
		else
			return 0;
	}
	void test_queue()
	{
		LinkQueue* lq;
		ElemType e;
		printf("初始化队列\n");
		InitQueue(lq);
		printf("队%s\n", (QueueEmpty(lq) == 1 ? "空" : "不空"));
		printf("a进队\n"); EnQueue(lq, 'a');
		printf("b进队\n"); EnQueue(lq, 'b');
		printf("c进队\n"); EnQueue(lq, 'c');
		printf("d进队\n"); EnQueue(lq, 'd');
		printf("队%s\n", (QueueEmpty(lq) == 1 ? "空" : "不空"));
		GetHead(lq, e);
		printf("队头元素:%c\n", e);
		printf("出队次序:");
		while (!QueueEmpty(lq)) //队不空循环
		{
			DeQueue(lq, e); //出队元素e
			printf("%c ", e); //输出元素e
		}
		printf("\n");
		DestroyQueue(lq);
	}
}

namespace stack
{
	typedef struct node
	{
		ElemType data; //存储结点数据，
		//这里假设ElemType为char类型
		struct node* next; //指针域
	} LinkStack;
	void InitStack(LinkStack*& ls)
	{
		ls = NULL;
	}
	void DestroyStack(LinkStack*& ls)
	{
		LinkStack* pre = ls, * p;
		if (pre == NULL) return; //考虑空栈的情况
		p = pre->next;
		while (p != NULL)
		{
			free(pre); //释放pre结点
			pre = p; p = p->next; //pre、p同步后移
		}
		free(pre); //释放尾结点
	}
	int Push(LinkStack*& ls, ElemType x)
	{
		LinkStack* p;
		p = (LinkStack*)malloc(sizeof(LinkStack));
		p->data = x; //创建结点p用于存放x
		p->next = ls; //插入p结点作为栈顶结点
		ls = p;
		return 1;
	}
	int Pop(LinkStack*& ls, ElemType& x)
	{
		LinkStack* p;
		if (ls == NULL) //栈空,下溢出返回0
			return 0;
		else //栈不空时出栈元素x并返回1
		{
			p = ls; //p指向栈顶结点
			x = p->data; //取栈顶元素x
			ls = p->next; //删除结点p
			free(p); //释放p结点
			return 1;
		}
	}
	int GetTop(LinkStack* ls, ElemType& x)
	{
		if (ls == NULL) //栈空,下溢出时返回0
			return 0;
		else //栈不空,取栈顶元素x并返回1
		{
			x = ls->data;
			return 1;
		}
	}
	int StackEmpty(LinkStack* ls)
	{
		if (ls == NULL)
			return 1;
		else
			return 0;
	}
	void test()
	{
		LinkStack* st;
		ElemType e;
		printf("初始化栈st\n");
		InitStack(st);
		printf("栈%s\n", (StackEmpty(st) == 1 ? "空" : "不空"));
		printf("a进栈\n"); Push(st, 'a');
		printf("b进栈\n"); Push(st, 'b');
		printf("c进栈\n"); Push(st, 'c');
		printf("d进栈\n"); Push(st, 'd');
		printf("栈%s\n", (StackEmpty(st) == 1 ? "空" : "不空"));
		GetTop(st, e);
		printf("栈顶元素:%c\n", e);
		printf("出栈次序:");
		while (!StackEmpty(st)) //栈不空循环
		{
			Pop(st, e); //出栈元素e并输出
			printf("%c ", e);
		}
		printf("\n");
		DestroyStack(st);
	}
}
int main()
{
	//queue::test_queue();
	stack::test();
	return 0;
}