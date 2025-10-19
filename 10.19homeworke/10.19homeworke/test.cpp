#define _CRT_SECURE_NO_WARNINGS 1
#include"sqlist.h"
#include"SLinkNode.h"
#include"CDLinkNod.h"
#include"CSLinkNode.h"
#include"DLinkNod.h"
#define MaxSize 100

void test_SqList()
{
	int i; int e;
	SqList<int> L(MaxSize); //定义一个顺序表L
	L.InsElem(1, 1); //插入元素1，位置1
	L.InsElem(3, 2); //插入元素3，位置2
	L.InsElem(1, 3); //插入元素1
	L.InsElem(5, 4); //插入元素5
	L.InsElem(4, 5); //插入元素4
	L.InsElem(2, 6); //插入元素2
	printf("线性表:"); L.DispList();
	printf("长度:%d\n", L.GetLength());
	i = 3; L.GetElem(i, e);
	printf("第%d个元素:%d\n", i, e);
	e = 1;
	printf("元素%d是第%d个元素\n", e, L.Locate(e));
	i = 4; printf("删除第%d个元素\n", i);
	L.DelElem(i);
	printf("线性表:"); L.DispList();
}


// 测试
void test_SLinkNode() {
	SLinkList list;

	list.insertHead(1);
	list.insertHead(2);
	list.insertTail(3);
	list.insertTail(4);
	list.insertAt(5, 3);

	cout << "单链表: ";
	list.display();
	cout << "长度: " << list.getLength() << endl;

	list.deleteNode(3);
	cout << "删除3后: ";
	list.display();

	if (list.find(5)) {
		cout << "找到5了" << endl;
	}
}
// 测试
void test_CSLinkNode() {
	CircularSLinkList list;

	list.insertHead(1);
	list.insertHead(2);
	list.insertTail(3);
	list.insertTail(4);

	cout << "循环单链表: ";
	list.display();
	cout << "长度: " << list.getLength() << endl;

	list.deleteNode(3);
	cout << "删除3后: ";
	list.display();

	if (list.find(4)) {
		cout << "找到4了" << endl;
	}
}
// 测试
void test_DLinkNod() {
	DLinkList list;

	list.insertHead(1);
	list.insertHead(2);
	list.insertTail(3);
	list.insertTail(4);

	cout << "双链表正向: ";
	list.displayForward();
	cout << "双链表反向: ";
	list.displayBackward();
	cout << "长度: " << list.getLength() << endl;

	list.deleteNode(3);
	cout << "删除3后正向: ";
	list.displayForward();

	if (list.find(4)) {
		cout << "找到4了" << endl;
	}
}
// 测试
void test_CDLinkNod() {
	CircularDLinkList list;

	list.insertHead(1);
	list.insertHead(2);
	list.insertTail(3);
	list.insertTail(4);

	cout << "循环双链表正向: ";
	list.displayForward();
	cout << "循环双链表反向: ";
	list.displayBackward();
	cout << "长度: " << list.getLength() << endl;

	list.deleteNode(3);
	cout << "删除3后正向: ";
	list.displayForward();

	if (list.find(4)) {
		cout << "找到4了" << endl;
	}

}
int main()
{
	//test_SqList();
	//test_SLinkNode();
	//test_CDLinkNod();
	//test_CSLinkNode();
	test_DLinkNod();
	return 0;
}