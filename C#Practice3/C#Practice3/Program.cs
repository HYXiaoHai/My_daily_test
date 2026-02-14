using C_Practice3;
using System.Net;
using System.Net.Http.Json;
using System.Net.Sockets;
using System.Numerics;
using System.Reflection.Emit;
using System.Text;
using System.Xml;
using System.Xml.Linq;
using Newtonsoft.Json;
namespace C学习
{
    //class Program3
    //{
    //    static void Main()
    //    {

    //    }
    //}

    #region 文件操作
    //class Program1
    //{
    //    static void Main()
    //    {
    //        #region File对“文件”的原子操作
    //        string path = @"C:\Game\save.dat";

    //        if (File.Exists(path)) ;//是否存在
    //        {
    //            // 读取所有文本（小文件）
    //            string content = File.ReadAllText(path);

    //            // 写入文本（覆盖）
    //            File.WriteAllText(path, "hahahahahah");

    //            // 追加文本
    //            File.AppendAllText(path, "more");

    //            // 删除
    //            File.Delete(path);
    //        }
    //        // 惰性读取大文件 —— 不会一次性加载到内存
    //        foreach (string line in File.ReadLines(@"C:\Logs\server.log"))
    //        {
    //            Console.WriteLine(line); // 逐行处理
    //        }
    //        #endregion

    //        #region Directory 对“目录”的原子操作
    //        string dir = @"C:\Game\Saves";

    //        // 创建目录（如果不存在会自动创建多级）
    //        Directory.CreateDirectory(dir);

    //        // 判断是否存在
    //        if (Directory.Exists(dir))
    //        {
    //            //遍历所有 .json 文件
    //            string[] files = Directory.GetFiles(dir, "*.json");

    //            //遍历所有子目录
    //            string[] subs = Directory.GetDirectories(dir);

    //            //删除目录（true = 递归删除子文件）
    //            Directory.Delete(dir, true);
    //        }

    //        #endregion

    //        #region Path路径字符串的“手术刀”
    //        string folder = @"C:\Game";
    //        string file = "player.json";

    //        // 永远用 Combine，别手写 "\\" 或 "/"
    //        //拼接
    //        string fullPath = Path.Combine(folder, file); // C:\Game\player.json 

    //        // 拆解路径
    //        string dirName = Path.GetDirectoryName(fullPath);   // C:\Game
    //        string fileName = Path.GetFileName(fullPath);       // player.json
    //        string nameWithoutExt = Path.GetFileNameWithoutExtension(fullPath); // player
    //        string ext = Path.GetExtension(fullPath);           // .json

    //        // 临时文件
    //        string temp = Path.GetTempFileName(); // 系统临时目录下创建0字节文件
    //        #endregion

    //        #region 实例双雄：FileInfo 和 DirectoryInfo
    //        //这两个类需要 new 实例，代表一个具体的文件 / 目录。
    //        //优势：多次操作同一文件 / 目录时，只做一次安全检查，性能更好，代码也更面向对象。

    //        //单次读/写/判断 → 静态类（代码简洁）
    //        //需要多次读取属性、或者要对同一个文件做多种操作 → 实例类（性能更优）

    //        // === FileInfo ===
    //        FileInfo fi = new FileInfo(@"C:\Game\player.json");

    //        if (fi.Exists)
    //        {
    //            Console.WriteLine($"大小: {fi.Length} 字节");
    //            Console.WriteLine($"创建时间: {fi.CreationTime}");
    //            Console.WriteLine($"是否只读: {fi.IsReadOnly}");

    //            // 复制、移动、删除
    //            fi.CopyTo(@"C:\Backup\player.json", overwrite: true);
    //            fi.MoveTo(@"C:\Game\player_old.json");
    //            fi.Delete();
    //        }
    //        else
    //        {
    //            // 创建文件并写入
    //            using (StreamWriter sw = fi.CreateText())
    //            {
    //                sw.Write("{\"name\":\"hero\"}");
    //            }
    //        }
    //        // === DirectoryInfo ===
    //        DirectoryInfo di = new DirectoryInfo(@"C:\Game\Saves");

    //        if (!di.Exists) di.Create();
    //        // 获取所有文件（支持通配符）
    //        FileInfo[] files = di.GetFiles("*.save");
    //        foreach (FileInfo f in files)
    //        {
    //            Console.WriteLine($"{f.Name} - {f.Length} bytes");
    //        }

    //        ///////////////////////////////////////////////////////////////
    //        FileInfo myfile = new FileInfo(@"目录地址");
    //        DirectoryInfo info = new DirectoryInfo(myfile.FullName);
    //        myfile.CopyTo(@"复制地址");
    //        //File.Copy();
    //        myfile.Create();//增加文件夹creat

    //        myfile.Delete();

    //        #region FileStream 与文本辅助类
    //        //FileStream 是字节级的原始流，适合读写二进制文件（图片、加密存档、自定义格式）。
    //        //配合 StreamReader/ StreamWriter 可轻松处理文本。

    //        //1 FileStream 直接操作字节
    //        string path1 = @"C:\Game\avatar.png";

    //        // 打开或创建，读写权限：共享模式
    //        using (FileStream fs = new FileStream(path, FileMode.OpenOrCreate, FileAccess.ReadWrite))
    //        {
    //            // 读取第一个字节
    //            int b = fs.ReadByte();

    //            // 写入字节数组
    //            byte[] data = new byte[1024];
    //            fs.Write(data, 0, data.Length);

    //            // 设置位置
    //            fs.Seek(0, SeekOrigin.Begin);
    //        } // using 自动释放资源

    //        //2 搭配 StreamReader/ Writer —— 文本专用
    //        // 写入文本
    //        using (FileStream fs = new FileStream("log.txt", FileMode.Create))
    //        using (StreamWriter sw = new StreamWriter(fs, Encoding.UTF8))
    //        {
    //            sw.WriteLine("游戏启动");
    //            sw.WriteLine($"帧率: {60}");
    //        }

    //        // 读取文本
    //        //StreamReader reader = new StreamReader(@"路径");
    //        using (FileStream fs = new FileStream("log.txt", FileMode.Open))
    //        using (StreamReader sr = new StreamReader(fs, Encoding.UTF8))//
    //        {
    //            string line;
    //            while ((line = sr.ReadLine()) != null)
    //            {
    //                Console.WriteLine(line);
    //            }
    //        }
    //        //////////////////////////////////////////////////////////////////////////////////
    //        //流
    //        FileStream read = new FileStream(@"路径", FileMode.Open, FileAccess.Read);//路径 方式 权限
    //        //read.ReadByte();//读取一个字节

    //        FileStream write = new FileStream("", FileMode.Create, FileAccess.Write);
    //        //write.WriteByte();

    //        //复制 
    //        int nextByte = -1;
    //        while ((nextByte = read.ReadByte()) != -1)
    //        {
    //            write.WriteByte((byte)nextByte);
    //        }

    //        //复制优化
    //        byte[] buffer = new byte[1024];
    //        int count = 0;
    //        while ((count = read.Read(buffer, 0, 1024)) != 0)
    //        {
    //            write.Write(buffer, 0, count);//把这个流的数据写入。
    //        }
    //        write.Close();
    //        read.Close();

    //        #endregion

    //        #endregion

    //    }
    //}
    #endregion

    #region Tcp服务端
    //更可靠
    //先确定对方存在
    class Program
    {
        static void Main()
        {
            Socket tcpServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);//创建插口 ip4 流形式 Tcp协议

            IPAddress iPAddress = new IPAddress(new byte[] { 192, 168, 0, 8 });
            //Ip+Port
            IPEndPoint iPEndPoint = new IPEndPoint(iPAddress, 8080);//创建

            tcpServer.Bind(iPEndPoint);//绑定

            tcpServer.Listen(100);//最多100个人链接
            Console.WriteLine("开始接客了。。");

            Socket clinet = tcpServer.Accept(); //开始监听其他人是否链接 返回客户端socket
            Console.WriteLine("一个客户端链接过来了");

            byte[] data = new byte[1024];
            int length = clinet.Receive(data);
            string message = Encoding.UTF8.GetString(data, 0, length);//二进制 更改成 字符
            Console.WriteLine("接收到了客户的消息：" + message);

            clinet.Close();

            tcpServer.Close();
        }
    }
    //特性          TCP	                                UDP
    //连接	        面向连接（三次握手）	            无连接
    //可靠性	    可靠：保证数据到达、顺序、无重复	不可靠：可能丢包、乱序、重复
    //流量控制	    有（滑动窗口）	                    无
    //拥塞控制	    有	                                无
    //首部开销	    20字节	                            8字节
    //传输速度	    较慢（确认重传、拥塞控制）	        较快
    //数据边界	    流式（无消息边界，需处理粘包）	    保留消息边界（每个包独立）

    //游戏场景选择
    //场景                          选择	                                    原因
    //下载                          TCP                             需要可靠
    //登录认证、商城购买、聊天室	TCP	                            必须可靠、有序，丢包会出大问题
    //MMO角色移动、状态同步	        TCP 或 UDP+可靠层	            传统MMO多用TCP简化开发，但对延迟敏感时需UDP
    //FPS/格斗/赛车（帧同步）	    UDP	                            实时性要求极高，可容忍少量丢包
    //位置/状态广播	                UDP	                            即使丢一帧，下一帧覆盖即可
    //语音/视频流	                UDP	                            实时性优先，少量丢包不影响理解

    //总结：关键业务用TCP（可靠但慢），实时高频用UDP（快但不可靠，可在上层实现可靠逻辑）。
#endregion

    #region UDP服务端
    class Program2
    {
        static void Main()
        {
            Socket udpServer = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            IPAddress iPAddress = new IPAddress(new byte[] { 192, 168, 0, 8 });
            //Ip+Port
            IPEndPoint iPEndPoint = new IPEndPoint(iPAddress, 8080);//创建

            udpServer.Bind(iPEndPoint);
            udpServer.Listen(100);

            IPEndPoint iPEndPoint1 = new IPEndPoint(IPAddress.Any, 0);

            byte[] data = new byte[1024];
            EndPoint ep = (EndPoint)iPEndPoint1;
            int length = udpServer.ReceiveFrom(data, ref ep);

            Console.WriteLine("收到数据" + Encoding.UTF8.GetString(data, 0, length));
        }
    }
    #endregion

    #region XML
    //用来保存数据的 类似json
    //excel 数据直观，但是文件较大，文件读取慢
    
    //XML格式和Json格式的文本
    //数据方便管理
    //程序读取快

    //XML示例
//<? xml version="1.0" encoding="UTF-8"?>
//<player id = "1001" >
//    < name > 勇士 </ name >
//    < level > 10 </ level >
//    < skills >
//        < skill > 旋风斩 </ skill >
//        < skill > 冲锋 </ skill >
//    </ skills >
//</ player >

    class Program3
    {
        static void Main()
        {
            List<Skill>listSkill = new List<Skill>();
            XmlDocument xmlDocument = new XmlDocument();
            xmlDocument.Load("Skills.xml");//加载
            xmlDocument.LoadXml(File.ReadAllText("Skills.xml"));//传递字符串

            XmlNode root = xmlDocument.FirstChild;
            XmlNodeList skillList = root.ChildNodes;
            foreach (XmlNode skill in skillList)
            {
                Skill skillObj = new Skill();
                foreach (XmlNode node in skill.ChildNodes)
                {
                    if(node.Name == "id")
                    {
                        skillObj.Id = Int32.Parse(node.InnerText);
                    }
                    else if(node.Name == "name")
                    {
                        skillObj.Name = node.InnerText;
                        skillObj.Lang = node.Attributes[0].Value;
                    }
                    else
                    {
                        skillObj.Damage = Int32.Parse(node.InnerText); 
                    }
                }

                XmlElement idEle = skill["id"];
                skillObj.Id = Int32.Parse(idEle.InnerText);

                XmlElement nameEle = skill["name"];
                skillObj.Name =nameEle.InnerText;

                XmlAttributeCollection attriCol = nameEle.Attributes;
                XmlAttribute attrru =  attriCol["lang"];
                skillObj.Lang = attrru.Value;

                XmlElement damageEle = skill["damage"];
                skillObj.Damage = Int32.Parse(damageEle.InnerText);


                listSkill.Add(skillObj);
            }
            foreach (Skill item in listSkill)
            {
                Console.WriteLine(item.Id+item.Name+item.Damage);
            }
        }
    }
    #endregion

    #region Json
    class Program4
    {
        static void Main()
        {

            //Serialize 序列化
            string[] names = { "Micheal", "张三", "李四" };
            string str = JsonConvert.SerializeObject(names);

            //DeserializeObject 反序列化
            Skill[] skillArray = JsonConvert.DeserializeObject<Skill[]>(File.ReadAllText("Skills.txt"));
            foreach (Skill item in skillArray)
            {
                Console.WriteLine(item.Id);
            }
        }
    }

    #endregion

}
