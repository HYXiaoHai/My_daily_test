#pragma once
#include<iostream>
#include<cassert>
using namespace std;
template<class K, class V>
struct AVLTreeNode
{
	// 需要parent指针，后续更新平衡因⼦可以看到 
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf; // 平衡因子
	AVLTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{ }
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
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
			else if (cur->_kv.first > kv.first)
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
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		cur->_parent = parent;

		// 更新平衡因⼦ 
		while (parent)
		{
			// 更新平衡因⼦ 
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;
			if (parent->_bf == 0)
			{
				// 更新结束 
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				// 继续往上更新 
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				// 不平衡了，旋转处理 
				break;
			}
			else
			{
				//插入之前这颗树就有2/-2bf的节点，这棵树之前就不是AVLTree
				assert(false);
			}
		}
		return true;
	}

private:
	Node* _root = nullptr;
};
