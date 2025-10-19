#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
struct SLinkNode {
    int data;
    SLinkNode* next;
    SLinkNode(int val = 0) : data(val), next(nullptr) {}
};

class SLinkList {
private:
    SLinkNode* head;
public:
    SLinkList() {
        head = new SLinkNode();
    }

    ~SLinkList() {
        SLinkNode* p = head;
        while (p) {
            SLinkNode* temp = p;
            p = p->next;
            delete temp;
        }
    }

    // 头插法
    void insertHead(int x) {
        SLinkNode* newNode = new SLinkNode(x);
        newNode->next = head->next;
        head->next = newNode;
    }

    // 尾插法
    void insertTail(int x) {
        SLinkNode* newNode = new SLinkNode(x);
        SLinkNode* p = head;
        while (p->next) p = p->next;
        p->next = newNode;
    }

    // 按位置插入
    bool insertAt(int x, int pos) {
        if (pos < 1) return false;
        SLinkNode* p = head;
        for (int i = 0; i < pos - 1 && p; i++) {
            p = p->next;
        }
        if (!p) return false;
        SLinkNode* newNode = new SLinkNode(x);
        newNode->next = p->next;
        p->next = newNode;
        return true;
    }

    // 删除节点
    bool deleteNode(int x) {
        SLinkNode* p = head;
        while (p->next && p->next->data != x) {
            p = p->next;
        }
        if (!p->next) return false;
        SLinkNode* temp = p->next;
        p->next = temp->next;
        delete temp;
        return true;
    }

    // 查找
    SLinkNode* find(int x) {
        SLinkNode* p = head->next;
        while (p && p->data != x) {
            p = p->next;
        }
        return p;
    }

    // 获取长度
    int getLength() {
        int len = 0;
        SLinkNode* p = head->next;
        while (p) {
            len++;
            p = p->next;
        }
        return len;
    }

    // 打印
    void display() {
        SLinkNode* p = head->next;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};
