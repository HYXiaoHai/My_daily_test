#define _CRT_SECURE_NO_WARNINGS 1
//#include"AVLTree.h"
#include<iostream>
#include<vector>
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
	{
	}
};

// AVL: 二叉搜索树 + 平衡因子的限制
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
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
	// 在AVL树中插入值为data的节点
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
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;
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
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					//右单旋
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					//左单旋
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//左右双旋
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					//右左双旋
					RotateRL(parent);
				}
				else
				{
					assert(false);
				}
				break;
			}
			else
			{
				assert(false);
			}
		}
		return true;
	}

	// AVL树的验证
	bool IsAVLTree()
	{
		return _IsBalanceTree(_root);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	// 根据AVL树的概念验证pRoot是否为有效的AVL树
	bool _IsBalanceTree(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		int bf = rightHeight - leftHeight;
		if (abs(bf) >= 2 || bf != root->_bf)
		{
			cout << root->_kv.first << "平衡因子异常" << endl;
			return false;
		}
		return  _IsBalanceTree(root->_left) && _IsBalanceTree(root->_right);
	}
	size_t _Height(Node* pRoot)
	{
		if (pRoot == nullptr)
		{
			return 0;
		}
		int Hightl = _Height(pRoot->_left);
		int Hightr = _Height(pRoot->_right);
		return Hightl > Hightr ? Hightl + 1 : Hightr + 1;
	}
	// 右单旋
	void RotateR(Node* pParent)
	{
		Node* subL = pParent->_left;
		Node* subLR = subL->_right;

		Node* parentParent = pParent->_parent;

		pParent->_left = subLR;
		if (subLR != nullptr)
			subLR->_parent = pParent;

		subL->_right = pParent;
		pParent->_parent = subL;

		if (pParent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == pParent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
		subL->_bf = 0;
		pParent->_bf = 0;
	}
	// 左单旋
	void RotateL(Node* pParent)
	{
		Node* subR = pParent->_right;
		Node* subRL = subR->_left;

		Node* PParent = pParent->_parent;

		pParent->_right = subRL;
		if (subRL != nullptr)
			subRL->_parent = pParent;

		subR->_left = pParent;
		pParent->_parent = subR;

		if (pParent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (PParent->_left == pParent)
			{
				PParent->_left = subR;
			}
			else
			{
				PParent->_right = subR;
			}
			subR->_parent = PParent;
		}
		subR->_bf = 0;
		pParent->_bf = 0;
	}
	 //右左双旋
	void RotateRL(Node* pParent)
	{
		Node* subR = pParent->_right;
		Node* subRL = subR->_left;

		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(pParent);

		if (bf == 0)
		{
			subR->_bf = 0;
			subRL->_bf = 0;
			pParent->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			subRL->_bf = 0;
			pParent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			subRL->_bf = 0;
			pParent->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}
	// 左右双旋
	void RotateLR(Node* pParent)
	{
		Node* subL = pParent->_left;
		Node* subLR = subL->_right;

		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(pParent);

		if (bf == 0)
		{
			subL->_bf = 0;
			subLR->_bf = 0;
			pParent->_bf = 0;
		}
		else if (bf == 1)
		{
			subL->_bf = -1;
			subLR->_bf = 0;
			pParent->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			subLR->_bf = 0;
			pParent->_bf = 1;
		}
		else
		{
			assert(false);
		}
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}

private:
	Node* _root = nullptr;
};


void TestAVLTree1()
{
	AVLTree<int, int> t;
	// 常规的测试⽤例 
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// 特殊的带有双旋场景的测试⽤例 
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
		t.Insert({ e, e });
		t.InOrder();
	}
	t.InOrder();
	cout << t.IsAVLTree() << endl;
}

// 插⼊⼀堆随机值，测试平衡，顺便测试⼀下⾼度和性能等 
void TestAVLTree2()
{
	const int N = 100000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
	}
	size_t begin2 = clock();
	AVLTree<int, int> t;
	for (auto e : v)
	{
		t.Insert(make_pair(e, e));
	}
	size_t end2 = clock();
	cout << "Insert:" << end2 - begin2 << endl;
	cout << t.IsAVLTree() << endl;
	//cout << "Height:" << t.Height() << endl;
	//cout << "Size:" << t.Size() << endl;
	size_t begin1 = clock();
	// 确定在的值 
	/*for (auto e : v)
	{
	t.Find(e);
	}*/
	// 随机值 
	for (size_t i = 0; i < N; i++)
	{
		t.Find((rand() + i));
	}
	size_t end1 = clock();
	cout << "Find:" << end1 - begin1 << endl;
}


int main()
{
	TestAVLTree1();
	return 0;
}