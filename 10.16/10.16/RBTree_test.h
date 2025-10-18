#pragma once
#include<iostream>
#include<cassert>
using namespace std;

// 枚举值表示颜色
enum Colour
{
	RED,
	BLACK
};


// 这里我们默认按key/value结构实现
template<class K, class V>
struct RBTreeNode
{
	// 这里更新控制平衡也要加入parent指针
	pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Colour _col;


	RBTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{
	}
};


template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first>kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		cur->_col = RED;
		if (parent->_kv.first > kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		while (parent&&parent->_col == RED)
		{
			Node* grandparent = parent->_parent;
			if (parent == grandparent->_left)
			{
				Node* uncle = grandparent->_right;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandparent->_col = RED;

					cur = grandparent;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(grandparent);

						parent->_col = BLACK;
						grandparent->_col = RED;
					}
					else
					{
						RotateL(parent);
						RotateR(grandparent);

						cur->_col = BLACK;
						grandparent->_col = RED;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandparent->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandparent->_col = RED;

					cur = grandparent;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						RotateL(grandparent);
						parent->_col = BLACK;
						grandparent->_col = RED;
					}
					else
					{
						RotateR(parent);
						RotateL(grandparent);
						cur->_col = BLACK;
						grandparent->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}
	bool IsBalance()
	{
		if (_root == nullptr)
			return true;


		if (_root->_col == RED)
			return false;


		// 参考值
		int refNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				++refNum;
			}
			cur = cur->_left;
		}


		return Check(_root, 0, refNum);
	}
private:
	void RotateR(Node* parent)
	{
		//存储指针
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//保存parent的父节点
		Node* parentParent = parent->_parent;

		//旋转
		parent->_left = subLR;
		if (subLR != nullptr)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		//判断旋转后，是不是根节点
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		Node* parentParent = parent->_parent;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;;
		_InOrder(root->_right);
	}


	// 前序递归遍历
	bool Check(Node* root, int blackNum, const int refNum)
	{
		if (root == nullptr)
		{
			// 前序遍历走到空时，意味着一条路径走完了
			//cout << blackNum << endl;
			if (refNum != blackNum)
			{
				cout << "存在黑色结点的数量不相等的路径" << endl;
				return false;
			}
			return true;
		}


		// 检查孩子不太方便，因为孩子有两个，且不一定存在，反过来检查父亲就方便多了
		if (root->_col == RED && root->_parent && root->_parent->_col == RED)
		{
			cout << root->_kv.first << "存在连续的红色结点" << endl;
			return false;
		}


		if (root->_col == BLACK)
		{
			blackNum++;
		}


		return Check(root->_left, blackNum, refNum)
			&& Check(root->_right, blackNum, refNum);
	}


	


private:
	Node* _root = nullptr;
};