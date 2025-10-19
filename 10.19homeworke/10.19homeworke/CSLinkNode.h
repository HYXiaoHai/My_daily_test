#include<iostream>
using namespace std;

struct DSLinkNode {
	int data;
	DSLinkNode* next;
	DSLinkNode(int val = 0) : data(val), next(nullptr) {}
};

class CircularSLinkList {
private:
	DSLinkNode* head;
public:
	CircularSLinkList() {
		head = new DSLinkNode();
		head->next = head;  // 指向自己形成循环
	}

	~CircularSLinkList() {
		DSLinkNode* p = head->next;
		while (p != head) {
			DSLinkNode* temp = p;
			p = p->next;
			delete temp;
		}
		delete head;
	}

	// 头插法
	void insertHead(int x) {
		DSLinkNode* newNode = new DSLinkNode(x);
		newNode->next = head->next;
		head->next = newNode;
	}

	// 尾插法
	void insertTail(int x) {
		DSLinkNode* newNode = new DSLinkNode(x);
		DSLinkNode* p = head;
		while (p->next != head) p = p->next;
		p->next = newNode;
		newNode->next = head;
	}

	// 删除节点
	bool deleteNode(int x) {
		DSLinkNode* p = head;
		while (p->next != head && p->next->data != x) {
			p = p->next;
		}
		if (p->next == head) return false;
		DSLinkNode* temp = p->next;
		p->next = temp->next;
		delete temp;
		return true;
	}

	// 查找
	DSLinkNode* find(int x) {
		DSLinkNode* p = head->next;
		while (p != head && p->data != x) {
			p = p->next;
		}
		return (p == head) ? nullptr : p;
	}

	// 获取长度
	int getLength() {
		int len = 0;
		DSLinkNode* p = head->next;
		while (p != head) {
			len++;
			p = p->next;
		}
		return len;
	}

	// 打印
	void display() {
		DSLinkNode* p = head->next;
		while (p != head) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
};

