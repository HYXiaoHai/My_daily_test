#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;
//template<class T>
//class Auto_ptr
//{
//public:
//	Auto_ptr(const T* ptr = nullptr )
//		:_ptr(ptr)
//		,_pcount(new int(1))
//	{
//	}
//	Auto_ptr(const shared_ptr<T>& sp)
//		:_ptr(sp._ptr)
//		, _pcount(sp._pcount)
//	{
//		++(*_pcount);
//	}
//	Auto_ptr<T>& operator=(Auto_ptr<T>ptr)
//	{
//		reserv();
//		_ptr = ptr._ptr;
//		_pcount = ptr._pcount;
//		++(*_pcount);
//		return *this;
//	}
//	void reserv()
//	{
//		if (--(*_pcount)==0)
//		{
//			delete _ptr;
//			delete _pcount;
//		}
//	}
//private:
//	T* _ptr;
//	int* _pcount;
//};

namespace XiaoHai
{
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{
		}
		auto_ptr(auto_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			// 管理权转移 
			sp._ptr = nullptr;
		}
		auto_ptr<T>& operator=(auto_ptr<T>& ap)
		{
			// 检测是否为⾃⼰给⾃⼰赋值 
			if (this != &ap)
			{
				// 释放当前对象中资源 
				if (_ptr)
					delete _ptr;
				// 转移ap中资源到当前对象中 
				_ptr = ap._ptr;
				ap._ptr = NULL;
			}
			return *this;
		}
		~auto_ptr()
		{
			if (_ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
			}
		}
		// 像指针⼀样使⽤ 
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
	template<class T>
	class unique_ptr
	{
	public:
		explicit unique_ptr(T* ptr)
			:_ptr(ptr)
		{
		}
		~unique_ptr()
		{
			if (_ptr)
			{
				cout << "delete:" << _ptr << endl;
				delete _ptr;
			}
		}
		// 像指针⼀样使⽤ 
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		unique_ptr(const unique_ptr<T>&sp) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>&sp) = delete;
		unique_ptr(unique_ptr<T> && sp)
			:_ptr(sp._ptr)
		{
			sp._ptr = nullptr;
		}
		unique_ptr<T>& operator=(unique_ptr<T> && sp)
		{
			delete _ptr;
			_ptr = sp._ptr;
			sp._ptr = nullptr;
		}
	private:
		T* _ptr;
	};
	template<class T>
	class shared_ptr
	{
	public:
		explicit shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pcount(new int(1))
		{
		}

		template<class D>
		shared_ptr(T* ptr, D del)
			: _ptr(ptr)
			, _pcount(new int(1))
			, _del(del)
		{
		}
		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pcount(sp._pcount)
			, _del(sp._del)
		{
			++(*_pcount);
		}
		void release()
		{
			if (--(*_pcount) == 0)
			{
				// 最后⼀个管理的对象，释放资源 
				_del(_ptr);
				delete _pcount;
				_ptr = nullptr;
				_pcount = nullptr;
			}
		}
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr != sp._ptr)
			{
				release();
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				++(*_pcount);
				_del = sp._del;
			}
			return *this;
		}
		~shared_ptr()
		{
			release();
		}
		T* get() const
		{
			return _ptr;
		}
		int use_count() const
		{
			return *_pcount;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
		int* _pcount;
		//atomic<int>* _pcount;

		function<void(T*)> _del = [](T* ptr) {delete ptr; };
	};

	// 需要注意的是我们这⾥实现的shared_ptr和weak_ptr都是以最简洁的⽅式实现的， 
	// 只能满⾜基本的功能，这⾥的weak_ptr lock等功能是⽆法实现的，想要实现就要 
	// 把shared_ptr和weak_ptr⼀起改了，把引⽤计数拿出来放到⼀个单独类型，shared_ptr 
	// 和weak_ptr都要存储指向这个类的对象才能实现，有兴趣可以去翻翻源代码 
	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr()
		{
		}
		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get())
		{
		}
		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();
			return *this;
		}
	private:
		T* _ptr = nullptr;
	};
}



//int main()
//{
//	XiaoHai::auto_ptr<Date> ap1(new Date);
//	// 拷⻉时，管理权限转移，被拷⻉对象ap1悬空 
//	XiaoHai::auto_ptr<Date> ap2(ap1);
//	// 空指针访问，ap1对象已经悬空 
//	//ap1->_year++;
//	XiaoHai::unique_ptr<Date> up1(new Date);
//	// 不⽀持拷⻉ 
//	//unique_ptr<Date> up2(up1);
//	// ⽀持移动，但是移动后up1也悬空，所以使⽤移动要谨慎 
//	XiaoHai::unique_ptr<Date> up3(move(up1));
//	XiaoHai::shared_ptr<Date> sp1(new Date);
//	// ⽀持拷⻉ 
//	XiaoHai::shared_ptr<Date> sp2(sp1);
//	XiaoHai::shared_ptr<Date> sp3(sp2);
//	cout << sp1.use_count() << endl;
//	sp1->_year++;
//	cout << sp1->_year << endl;
//	cout << sp2->_year << endl;
//	cout << sp3->_year << endl;
//	return 0;
//}



struct ListNode
{
	int _data;
	std::shared_ptr<ListNode> _next;
	std::shared_ptr<ListNode> _prev;

	// 这⾥改成weak_ptr，当n1->_next = n2;绑定shared_ptr时 
	// 不增加n2的引⽤计数，不参与资源释放的管理，就不会形成循环引⽤了 
	/*std::weak_ptr<ListNode> _next;
	std::weak_ptr<ListNode> _prev;*/
	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};
int main()
{
	// 循环引⽤ -- 内存泄露 
	std::shared_ptr<ListNode> n1(new ListNode);
	std::shared_ptr<ListNode> n2(new ListNode);
	cout << n1.use_count() << endl;
	cout << n2.use_count() << endl;
	n1->_next = n2;
	n2->_prev = n1;
	cout << n1.use_count() << endl;
	cout << n2.use_count() << endl;
	// weak_ptr不⽀持管理资源，不⽀持RAII 
	// weak_ptr是专⻔绑定shared_ptr，不增加他的引⽤计数，作为⼀些场景的辅助管理 
	//std::weak_ptr<ListNode> wp(new ListNode);
	return 0;
}



int main()
{
	// 申请⼀个1G未释放，这个程序多次运⾏也没啥危害 
	// 因为程序⻢上就结束，进程结束各种资源也就回收了 
	char* ptr = new char[1024 * 1024 * 1024];
	cout << (void*)ptr << endl;
	return 0;
}



namespace XiaoHai
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _pcount(new int(1))
		{
		}
		template<class D>
		shared_ptr(T* ptr = nullptr, D del)
			: _ptr(ptr)
			, _pcount(new int(1))
			, _del(del)
		{
		}
		//sp2(sp1)
		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pcount(sp._pcount)
			, _del(sp._del)
		{
			++(*_pcount);
		}

		void release()
		{
			if (--(*_pcount) == 0)
			{
				_del(_ptr);
				delete _pcount;
			}
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr != sp._ptr)
			{
				release();
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				++(*_pcount);
				_del = sp._del;
			}
			return *this;
		}

		~shared_ptr()
		{
			//最后一个管理资源的对象释放
			release();
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			rerurn _ptr;
		}
		T& operator[](int i)
		{
			return _ptr[i];
		}
		T* get()const
		{
			return _ptr;
		}
		int pse_count()const
		{
			return *_pcount;
		}
	private:
		T* _ptr;
		int* _pcount;
		function<void(T*)>_del = [](T* ptr) {delete ptr; };
	};
}
int main()
{
	XiaoHai::shared_ptr<int>sp1(new int(1));
	XiaoHai::shared_ptr<int>sp2(sp1);
	XiaoHai::shared_ptr<int>sp3 = sp2;
	//shared_ptr<Date>
	return 0;
}