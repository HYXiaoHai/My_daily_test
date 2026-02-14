#define Unity5
#define Unity2017

#undef Unit4
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;


namespace MyObject
{
    class Program
    {
        static void Main()
        {
            #region arrayList 万物之父
            //万能数组 增添删改
            ArrayList array = new ArrayList();//声明

            array.Add(1);
            array.Add(2);
            array.Add("hahahah");
            array.Add(true);
            array.RemoveAt(2);//指定位置
            array.Remove(1);
            array.Contains(1);//判断是否存在1 返回true
            int x = array.IndexOf(2);//查找 未找到返回-1
            array.Insert(x, 1);//指定位置插入

            //遍历
            for (int i = 0; i < array.Count; i++)
            {
                Console.WriteLine(array[i]);
            }
            //迭代器遍历
            //var 智能指针
            foreach (object item in array)
            {
                Console.WriteLine(item);
            }

            //装箱拆箱
            int i = 1;
            array[0] = i;//装箱
            i = (int)array[0];//拆箱

            #endregion

            #region 栈stack 杯子

            //Stack<int> stack = new Stack<int>();
            Stack stack = new Stack();//万能版
            stack.Push(1);
            stack.Push(2);
            stack.Push(3);

            int a = stack.Pop();//弹出顶部
            int b = stack.Peek();//栈顶元素

            if (stack.Contains(1))
            {
                //查
            }

            //没有改
            //只有清空
            stack.Clear();

            //无法用for遍历
            foreach (var item in stack)
            {
                //由顶向下
                Console.WriteLine(item);
            }

            //另一种遍历
            object[] array1 = stack.ToArray();
            #endregion

            #region queue 队列
            Queue<object> queue = new Queue<object>();
            queue.Enqueue(1);//入队
            queue.Enqueue(2);
            queue.Enqueue(3);

            object o = queue.Dequeue();//取
            object o1 = queue.Peek();//返回堆头
            queue.Contains(1);//判断是否存在某一个元素

            //遍历同理

            #endregion

            #region hashtable哈希表
            Hashtable ht = new Hashtable();
            ht.Add(1, "123");
            ht.Add("123", 2);
            //不能出现相同的键

            ht.Remove("123");//移除对应的键

            Console.WriteLine(ht[2]);//[]里的是键 找不到返回空
            Console.WriteLine(ht.Contains(2));//查找是否存在2的键
            Console.WriteLine(ht.ContainsKey(2));//查找是否存在2的键
            Console.WriteLine(ht.ContainsValue(2));//查找是否存在2的值

            //遍历所有的键
            foreach (var item in ht.Keys)
            {
                Console.WriteLine(item);
            }

            //遍历所有的值
            foreach (var item in ht.Values)
            {
                Console.WriteLine(item);
            }
            //遍历所有的键值对
            foreach (DictionaryEntry item in ht)
            {
                Console.WriteLine(item.Key + ":" + item.Value);
            }

            //迭代器遍历
            IDictionaryEnumerator myEnumerator = ht.GetEnumerator();
            bool flag = myEnumerator.MoveNext();//
            while (flag)
            {
                Console.WriteLine(myEnumerator.Key + ":" + myEnumerator.Value);
                flag = myEnumerator.MoveNext();
            }

            #endregion

            #region 泛型
            //通过类型参数化来实现同一份代码上的操作多种类型
            //模板
            //    class TestClass<T>
            //{
            //    public T Value;
            //}
            //class TestClass2<T1, T2, T3>
            //{
            //    public T1 Value1;
            //    public T2 Value2;
            //    public T3 Value3;
            //}
            //interface ITestClass<T>
            //{
            //    void Foo();
            //    T Value { get; set; }
            //}
            //class Test : ITestClass<int>
            //{
            //    public int Value { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

            //    public void Foo()
            //    {
            //        throw new NotImplementedException();
            //    }

            //    public void TestFun<T>(T val)//函数
            //    {

            //    }
            //}


            #endregion

            #region 泛型约束 where
            ////让泛型的类型有一定限制
            ////1.值类型
            //class Test1<T> where T : struct
            //{
            //    public T Value;
            //    public void TestFunc<K>() where K : struct
            //    {

            //    }
            //}
            ////Test1<object> t1 = new Test1<object>();//object报错
            //Test1<int> t1 = new Test1<int>();

            ////2.引用类型
            //class Test2<T> where T : class
            //{
            //    public T Value;
            //    public void TestFunc<K>() where K : class
            //    {

            //    }
            //}
            //Test2<object> t2 = new Test2<object>();
            ////Test2<int> t2 = new Test2<int>();//int报错

            ////3.存在无参公共构造函数
            //class Test3<T> where T : new()
            //{
            //    public T Value;
            //    public void TestFunc<K>() where K : new()
            //    {

            //    }
            //}
            //class Test1
            //{

            //}
            //class Test2
            //{
            //    public Test2(int a)//无参构造被顶掉
            //    {

            //    }
            //}
            //Test3<Test1> t3 = new Test3<Test1>();
            ////Test3<Test2> t3 = new Test3<Test2>();//报错

            ////4.某个类型本身或其派生类
            //class Test4<T> where T : Test1
            //{
            //    public T Value;
            //    public void TestFunc<K>() where K : Test1
            //    {

            //    }
            //}
            //class Test3 : Test1
            //{

            //}
            //Test4<Test1> t4 = new Test4<Test1>();
            ////Test4<Test3> t4 = new Test4<Test3>();//均不报错

            ////5.某个接口的派生类型
            //interface IFly
            //{

            //}
            //class Test4 : IFly
            //{

            //}
            //class Test5<T> where T : IFly
            //{
            //    public T Value;
            //    public void TestFunc<K>() where K : IFly
            //    {

            //    }
            //}
            //Test5<Test4> t5 = new Test5<Test4>();
            //Test5<IFly> t51 = new Test5<IFly>();

            ////6.另一个泛型类型本身或者派生类型
            //class Test6<T, U> where T : U //自己和自己 或 自己和自己的派生类
            //{
            //    public T Value;
            //    public void TestFunc<K>() where K : U
            //    {

            //    }
            //}
            //Test6<Test4, IFly> t6 = new Test6<Test4, IFly>();//test4继承IFly

            ////约束的组合使用
            //class Test7<T> where T : class, new()
            //{

            //}

            ////多个泛型有约束
            //class Test8<T, K> where T : class where K : new()//中间没有逗号
            //{

            //}

            ////单例模式基类
            //class Manage<T> where T : class, new()
            //{
            //    static T _instance;
            //    public static T Instance()
            //    {
            //        if (null == _instance)
            //        {
            //            _instance = new T();
            //        }
            //        return _instance;
            //    }
            //}
            #endregion

            #region List
            List<int> list1 = new List<int>();
            list1.Add(1);
            list1.Add(2);
            list1.Add(3);
            list1.Add(4);

            list1.Remove(4);
            list1.RemoveAt(1);

            int index = list1.IndexOf(3);//返回位置或-1

            list1.Clear();

            //练习
            //    class Monster
            //    {
            //        public static List<Monster> monsters = new List<Monster>();
            //        public Monster()
            //        {
            //            monsters.Add(this);
            //        }
            //        public virtual void Attack()
            //        {

            //        }
            //    }
            //    class Boss : Monster {
            //    public override void Attack()
            //    {

            //    }
            //}
            //    class Gablin:Monster
            //{
            //    public override void Attack()
            //    {

            //    }
            //}


            //同arraylist

            #endregion

            #region Dictionary
            //同Hashtable
            Dictionary<int, string> dic = new Dictionary<int, string>();
            dic.Add(1, "ha");
            dic.Add(2, "haha");
            dic.Add(3, "hahaha");

            //增删查改同hashtable
            foreach (KeyValuePair<int, string> item in dic)
            {
                Console.WriteLine(item.Key + ":" + item.Value);
            }
            #endregion

            #region LinkedList
            //泛型双向链表
            LinkedList<int> list = new LinkedList<int>();
            list.AddLast(1);//尾部添加
            list.AddFirst(2);//头部添加
            list.AddFirst(10);//头部添加
            list.AddFirst(20);//头部添加



            list.Remove(2);//移除指定元素
            list.RemoveFirst();//移除头部
            list.RemoveLast();//移除尾部

            list.Clear();//清空

            LinkedListNode<int> first = list.First;//头
            LinkedListNode<int> last = list.Last;//尾

            LinkedListNode<int> node = list.Find(10);//找到20
            list.AddAfter(node, 15);//在结点后面插
            list.AddBefore(node, 15);//再借点前面插

            foreach (int item in list)
            {
                Console.WriteLine(item);
            }

            //结点遍历
            LinkedListNode<int> nowHead = list.First;
            while (nowHead != null)
            {
                Console.WriteLine(nowHead.Value);
                nowHead = nowHead.Next;
            }

            #endregion

            #region 泛型栈和队列
            Stack<int> stack1 = new Stack<int>();
            Queue<int> queue1 = new Queue<int>();

            //同object

            #endregion
        }
    }
    #region 委托 delegate 观察者设计模式
    // 函数（方法）的容器
    //用来传递函数的容器
    //本质是一个类，用来定义函数（方法）的类型
    //可以申明在namespace和class中

    //自定义委托
    //申明一个可以用来存储无参无返回值函数的容器
    //只是申明规则 并没有使用
    public delegate void MyFun();

    public delegate int MyFun1(int a);

    //委托常用在
    //1.作为类的成员
    //2.作为函数的参数

    //知识点5：
    //委托变量可以存储多个函数

    //多减不会报错
    //调用空的会报错


    //知识点6
    public class Test
    {
        public MyFun _fun;
        public MyFun _fun1;
        public MyFun1 _fun2;

        public void TestFun(MyFun fun, MyFun1 fun2)
        {
            //处理别的逻辑，当这些逻辑处理完了，在执行传入的函数
            int i = 1;
            i *= 2;
            i += 3;

            fun();
            fun2(i);

            this._fun = fun;
            this._fun2 = fun2;
        }
        //增
        public void AddFun(MyFun fun, MyFun1 fun1)
        {
            this._fun += fun;
            this._fun2 += fun1;
        }
        public void Remove(MyFun fun, MyFun1 fun1)
        {
            this._fun -= fun;
            this._fun2 -= fun1;
        }
    }
    class Program6
    {
        //使用委托 用来存函数
        static void Main()
        {
            MyFun f = new MyFun(Fun);
            //把Fun装载到了f；
            Console.WriteLine(1);
            Console.WriteLine(2);
            Console.WriteLine(3);
            Console.WriteLine(4);
            f.Invoke();//调用

            MyFun f2 = Fun;//记住了名字
            Console.WriteLine(1);
            Console.WriteLine(2);
            Console.WriteLine(3);
            Console.WriteLine(4);
            f2();//调用

            MyFun1 f3 = Fun2;
            f3(1);

            MyFun1 f4 = new MyFun1(Fun2);
            f4.Invoke(3);

            Test t = new Test();

            t.TestFun(Fun, Fun2);

            //委托变量可以存储多个函数
            MyFun ff = null;
            ff += Fun;
            ff += Fun;
            ff += Fun3;
            ff();//调用两次Fun 一次Fun3

            t.AddFun(Fun, Fun2);
            t._fun();
            t._fun2(50);

            //删
            t.Remove(Fun, Fun2);
            t._fun();
            t._fun2(10);
            //清空
            ff = null;
            if (ff != null)
            {
                ff();
            }

            //知识点6
            //系统自带的委托
            Action action = null;//void Fun()
            Func<string> func = null;//T Fun() ->string fun() 泛型委托
            Func<int, int> func1 = null;//int Fun(int x)类型的函数吗
            Action<int, string> action1 = null;//有参无返回值 void Fun(int,string ,.................)
        }
        static void Fun()
        {
            Console.Write("Fun");
        }
        static void Fun3()
        {
            Console.Write("Fun3");
        }
        static int Fun2(int value)
        {
            Console.WriteLine("Fun2" + value);
            return value;
        }
    }
        #endregion

        #region 事件 event
        //事件是委托的安全包裹
        //是特殊的变量类型

        //1.事件是作为 成员变量存在于类中
        //2.委托怎么用，时间就怎么用
        //事件相对委托的区别：
        //1.不能在类外部 赋值 只能 + -（+=也不行） 
        //2.不能在类外部 调用
        //3.事件不能作为 函数的临时变量

        //只能作为成员存在于类和接口以及结构体中

        //知识点3：
        //1.防止外部随意置空委托
        //防止外部随意调用委托
        //事件相当于对委托进行了封装 让其更安全
    class Test10()
    {
        //委托
        public Action myFun;

        //事件
        public event Action myEvent;
        public Test10()
        {
            myFun = TestFun;
            myFun += TestFun;
            myFun -= TestFun;
            myFun();

            myEvent = TestFun;
            myEvent += TestFun;
            myEvent -= TestFun;
            myEvent();
        }
        public void TestFun()
        {

        }
    }
    //class Program
    //{
    //    static void Main(string[] args)
    //    {
    //        Test10 t = new Test10();
    //        //委托可以在外部赋值
    //        t.myFun = null;
    //        t.myFun = TestFun;
    //        //事件不允许
    //        t.myEvent += TestFun;//可以+ - 函数

    //        //委托可以在外部调用
    //        t.myFun();
    //        //t.myEvent();//不允许
    //        //只能封装调用

    //        Action action = TestFun;
    //        //事件不能创建临时变量
    //        //event Action ae = TestFun;
    //    }

    //    static void TestFun()
    //    {

    //    }
    //}

    //练习
    //class ReShuiQI
    //{
    //    public 
    //    bool IsHot()
    //    {

    //    }
    //}

    //void Main()

    //{
    //    while (true)
    //    {

    //    }
    //}
    #endregion

    #region 匿名函数 delegate
    //没有名字的函数
    //主要配合委托事件
    //脱离委托事件

    //匿名函数的缺点
    //添加到委托或事件容器之后 不记录 无法单独移除
    class Program1
    {
        static void Main()
        {
            //真正调用它的时候，是这个委托容器啥时候调用 就什么时候调用这个匿名函数
            Action a = delegate ()
            {
                Console.WriteLine("匿名函数逻辑");
            };
            //2.有参
            Action<int, string> b = delegate (int a, string b)
            {
                Console.WriteLine("hahaha");
            };
            //3.有返回值
            Func<string> c = delegate ()
            {
                return "hahah";
            };
            //4.一般情况会作为函数参数传递 或者 作为函数返回值
            Test11 t = new Test11();
            t.Dosomting(100, delegate ()
            {
                Console.WriteLine("随参数传入");
            });

            Action fun = t.GetFun();
            fun();
            //一步到位
            t.GetFun()();

            Action ac3 = delegate ()
            {
            };

            ac3 += delegate ()
            {
            };
            ac3();
            //
            //添加到委托或事件容器之后 不记录 无法单独移除
            //不能 -= 只能清空
            ac3 -= ac3 += delegate ()
            {
            };
        }
        // 使用匿名方法版本
        static Func<int, int> CreateMultiplierAnonymous(int multiplier)
        {
            // 使用匿名方法
            return delegate (int x)
            {
                return x * multiplier;
            };
        }
    }

    class Test11
    {
        public Action action;
        //参数传递
        public void Dosomting(int a, Action fun)
        {
            Console.WriteLine(a);
            fun();
        }
        //返回值
        public Action GetFun()
        {
            return delegate
            {
                Console.WriteLine();
            };
        }
    }
    #endregion

    #region lambad表达式
    //闭包
    //内层的函数可以引用包含在他外层的函数变量
    //即使外层函数的执行已经中止
    //注意：
    //该变量提供的值并非变量创建的值，而是在夫函数范围内的最终值
    class Program2
    {
        static void Main()
        {
            Action a = () =>
            {
                Console.WriteLine('a');
            };

            Action<int> a2 = (int value) =>
            {
                Console.WriteLine(value);
            };
            Action<int> a3 = (value) =>
            {
                Console.WriteLine(value);
            };
            //有返回值 有参数
            Func<string, int> a4 = (value) =>
            {
                return 1;
            };

            Test12 test12 = new Test12();
            test12.DoSomting();


            Action<int> action2 = (int value) =>
            {
                Console.WriteLine(value);
            };

            // 获取一个从1开始打印的委托
            Action printFrom1 = CreateNumberPrinter(1);
            printFrom1(); // 打印1~10
        }
        #region 练习
        static Action CreateNumberPrinter(int start)
        {
            // 使用闭包记住起始值
            int current = start;

            return () =>
            {
                for (int i = 0; i < 10; i++)
                {
                    Console.WriteLine(current + i);
                }
            };
        }
        #endregion

    }
    class Test12
    {
        public event Action action;
        public Test12()
        {
            int value = 0;
            //形成了闭包
            //当构造函数完毕时，value生命周期被改变
            action = () =>
            {
                Console.WriteLine(value);
            };

            for (int i = 0; i < 10; i++)
            {
                action += () =>
                {
                    Console.WriteLine(i);//打印的值都是10 i 的 最终值
                };
            }
        }
        public void DoSomting()
        {
            action();
        }
    }
    #endregion

    #region List排序
    class Program3
    {
        static void Main()
        {
            List<int> list = new List<int>();
            list.Add(4);
            list.Add(2);
            list.Add(3);
            list.Add(1);

            list.Sort();//默认排序

            //自定义类排序1
            List<Item> items = new List<Item>(10);
            items.Add(new Item(20));
            items.Add(new Item(45));
            items.Add(new Item(30));
            items.Add(new Item(100));
            items.Add(new Item(50));
            items.Add(new Item(32));
            items.Sort();

            //自定义类排序2 比较函数
            List<ShopItem> shopitems = new List<ShopItem>(1);
            shopitems.Add(new ShopItem(2));
            shopitems.Add(new ShopItem(5));
            shopitems.Add(new ShopItem(6));
            shopitems.Add(new ShopItem(10));
            shopitems.Add(new ShopItem(8));
            shopitems.Add(new ShopItem(7));
            shopitems.Add(new ShopItem(9));
            shopitems.Sort(SortShopItem);
            shopitems.Sort((ShopItem a, ShopItem b) =>
            {
                return a._id - b._id; //升序 
            });//匿名函数

        }
        //比较函数
        static int SortShopItem(ShopItem a, ShopItem b)
        {
            return a._id - b._id; //升序 
        }
    }

    class Item : IComparable<Item>
    {
        public int _value;
        public Item(int value)
        {
            _value = value;
        }

        public int CompareTo(Item other)
        {
            //小于零：
            //放入传入对象的前面
            //等于0：保持当前位置不变
            //大于0：相反

            //传入对象的位置 就是0
            //返回为负数 就放在他的 前面
            return _value - other._value;//升序排列
            //升序就是this - other
            //降序相反
        }
    }

    class ShopItem
    {
        public int _id;
        public ShopItem(int id)
        {
            _id = id;
        }
    }
    #endregion

    #region 协变out 逆变in
    //协变：out
    //和谐的变化
    //子类变父类
    //父类泛型委托装子类泛型委托
    //string 变成 object

    //逆变：in
    //父类变子类
    //子类泛型委托装父类泛型委托
    //object 变成 string

    //只有泛型接口 和 泛型委托才能使用

    #region 作用
    //1.返回值 和 参数
    //用out修饰的泛型 只能作为返回值
    delegate T TestOut<out T>();
    //用in修饰的泛型 只能作为参数
    delegate void TestIn<in T>(T t);

    //class Test<in T>//报错
    //{

    //}

    //2.结合里氏替换原则
    //out:子委托必须作为返回值传递给父
    //in：兹委托必须作为参数传递给父
    class Father
    {

    }
    class Son:Father
    {

    }

    //
    #endregion
    class Program4
    {
        static void Main()
        {

            //2.结合里氏替换原则
            //自己判断是否有父子关系
            //son -> father
            TestOut<Son> os = () =>
            {
                return new Son();
            };

            TestOut<Father> of = os;
            Father f = of();//实际上 返回的 是os里装的函数 返回的是Son；

            //逆变
            TestIn<Father> iF = (value) =>
            {
            };

            TestIn<Son> iS = iF;
            iS(new Son());//实际上调用的是iF
        }
    }
    #endregion

    #region 多线程 Thread
    //打开一个应用程序就是打开一个进程
    //进程包含线程

    //多线程就是多开一条执行代码的管道

    class Program5
    {
        static bool isrunning = true;

        static object obj = new object();
        static void Main()
        {
            //新线程 将要执行的代码逻辑 封装到了一个函数语句块中
            Thread t = new Thread(NewThreadLogic);//声明

            t.Start();//启动//默认为前台线程
                      //后台线程
                      //当前台线程结束的时候，整个程序就结束了，即使后台线程正在运行
                      //后台线程不会防止应用程序的进程被终止掉
            t.IsBackground = true;//设置后台线程 //主线程结束 后台线程也默认结束

            //关闭释放一个线程
            //当线程执行完 不用可以的去关闭它
            t = null;
            //如果是死循环：
            //1.死循环中加个bool标识
            isrunning = false;
            //2.通过线程提供的方法 不建议
            t.Abort();//终止线程
            t = null;

            //5.线程的休眠 毫秒数 暂停
            //
            Thread.Sleep(1000);//1s

            //线程使用的内存是共享的 都属于该进程
            //可以加锁 lock
            //为了避免逻辑顺序的差错
            //
            while(true)
            {
                lock(obj)//检查obj是否会被锁住 //一定是引用类型
                {
                    Thread.Sleep(1000);
                    Console.WriteLine("Main Thread");
                }
            }

            //多线程用于 寻路 网络通信
        }
        static void NewThreadLogic()
        {
            //新开线程
            while (isrunning)
            {
                lock (obj)
                {
                    Thread.Sleep(1000);
                    Console.WriteLine("new Thread");
                }
        
            }
        }
    }
    #endregion

    #region 预处理器指令
    //以#开始
    //1.
    //#define
    //定义符号 一般放在最开始的地方
    //#undef
    //一般配合if使用
    //可以用来做跨平台
    //

    //2.
    //#waring
    //#error
    //告诉编译器
    //是报警告 还是 错误
    //配合if使用
    class Program6
    {
        static void Main()
        {
            //在实际编译之前，就对代码预处理
#if Unity5//判断是否存在Unity5符号 就把包含的代码翻译成二进制文件。
            Console.WriteLine("Unity5");
#elif Unity2017 || IOS
            Console.WriteLine("Unity2017");
#warning 这个版本不行
#else
            Console.WriteLine("其他版本");
#endif
        }
    }

    #endregion

    #region 反射 关键类Type
    //程序集
    //.exe(可执行文件)  .dll(库文件)

    //元数据
    //程序中的类，类中的函数，变量等等信息就是 程序的 元数据
    //有关程序以及类型的数据被称为 元数据  他们保存在程序集中

    //反射
    //在程序运行时，通过反射可以得到其他程序或者自己程序集代码的各种信息
    //类 函数 变量 对象 等 ，实例化 执行 操作他们

    //反射的作用
    //1.程序运行时得到所有的元数据，包括元数据的数据
    //2.程序运行时，实例化对象，操作对象
    //3.程序运行时创建新对象，用这些对象执行任务
    //可以在一个程序里 使用 另一个程序集里的函数（用别人的代码）unity里工作的基本原理
    class Test17
    {
        private int i = 1;
        public int j = 0;
        public string _str = "1234";
        public Test17()
        {

        }

        public Test17(int ii)
        {
            i = ii;
        }
        public Test17(int ii, string str):this(ii)
        {
            this._str = str;
        }

    }
    class Program7
    {
        static void Main()
        {
            //Type
            //访问元数据的主要方式
            //使用type成员获取有关声明的信息
            //有关类型成员（构造函数 方法）
            int a = 42;
            Type type = a.GetType();
            Console.WriteLine(type);//System.42 int类信息
            Type type2 = typeof(int);//得到int类型的type
            Type type3 = Type.GetType("System.Int32");//必须要包含命名空间  获取其他人的程序集
            //type type2 type3所指向的堆空间是相同的

            //得到类的程序集信息
            Console.WriteLine(type.Assembly);

            //获取类的所有公共类成员
            Type t = typeof(Test17);
            //需要引用命名空间
            MemberInfo[] infos = t.GetMembers();//获取所有公共public成员

            ConstructorInfo[] ctors = t.GetConstructors();//获取类的公共构造函数

            //获得一个构造函数
            //获得 Type数组 数组中内容按顺序是参数类型
            //使用 object数组 标识按顺序传入的参数
            ConstructorInfo info = t.GetConstructor(new Type[0]);//无参构造
            info.Invoke(null);//执行无参构造 返回object
            Test17 obj = info.Invoke(null) as Test17;
            Console.WriteLine(obj.j);

            ConstructorInfo info2 = t.GetConstructor(new Type[] { typeof(int)});//一个int类型的有参构造
            obj = info2.Invoke(new object[]{ 2})as Test17;
            ConstructorInfo info3 = t.GetConstructor(new Type[] { typeof(int),typeof(string)});//一个int类型 一个 string类型的有参构造
            obj = info3.Invoke(new object[]{3,"444"})as Test17;


            FieldInfo[] fields = t.GetFields();//公共成员变量
            for(int i =0;i<fields.Length;i++)
            {
                Console.WriteLine(fields[i]);
            }
            FieldInfo infoJ = t.GetField("j");//获取j
            Console.WriteLine(infoJ);

            //////////////////////////////////////////////////////////////////////////////////////////////////////

            //3.通过反射获取和设置对象的值
            Test17 test = new Test17();
            test.j = 99;
            test._str = "abc";  
            Console.WriteLine(infoJ.GetValue(test));//获得某个变量的值
            infoJ.SetValue(test,100);//设置值

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            Type strType = typeof(string);
            MethodInfo[] methods = strType.GetMethods();//获取类中的公共方法
            //如果存在方法重载 用Type数组标识参数类型
            MethodInfo  subStr = strType.GetMethod("Substring",new Type[] {typeof(int),typeof(int)});//获取一个
            //调用
            string str = "hello,World";
            //第一个参数 相当于 是哪个对象要执行
            //如果是静态方法 第一个参数就是null
            object result = subStr.Invoke(str,new object[] { 7,5});// = str.Substring(7, 5);


        }

    }

    #endregion

    #region 反射 Assembly Activator
    //Assembly
    //用来加载其他程序集，加载后才能使用type
    //比如 dll文件
    //

    //Activator
    //用于快速实例化对象的类
    //用于将Type对象快捷实例化为对象
    //先得到type
    class Program8
    {
        static void Main()
        {
            //Activator
            //先得到type
            Type test = typeof(Test17);
            //1.无参构造
            Test17 obj = Activator.CreateInstance(test) as Test17 ;
            Console.WriteLine (obj._str);
            //2.有参构造
            obj = Activator.CreateInstance (test,99) as Test17 ;//Test17(int i)有参构造
            Console.WriteLine(obj.j);
            obj = Activator.CreateInstance (test,99,"111222") as Test17 ;//Test17(int i,string str)有参构造
            Console.WriteLine(obj.j);

            //Assembly
            Assembly assembly = Assembly.Load("程序集名称");//同一个工程路径下的
            Assembly assembly1 = Assembly.LoadFrom("包含程序集清单的文件的名称或路径");
            Assembly assembly2 = Assembly.LoadFile("要加载文件的完全限定路径");

            //类库文件
            //dll
            //运行后打包成dll 用来纯写代码的
            Assembly assemblyMy = Assembly.LoadFrom("D:\\a VS编程\\GitHub\\My_daily_test\\C#Practice2\\MyClassLibrary\\bin\\Debug");
            Type myplayer = assembly1.GetType("MyClassLibrary.dll");
        }
    }
    #endregion

    #region 特性 Attribute
    //是允许我们向程序的程序集添加元数据的语言结构
    //用于保存程序结构信息的某种特殊类型的类

    //就是为元数据添加额外的信息
    //之后也可以通过反射来获取

    class MyCustomAttribute :Attribute//自定义特性
    {
        public string _info;
        public MyCustomAttribute(string info)
        {
            this._info = info;
        }
        public void Test()
        {
            Console.WriteLine("MyCustomAttribute - Test");
        }
    }
    //限制自定义特性的使用范围
    [AttributeUsage(AttributeTargets.Class|AttributeTargets.Struct,AllowMultiple =true,Inherited =true)]
    //AttributeTargets 特性能够使用在什么地方
    //AllowMultiple 是否允许多个特性用在同一个目标上
    //Inherited 能否被派生类和重写成员继承
    class MyCustom2Attribute :Attribute//自定义特性
    {
        public string _info;
        public MyCustom2Attribute(string info)
        {
            this._info = info;
        }
        public void Test()
        {
            Console.WriteLine("MyCustomAttribute - Test");
        }
    }

    //使用
    //标识他们具有该特性的声明
    [MyCustom("这个是我自己写的一个用于计算的类")]
    class MyClass
    {
        [MyCustom("数值变量")]
        public int value;
        
        [MyCustom("加法")]
        public void TestFun([MyCustom("函数参数")]int a)
        {

        }
    }
    //系统自带的特性
    //1.过时特性
    class TestClass
    {
        //true:使用该方法会报错
        //false:报错
        [Obsolete("已过时", false)]
        public void OldSpeak(string str)
        {

        }
        public void Speak(string str)
        {

        }
        //2.可以看清执行函数的位置
        public void SpeakerCaller(string str, [CallerFilePath] string filename = "", [CallerLineNumber] int line = 0, [CallerMemberName] string target = "")
        {

        }

    }
    class Program9
    {
        //3.用来调用c或c++的dll包的方法
        [DllImport("Test.dll")]
        public static extern int Add(int a,int b); 
        //4.条件编译
        //如下 要有#define Fun 才能编译函数
        [Conditional("Fun")]
        static void Fun()
        {

        }
        static void Main()
        {
            //特性使用
            MyClass mc = new MyClass();
            Type t = mc.GetType();
            //判断是否使用特性                  是否搜索继承链
            if(t.IsDefined(typeof(MyCustomAttribute),false))
            {
                Console.WriteLine("使用");
            }

           object[] array =  t.GetCustomAttributes(false);//获得所有的特性
            for (int i = 0; i < array.Length; i++)
            {
                if (array[i] is  MyCustomAttribute)
                {
                   
                    Console.WriteLine((array[i] as MyCustomAttribute)._info);
                }
            }

        }
    }
    #endregion

    #region 迭代器 iterator
    
    class CustomList : IEnumerable, IEnumerator
    {
        private int[] list;

        private int index = -1;//光标 默认-1 用于表示数据得到了哪个位置
        public CustomList()
        {
            list = new int[] { 1, 2, 3, 4, 5, 6, 7, 8 };
        }

        public object Current
        {
            get
            {
                return list[index];//获取元素
            }
        }
        public IEnumerator GetEnumerator()//
        {
            Reset();
            return this;
        }

        public bool MoveNext()//移动光标到下一个 光标类比指针
        {
            //移动光标
            ++index;
            return index < list.Length;//是否溢出
        }

        public void Reset() //重置光标 一般写在GetEnumerator里
        {
            index = -1;
        }
    }

    //泛型
    class CustomList2<T> : IEnumerable
    {
        private T[] list;

        private int index = -1;//光标 默认-1 用于表示数据得到了哪个位置
        public CustomList2(params T[] values)
        {
            list= values;
        }

        public IEnumerator GetEnumerator()
        {
            for (int i = 0; i < list.Length; ++i)
            {
                yield return list[i];//语法糖
                                     // yield return配合迭代器使用
                                     //可以理解为 暂时返回 保留当前的状态
                                     //一会还会回来

                //yield return 生成代码的时候 还是会自动生成MoveNext等 系统自己完成后续
            }
        }
    }
    class Program10
    {
        static void Main()
        {
                CustomList custom = new CustomList();
                CustomList2<int> custom2 = new CustomList2<int>(1,2,3,4,5);

                //foreach本质：
                //1.先获取in后面这个对象的IEnumerator
                // 会调用GetEnumerator方法
                //2.执行得到IEnumerator对象中的MoveNext方法
                //3.只要MoveNext返回true 就会得到Current 然后赋值给Item
                //4.若是false则退出循环
                foreach (int Item in custom)
                {
                    Console.WriteLine(Item);
                }

                foreach (int Item in custom2)
                {
                    Console.WriteLine(Item);
                }
        }
    }
    #endregion

    #region 特殊语法
    class Person
    {
        private int money;
        public bool sex;
        public string Name
        {
            get;
            set;
        }
        public int Age
        {
            get;
            set;
        }
    }
    class Program11
    {
        static void Main()
        {
            //1.var
            //var必须初始化
            //var不能作为类的成员 只能用于临时变量申明
            var i = 10;
            var str = "string";
            var array = new int[] { 1, 2, 3, };

            //2.申明对象时可以直接通过大括号的形式初始化公共成员变量和属性
            Person p = new Person(){sex = true, Age = 18,Name = "666", };

            //3.设置集合的初始值
            int[] array2 = new int[] { 1, 2, 3, 4, 5 };
            List<int> ints = new List<int>() { 1,2,3,5};
            Dictionary<int,string>dic = new Dictionary<int, string>()
            {
                {1,"123"},
                {2,"123"}
            };

            //4.匿名类型
            //临时类
            var v = new { age = 10, money = 11, name = "hah" };

            //5.可空类型
            //a.值类型不能赋为空
            //int c =null
            //b.申明时 在值类型后面加？ 可以赋值为空
            int? c = null;
            //c.判断是否为空
            if(c.HasValue)
            {

            }
            //d.获得可空类型值
            int? value = null;
            Console.WriteLine(value.GetValueOrDefault(100));//若为空

            object o = null;
            o?.ToString();//语法糖，自动判断是否为空

            //e.空合并操作符
            //三目运算符的简便写法
            int? intv = null;
            int intI = intv == null ? 100 : intv.Value;
            intI = intv ?? 100;

            //f.内插字符串
            string name = "XiaoHai";
            int age = 10;
            Console.WriteLine($"好好学习,{name},AGE:{age}");

            //g.单句逻辑简略法
            //if while 同理
            //public string Name
            //{
            //    get => "唐老师";
            //    set => Console.WriteLine(1);
            //}

            int Add(int x, int y) => x + y;
        }
    }
    #endregion

    #region 值类型 和 引用类型2
    //值类型
    //char bool
    //enum
    //struct

    //引用类型
    //委托
    //class
    //interface
    //数组
    //string

    //值类型跟着大哥走 引用类型一根筋

    //利用里氏替换原则 用接口容器装在结构体存在装箱拆箱
    #endregion

    #region 插入排序

    #endregion

    #region 希尔排序

    #endregion

    #region 归并排序

    #endregion

    #region 正则表达式
    //模式          含义                   示例
    //\d            数字                   \d{4} → 四位数
    //\w	        字母/数字/下划线       \w+ → 单词
    //.	            任意字符（除换行）     a.b → a+任意+b
    //*	            0次或多次	           ab*c → ac, abc, abbc
    //+	            1次或多次	           ab+c → abc, abbc
    //?	            0次或1次	           colou?r → color, colour
    //{n, m}	    n到m次                 \d{2,4} → 2~4位数字
    //[abc]         字符集                 gr[ae]y → gray, grey
    //^	            开始（或取反在[] 中） ^abc → 以abc开头
    //$	            结尾	               xyz$ → 以xyz结尾
    //( )	        捕获组	               (\d+)px → 提取数字
    class Program12
    {
        static void Main()
        {
            string input = "HP: 150/200";
            // 判断：是否以HP开头
            bool hasHp = Regex.IsMatch(input, "^HP");  // true

            // 提取：当前血量和最大血量
            Match match = Regex.Match(input, @"HP:\s*(\d+)/(\d+)");
            if (match.Success)
            {
                int current = int.Parse(match.Groups[1].Value); // 150
                int max = int.Parse(match.Groups[2].Value);     // 200
            }
            // 替换：屏蔽敏感词
            string chat = "笨蛋，你作弊";
            string filtered = Regex.Replace(chat, "笨蛋|作弊", "***"); // "***，你***"

            // 分割：按标点拆分
            string[] words = Regex.Split("a,b;c", "[,;]"); // ["a","b","c"]
        }
    }

    #endregion

    #region 文件操作
    class Program13
    {
        static void Main()
        {
            FileInfo myfile = new FileInfo(@"目录地址");
            DirectoryInfo info = new DirectoryInfo(myfile.FullName);
            myfile.CopyTo(@"复制地址");
            //File.Copy();
            myfile.Create();//增加文件夹creat

            myfile.Delete();

            //流
            FileStream read = new FileStream(@"路径",FileMode.Open,FileAccess.Read);//路径 方式 权限
            //read.ReadByte();//读取一个字节

            FileStream write = new FileStream("", FileMode.Create, FileAccess.Write);
            //write.WriteByte();

            while(true)
            {

            }
        }
    }
    #endregion
}


