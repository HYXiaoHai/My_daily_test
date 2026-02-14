
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Tcp客户端
{
    class Program
    {
        static void Main(string[] args)
        {
            Socket tcpClirnt = new Socket(AddressFamily.InterNetwork,SocketType.Stream, ProtocolType.Tcp);

            IPAddress iPAddress = new IPAddress(new byte[] { 192, 168, 0, 8 });
            //Ip+Port
            IPEndPoint iPEndPoint = new IPEndPoint(iPAddress, 8080);//创建

            tcpClirnt.Connect(iPEndPoint);//链接
            Console.WriteLine("连接上了服务器");

            string message = "我上线了";
            tcpClirnt.Send(Encoding.UTF8.GetBytes(message));//编码格式

            tcpClirnt.Close();

        }
    }
}