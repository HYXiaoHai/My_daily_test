#include<iostream>
using namespace std;

struct CDLinkNode {
    int data;
    CDLinkNode* prev;
    CDLinkNode* next;
    CDLinkNode(int val = 0) : data(val), prev(this), next(this) {}
};

class CircularDLinkList {
private:
    CDLinkNode* head;
public:
    CircularDLinkList() {
        head = new CDLinkNode();
    }

    ~CircularDLinkList() {
        if (head->next == head) {
            delete head;
            return;
        }

        CDLinkNode* p = head->next;
        while (p != head) {
            CDLinkNode* temp = p;
            p = p->next;
            delete temp;
        }
        delete head;
    }

    // 头插法
    void insertHead(int x) {
        CDLinkNode* newNode = new CDLinkNode(x);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
    }

    // 尾插法
    void insertTail(int x) {
        CDLinkNode* newNode = new CDLinkNode(x);
        CDLinkNode* tail = head->prev;

        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode;
        head->prev = newNode;
    }

    // 删除节点
    bool deleteNode(int x) {
        CDLinkNode* p = head->next;
        while (p != head && p->data != x) {
            p = p->next;
        }
        if (p == head) return false;

        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        return true;
    }

    // 查找
    CDLinkNode* find(int x) {
        CDLinkNode* p = head->next;
        while (p != head && p->data != x) {
            p = p->next;
        }
        return (p == head) ? nullptr : p;
    }

    // 获取长度
    int getLength() {
        int len = 0;
        CDLinkNode* p = head->next;
        while (p != head) {
            len++;
            p = p->next;
        }
        return len;
    }

    // 正向打印
    void displayForward() {
        CDLinkNode* p = head->next;
        while (p != head) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    // 反向打印
    void displayBackward() {
        CDLinkNode* p = head->prev;
        while (p != head) {
            cout << p->data << " ";
            p = p->prev;
        }
        cout << endl;
    }
};

