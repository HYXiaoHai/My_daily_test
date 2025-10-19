#include<iostream>
using namespace std;

struct DLinkNode {
    int data;
    DLinkNode* prev;
    DLinkNode* next;
    DLinkNode(int val = 0) : data(val), prev(nullptr), next(nullptr) {}
};

class DLinkList {
private:
    DLinkNode* head;
public:
    DLinkList() {
        head = new DLinkNode();
        head->next = head;
        head->prev = head;
    }

    ~DLinkList() {
        DLinkNode* p = head->next;
        while (p != head) {
            DLinkNode* temp = p;
            p = p->next;
            delete temp;
        }
        delete head;
    }

    // 头插法
    void insertHead(int x) {
        DLinkNode* newNode = new DLinkNode(x);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
    }

    // 尾插法
    void insertTail(int x) {
        DLinkNode* newNode = new DLinkNode(x);
        DLinkNode* tail = head->prev;

        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode;
        head->prev = newNode;
    }

    // 删除节点
    bool deleteNode(int x) {
        DLinkNode* p = head->next;
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
    DLinkNode* find(int x) {
        DLinkNode* p = head->next;
        while (p != head && p->data != x) {
            p = p->next;
        }
        return (p == head) ? nullptr : p;
    }

    // 获取长度
    int getLength() {
        int len = 0;
        DLinkNode* p = head->next;
        while (p != head) {
            len++;
            p = p->next;
        }
        return len;
    }

    // 正向打印
    void displayForward() {
        DLinkNode* p = head->next;
        while (p != head) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    // 反向打印
    void displayBackward() {
        DLinkNode* p = head->prev;
        while (p != head) {
            cout << p->data << " ";
            p = p->prev;
        }
        cout << endl;
    }
};

