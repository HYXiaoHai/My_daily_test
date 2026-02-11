using System;
using System.Text;
#region 二维数组

//int[,] arr = new int[2, 3];//二维数组
//int[][] arr1 = new int[2][];//交错数组[行数][（不写）]   每一行的列是可以不同的
//int[][] arr2 = new int[3][]{new int[] {1,2,3},
//                             new int[] {1,2}, 
//                             new int[] {1}};


#endregion

#region 值和引用类形

//int a = 10;//值类型
//int[] arr1 = new int[]{1,2,3,4};//引用类型

//int b = a;
//int[] arr2 = arr1;
//Console.WriteLine("a={0},b ={1}",a,b);
//Console.WriteLine("arr1[0]={0},arr2[0] ={1}", arr1[0], arr2[0]);

//b = 20;
//arr2[0] = 5;
//Console.WriteLine("a={0},b ={1}", a, b);
//Console.WriteLine("arr1[0]={0},arr2[0] ={1}", arr1[0], arr2[0]);

//int[] a = new int[] { 10 };
//int[] b = a;
//b = new int[5];
//Console.WriteLine(a[0]);

#endregion

#region ref和out
//买票上车 上车买票
//ret传入的变量必须初始化 out不用
//out传入的变量必须在内部赋值 ret不用

//用作函数内部 改值 或 重新申明 能够影响外部传入的变量,让其也被修改.
using System.Diagnostics.Metrics;
using System.Security.Cryptography;
using System.Text;

static void ChangeValue(int value)
{
    value = 3;
}
//ref
static void ChangeValue1(ref int value)
{
    value = 3;
}
//out
static void ChangeValue2(out int value)
{
    value = 99;
}

static void ChangeArrayValue(int[] value)
{
    value[0] = 99;
}
static void ChangeArrayValue1(int[] value)
{
    value = new int[] { 1, 2, 3 };
}
static void ChangeArrayValue2(ref int[] value)
{
    value = new int[] { 100, 200, 300 };
}

static void ChangeArrayValue3(out int[] value)
{
    value = new int[] { 999, 200, 300 };
}

//static void Main(string[] args)
//{
//    int a = 1;
//    ChangeValue(a);
//    Console.WriteLine(a);//1

//    ChangeValue1(ref a);
//    Console.WriteLine(a);//3

//    ChangeValue2(out a);
//    Console.WriteLine(a);//3

//    int[] arr2 = { 1, 2, 3 };
//    ChangeArrayValue(arr2);
//    Console.WriteLine(arr2[0]);//99

//    ChangeArrayValue1(arr2);
//    Console.WriteLine(arr2[0]);//99

//    ChangeArrayValue2(ref arr2);
//    Console.WriteLine(arr2[0]);//100

//    ChangeArrayValue3(out arr2);
//    Console.WriteLine(arr2[0]);//100
//}


#endregion

#region 变长参数 和 默认参数 和 函数重载
//params 后面必须为数组
//函数中 只能出现一个params关键字 并且一定是在最后一组参数 前面可以有n个其他参数.


//有参数默认值的参数 一般称为可选参数
//作用是 当调用函数时可以不传参数(c++默认参数)
//默认参数必须在 非默认参数的后面

//函数重载
//与返回类型无关 只和 参数类型 数量 顺序

//函数名相同 参数数量不同
//参数数量相同 类型不同 
//数量相同 顺序不同(有类型差异
//params ref out都算新的
//static int Sum(params int[] arr)
//{
//    int sum = 0;
//    for (int i = 0; i < arr.Length; i++)
//        sum += arr[i];
//    return sum;
//}

//static void Speak(string str = "hahahaha")
//{

//}
//可以传入Sum{1,2,3,4,5,6};
//可以传入Sum{};
#endregion
#region 递归
//static int num(int a)
//{
//    Console.WriteLine(a);

//    if (a==1)
//    {
//        return 1;
//    }
//    return a*num(a-1);
//}

//    int num1 = num(5);
//    Console.WriteLine(num1);//100
#endregion


#region 冒泡

////int[] a = new int[] { 1, 4, 7, 3, 10, 8, 7 };
//int[] a = new int[] { 10,1, 2, 3, 3, 7 ,8};

//for(int i =0;i<a.Length;i++)
//{
//    int flag = 1;
//    for(int j =0;j<a.Length-1-i;j++)
//    {
//        if (a[j] > a[j+1])
//        {
//            flag = 0;
//            int tmp = a[j];
//            a[j] = a[j+1];
//            a[j + 1] = tmp;
//        }
//    }
//    if (flag == 1)
//    {
//        break;
//    }
//}

//for(int i =0;i<a.Length;i++)
//{
//    Console.WriteLine(a[i]);//100
//}

#endregion

#region 选择排序

//int[] a = new int[] { 1, 4, 7, 3, 10, 8, 7 };
////int[] a = new int[] { 10,1, 2, 3, 3, 7 ,8};

//for(int i =0;i<a.Length;i++)
//{
//    int index = i;
//    for(int j =i+1;j<a.Length-i;j++)
//    {
//        if (a[index] < a[j])
//        {
//            index = j; 
//        }
//        if(j == a.Length-1-i)
//        {
//            int tmp = a[index];
//            a[index] = a[j];
//            a[j] = tmp;
//        }
//    }
//}

//for(int i =0;i<a.Length;i++)
//{
//    Console.WriteLine(a[i]);//100
//}

#endregion
#region 类

//class Gameobject
//{
//   Gameobject() { val = 1; }
//   public int val;
//}
//Gameobject A = new Gameobject();
//Gameobject B = A;
//B.val =2;

//Gameobject A = new Gameobject();
//Gameobject B = A;
//B = null;

//Gameobject A = new Gameobject();
//Gameobject B = A;
//B = new Gameobject();

#endregion

#region 垃圾回收

//托管堆：C# 中引用类型对象分配在托管堆上。托管堆是由 CLR 管理的内存区域。

//代际回收：.NET 的垃圾回收器使用代际回收算法。它将堆中的对象分为三代：

//第0代：新创建的对象。这些对象通常生命周期很短。

//第1代：经过一次垃圾回收后仍然存活的对象。

//第2代：经过多次垃圾回收后仍然存活的对象，通常是长生命周期对象。
//垃圾回收通常首先回收第0代，如果回收后释放的内存不足，则回收第1代，依此类推。

//回收触发条件：垃圾回收在以下情况下可能会被触发：

//第0代堆已满

//调用 GC.Collect() 方法（通常不建议手动调用）

//系统内存不足

//应用程序域卸载

//CLR 关闭等

//垃圾回收过程：垃圾回收过程包括以下步骤：

//标记：从根对象（如全局对象、静态对象、局部变量、CPU寄存器等）开始，标记所有可达对象。

//清理：回收不可达对象所占用的内存。对于不可达的对象，如果是非托管资源，需要手动释放（通过终结器或 IDisposable 接口）。

//压缩（可选）：移动存活对象，以减少堆碎片，但这会影响性能。


//手动触发
//在Loading条的时候调用
GC.Collect();

#endregion

#region 成员属性

//1.用于保护成员变量
//2为成员属性的获取和赋值添加逻辑处理
//解决3p问题
//class Person
//{
//    private int age;
//    private int money;
//    private string name;

//    public string Name
//    {
//        get
//        {
//            return name;//从外面获取private
//        }
//        set
//        {
//            //可以设置之前添加一些逻辑规则
//            //value 关键字 用于标识 外部传入的值
//            name = value;
//        }
//    }
//    //public int Age
//    //{
//    //    get
//    //    {
//    //        //加密处理
//    //        return age -5;
//    //    }
//    //     set
//    //    {
//    //        //加密处理
//    //        age = value+5;
//    //    }
//    //}
//    //
//    public int Age//外面不让改
//    {
//        get
//        {
//            //加密处理
//            return age -5;
//        }
//        private set
//        {
//            //加密处理
//            age = value+5;
//        }
//    }
//    public int Money//外面只能得
//    {
//        get
//        {
//            return money;
//        }
//    }

//    //自动属性
//    //如果只西洼港外部能得不能改的 又没什么特殊处理 （不需要设置成员变量）
//    public float Hight
//    {
//        get;
//        private set;

//    }
//}

//class Program
// {
//    static void Main(string[] args)
//    {
//        Person p = new Person();
//        p.Name = "Test";//修改
//        p.Age = 5;//修改
//    }
//}

#endregion

#region 索引器
//可以让我们以[]的形式范围自定义类中的元素 规则自己顶 访问时和数组一样
//比较适用于在类中有数组变量时使用 可以方便访问
//支持重载
//namespace suoyinqi
//{
//    class Person
//    {
//        private int age;
//        private int money;
//        private string name;
//        private Person[] friends;

//        //索引器
//        //public Person this[int index]
//        //{
//        //    get
//        //    {
//        //        return friends[index];
//        //    }
//        //    set
//        //    {
//        //        friends[index] = value;
//        //    }
//        //}

//        //索引器可以写逻辑
//        public Person this[int index]
//        {
//            get
//            {
//                if(friends == null)
//                {
//                    return null;
//                }
//                else if(friends.Length -1<index)
//                {
//                    return null;
//                }
//                    return friends[index];
//            }
//            set
//            {
//                if (friends == null)
//                {
//                    friends = new Person[] { value};
//                }
//                friends[index] = value;
//            }
//        }
//    }
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Person p = new Person();
//            p[0] = new Person();//索引器的使用
//        }
//    }
//}


#endregion

#region 静态成员
////static 不需要实例化 程序运行时自动保存静态存储区（唯一的） 与程序同生共死
////静态函数不能使用非静态成员变量
////静态函数能使用静态成员变量
////const是特殊的static
////const必须初始化不能修改
////const只能修饰变量
////const一定写在访问修饰符后面的，static没有这个要求

////作用：
////常用的唯一的变量的声明
////方便别人获取的对象申明
////静态使用越多 对内存占用的越多
//class Test
//{
//    //静态成员变量
//    public static float PI = 3.1415926f;
//    public int testInt = 100;

//    public static float  CalcCircle(float r)
//    {
//        return PI*r*r;
//    }
//    public void TestFun()
//    {
//        Console.WriteLine("66666");
//    }
//}
////静态变量的使用(直接点出来)
//Test.PI;//
//Test.CalcCircle(2);

#endregion
#region 静态类 和 静态构造方法
//static 不需要实例化 程序运行时自动保存静态存储区（唯一的） 与程序同生共死
//静态函数不能使用非静态成员变量
//静态函数能使用静态成员变量
//const是特殊的static
//const必须初始化不能修改
//const只能修饰变量
//const一定写在访问修饰符后面的，static没有这个要求

//作用：
//常用的唯一的变量的声明
//方便别人获取的对象申明
//静态使用越多 对内存占用的越多
class Test
{
    //静态成员变量
    public static float PI = 3.1415926f;
    public int testInt = 100;

    public static float CalcCircle(float r)
    {
        return PI * r * r;
    }
    Test()//普通构造
    {

    }
    static Test()//静态构造函数 在第一次使用的时候
    {

    }
    public void TestFun()
    {
        Console.WriteLine("66666");
    }
}
//静态变量的使用(直接点出来)
Test.PI;//
Test.CalcCircle(2);

#endregion
#region 拓展
//为现有非静态 变量类型 添加 新方法

//不需要再对象中重写方法
//不需要继承来添加方法
//为别人封装的类型写额外的方法

//写在静态类中
//一定是一个静态类
//第一个参数为推展目标
//第一个参数用this指标

//static class Tools
//{
//为int拓展一个成员方法
//成员方法 是需要 实例化对象后 才能使用的
//value 代表 使用该方法的 实例化对象
//    public static void SpeakValue(this int value)
//    {
//        Console.WriteLine("拓展方法" + value);
//    }

//    public static void SpeakValue1(this string str1,string str2)
//    { 
//        Console.WriteLine("为string拓展"+str1+"66"+str2);
//    }

//    public static void Fun3(this Test T)
//    {
//        Console.WriteLine("为Test拓展" );
//    }

//}

//class Test()
//{
//    public int i = 10;
//    public void Func1()
//    {
//        Console.WriteLine("Func1");

//    }
//    public void Func2()
//    {
//        Console.WriteLine("Func1");

//    }

//    static void Main()
//{
//    int i = 10;
//    i.SpeakValue();
//    string str = "0000";
//    str.SpeakValue1("111");
//        Test T = new Test();
//        T.Fun3();
//}


#endregion

#region 运算符重载
//operation
class Point
{
    public int x;
    public int y;

    public static Point operator +(Point x1, Point x2)
    {
        Point p = new Point();
        p.x = x1.x + x2.x;
        p.y = x1.y + x2.y;
        return p;
    }
    //支持函数重载
    public static Point operator +(Point x1, int x2)
    {
        Point p = new Point();
        p.x = x1.x + x2;
        p.y = x1.y + x2;
        return p;
    }
}

static void Main()
{
    Point p = new Point();
    Point p2 = new Point();
    p.x = 1;
    p.y = 1;
    p2.x = 2;
    p2.y = 2;
    Point p3 = p + p2;
    p3 = p + 3;
}

#endregion
#region 内部类 和 分布类

//class Person
//{
//   public class Body
//    {
//        class Arm//默认private
//        { }

//    }

//}

////分布类
////同一个类分开写
////partial
////把一个类分成几部分申明

////分部描述一个类
////增加程序拓展性

////分布类可以写在多个脚本文件中
////修饰符要一致
////分布类不能有重复的成员
////
//partial class Student
//{
//    public bool sex;
//}
//partial class Student
//{
//    public int age;
//}
//static void  Main()
//{
//    Person.Body body = new Person.Body();
//}

#endregion
#region 里氏替换原则 is as
//is 判断一个对象是否是指定类对象
//返回值：bool 是为真 不是为假

//as：将一个对象转换为指定类对象
//返回值是指定类对象

class GameObject
{
    public GameObject(int i)//父类的默认构造很重要
    {

    }
}
class Player : GameObject
{
    Player(int i) : base(i)//base指定调用
    {

    }

}

//GameObject player =new Player();

//if(player is Player)
//{
//    Player p = player as Player;
//}

#endregion
#region 万物之父 装箱拆箱
//object是所有类型的基类
//装箱：把值类型用引用类型存储
//拆箱：把引用类型存储的值类型取出来
//装箱：栈内存会迁移到内存中
//拆箱：堆内存会迁移到栈内存中
object o = new Player();
if (o is Player)
{
    Player player = o as Player;
}

object o2 = 1f; //装箱
float f1 = (float)o2;//拆箱

object o3 = "121212";
string s1 = (string)o3;
string s2 = o3.ToString();

object arr = new int[3];
int[] ar = arr as int[];
#endregion
#region 密封类 sealed
//密封关键字修饰的类
//让类无法在被继承

//sealed class Father//断子绝孙
//{

//}

//class Son:Father//报错
#endregion

//多态
#region 多态vob
//v:virtual;重写
//o:override;
//b: base;
#endregion

#region 抽象类 abstract override
//不能被实例化
//可以包含抽象方法
//继承抽象类必须重写其方法

//抽象方法必须写在抽象类

//用于整体框架的设计 让基类更安全
namespace chouxianglei
{

    abstract class Fruits
    {
        public string name;
        public abstract void Bad();//抽象方法不能有函数体 纯虚
        public virtual void Test()//在父类虚函数可以选择写逻辑 且 子类选性实现
        {

        }
    }
    class appel : Fruits
    {
        public override void Bad()
        {

        }
    }

    abstract class Thing
    {
        public string name;
    }

    class Water : Thing
    { }

    class Program
    {
        static void Main()
        {
            Thing thing = new Water();
        }
    }
}



#endregion

#region 接口 interface
//接口是行为的抽象规范
//他也是一种自定义类型

//不包含成员变量
//只包含方法，属性 索引器 实践
//成员不能被实现
//成员可以不用写访问修饰符，不能私有的
//接口不能继承类 但是可以继承另一个接口

//接口的使用规范
//类可以继承多个接口
//类继承接口后，必须实现接口中所有成员

//特点
//它和类的申明类似
//接口是用来继承的
//接口不能被实例化，但是可以作为容器存储对象

//接口是抽象行为的基类

//接口是用来继承的

//抽象类只能单一继承，接口可以被多继承
//抽象类中可以有成员变量，接口中不能
//抽象类中可以申明成员方法，虚方法，抽象方法，静态方法，接口中只能申明没有实现的抽象方法

//标识对象用抽象类  行为拓展用接口

public interface IFly
{
    public void Fly();//不需要函数体 不能私有   

    //string Name { get; set; }//属性

    //int this[int index]
    //{ get; set; }//索引器

    //event Action doSomthing;//事件

}
#region 模拟实验

//用接口模拟移动硬盘，u盘，MP3插到电脑上读取数据
//移动硬盘与u盘都属于存储设备
//MP3属于播放设备
//但他们都能插到电脑上传输数据。
//电脑提供一个接口，请实现电脑的传输数据功能
public interface IMove
{
    public void MOve();//不需要函数体 不能私有   
}
public interface IUSB//usb接口
{
    string DeviceName { get; }
    bool IsConnected { get; set; }
    void Connect();
    void Disconnect();
    void TransmitData(byte[] data);
}
// 2. 存储设备接口（继承自USB）
public interface IStorageDevice : IUSB
{
    long StorageCapacity { get; }
    long AvailableSpace { get; }
    void Format();
    void ReadData(string filePath);
    void WriteData(string filePath, byte[] data);
}

// 3. 媒体播放器接口
public interface IMediaPlayer : IUSB
{
    void Play();
    void Pause();
    void Stop();
    void Next();
    void Previous();
    List<string> GetPlaylist();
    void AddToPlaylist(string mediaPath);
}
// 4. 具体的设备类
public abstract class StorageDeviceBase : IStorageDevice
{
    public string DeviceName { get; protected set; }
    public bool IsConnected { get; set; }
    public long StorageCapacity { get; protected set; }
    public long AvailableSpace { get; protected set; }

    protected Dictionary<string, byte[]> files = new Dictionary<string, byte[]>();

    public StorageDeviceBase(string name, long capacity)
    {
        //。。。。。
    }

    public virtual void Connect()
    {
        IsConnected = true;
    }

    public virtual void Disconnect()
    {
        IsConnected = false;
    }

    public virtual void TransmitData(byte[] data)
    {
        if (!IsConnected)
        {
            return;
        }
        // 模拟数据传输耗时
    }

    public virtual void ReadData(string filePath)
    {
        if (files.ContainsKey(filePath))
        {
        }
        else
        {
        }
    }

    public virtual void WriteData(string filePath, byte[] data)
    {
        if (data.Length > AvailableSpace)
        {
            return;
        }

        files[filePath] = data;
        AvailableSpace -= data.Length;
    }

    public virtual void Format()
    {
        files.Clear();
        AvailableSpace = StorageCapacity;
    }
}

class YidongYingPan : IUSB
{
    int data;

    public string DeviceName => throw new NotImplementedException();

    public bool IsConnected { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

    public void Connect()
    {
        throw new NotImplementedException();
    }

    public void Disconnect()
    {
        throw new NotImplementedException();
    }

    public bool IsUsb()
    {
        return true;
    }

    public void Transmit()
    {
        //传输数据到data
    }

    public void TransmitData(byte[] data)
    {
        throw new NotImplementedException();
    }
}
// 5. 具体设备实现
public class MobileHardDisk : StorageDeviceBase
{
    public MobileHardDisk() : base("移动硬盘", 1024L * 1024 * 1024 * 2) // 2GB
    {
    }

    public override void TransmitData(byte[] data)
    {
        base.TransmitData(data);
    }
}

#endregion
class Animal
{ }
class Personal : Animal, IFly
{
    public void Fly()
    {

    }
    public string Name { get; set; }
    public int this[int index]
    {
        get
        {
            return 0;
        }
        set
        {
        }
    }
    public event Action doSomthing;
}
class Maque : Animal, IFly, IMove
{
    public void Fly()
    {
        throw new NotImplementedException();
    }

    public void MOve()
    {
        throw new NotImplementedException();
    }
}

#endregion
#region 密封函数 sealed
//
abstract class Animal
{
    public string name;
    public abstract void Eat();
    public virtual void Speak()
    {

    }
}

class Person : Animal
{
    public sealed override void Eat()//断子绝孙
    {
        throw new NotImplementedException();
    }

    public override void Speak()
    {
        base.Speak();
    }
}

class WhitePerson : Person
{
    //public override void Eat();//报错

    public override void Speak()
    {
        base.Speak();
    }
}


#endregion

#region object 的函数
namespace MyGame
{
    class Test
    {
        public int val = 10;

        public Test Clone()
        {
            return MemberwiseClone() as Test;
        }
    }
    class Program
    {
        static void Main()
        {
            //静态方法
            Console.WriteLine(Object.Equals(1, 1));

            Animal animal1 = new Animal();
            Animal animal2 = new Animal();

            Console.WriteLine(Object.Equals(animal1, animal2));//false
            Console.WriteLine(Object.ReferenceEquals(animal1, animal2));//不能用来比值 专门用来比引用的

            //GetType//反射相关
            //获取对象运行时的类型Type
            Type type = animal1.GetType();

            //MemberwiseClone
            //获取对象的浅拷贝对象，口语化的意思就是返回一个新的对象
            //新对象和老对象的引用变量一致

            //虚方法
            //Equals

            //GetHashCode
            //获取对象的哈希码（根据哈希算法算的）

            //ToString
            //返回当前值的字符串模式，也可以自己重写
        }
    }
}


#endregion

#region string

string std = "12345678";

int index =  std.IndexOf("67");//正向查找  未找到返回-1
int index1 =  std.LastIndexOf('8');//反向查找

string s = std.Remove(index);//移除index后的移除
string s = std.Remove(index ,index1);//移除之间（起始值 数量）
string s2 = std.Replace("5","0");//替换
string s3 = std.Substring(2);//截取 跟remove作用相反

//字符串切割!!!!!!!!!!!!!!
string str = "1,2,3,4,5";
string[] strs = str.Split(',');//按照，切割
foreach (var item in strs)
{
    Console.WriteLine(item);
}

#endregion
#region StringBuilder
//string是特殊的引用
//每次重新赋值或拼接都会重新开辟空间 浪费空间

//频繁的修改和字符串可以使用，可以提升性能
//需要命名空间
 StringBuilder str4 = new StringBuilder("123456789");//必须new
//是一个string版的vector
//会自动扩容 提前预备房间 

//增添删改
str4.Append("444");

str4.AppendFormat("{0}{1}", 100, 999);//拼接

str4.Insert(0, "XiaoHai");

str4.Remove(0,4);//删
str4.Clear();//清空

#endregion


