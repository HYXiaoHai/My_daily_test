#pragma once
#include<iostream>
#include<cassert>
using namespace std;

// 枚举值表⽰颜⾊ 
enum Colour
{
	RED,
	BLACK
};

// 这⾥我们默认按key/value结构实现 
template<class T>
struct RBTreeNode
{
	// 这⾥更新控制平衡也要加⼊parent指针 
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Colour _col;
	RBTreeNode(const T& data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{
	}
};

template<class T,class Ref,class Ptr>
struct TreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef TreeIterator<T,Ref,Ptr> Self;
	Node* _node;
	TreeIterator(Node* node)
		:_node(node)
	{
	}
	T& operator*()
	{
		return _node->_data;
	}
	T* operator->()
	{
		return &_node->_data;
	}
	bool operator != (const Self& s)const
	{
		return _node != s._node;
	}
	Self& operator++()
	{
		//当前节点右不为空，下一个就是右子树的中序第一个（最左边）
		//当前节点右为空，下一个孩子是父亲左的那个祖先节点
		if (_node->_right)
		{
			Node* min = _node->_right;
			while (min->_left)
			{
				min = min->_left;
			}
			_node = min;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	Self& operator--()
	{
		//当前节点右不为空，下一个就是右子树的中序第一个（最左边）
		//当前节点右为空，下一个孩子是父亲左的那个祖先节点
		if (_node->_left)
		{
			Node* max = _node->_left;
			while (max->_right)
			{
				max = max->_right;
			}
			_node = max;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
};


template<class K, class T, class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef TreeIterator<T> Iterator;

	Iterator Begin()
	{
		Node* min = _root;
		while (min && min->_left != nullptr)
		{
			min = min->_left;
		}

		return Iterator(min);
	}

	Iterator End()
	{
		return Iterator(nullptr);
	}

	bool Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;

			return true;
		}
		KeyOfT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(data);
		cur->_col = RED;
		if (kot(parent->_data) < kot(data))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//   g
			// p   u
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					// u存在且为红 ->变⾊再继续往上处理
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else// u不存在或存在且为黑 ->旋转+变⾊ 
				{
					if (cur == parent->_left)
					{
						//    g
						//  p   u
						//c
						//单旋 
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//    g
						//  p   u
						//     c
						//双旋 
						RotateL(parent);
						RotateR(grandfather);

						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else
			{
				//   g
				// u   p
				Node* uncle = grandfather->_left;
				// 叔叔存在且为红，-》变⾊即可 
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					// 继续往上处理 
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 叔叔不存在，或者存在且为⿊ 
				{
					// 情况⼆：叔叔不存在或者存在且为⿊ 
					// 旋转+变⾊ 
					// g
					// u p
					// c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						// g
						// u p
						// c
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	Node* Find(const K& key)
	{
		KeyOfT kot;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else if (kot(cur->_data) > key)
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

	Node* _root = nullptr;
};

