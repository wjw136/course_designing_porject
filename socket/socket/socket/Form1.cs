using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;
using System.Threading;

//服务端
namespace socket
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //连接
        private void button1_Click(object sender, EventArgs e)
        {
            Socket socketwatch = new Socket(SocketType.Stream, ProtocolType.Tcp);
            //服务器上的所有ip
            IPAddress ip = IPAddress.Any;
            IPEndPoint point = new IPEndPoint(ip, Convert.ToInt32(textBox1.Text));

            //监听
            socketwatch.Bind(point);
            //等待连接的最大队列长度
            socketwatch.Listen(10);
            showmsg("监听成功!");


            //开辟新线程进行监听
            Thread th = new Thread(Listen);
            th.IsBackground = true;
            th.Start(socketwatch);

        }
        /// <summary>
        /// 开辟新线程监听客户端的连接
        /// </summary>
        /// <param name="o"></param>
        Socket socketsend;
        void Listen(object o)
        {
            Socket socketwatch = o as Socket;
            while (true)
            {
                //等待客户端的连接
                //每次将当前连接返回(pass by value), 并且接收下一个连接队列中的连接
                socketsend = socketwatch.Accept();
                showmsg(socketsend.RemoteEndPoint.ToString() + ": 连接成功");

                //开辟后台线程接收消息
                //线程==函数(伪main主函数)
                Thread th = new Thread(Recieve);
                th.IsBackground = true;
                //开启线程是传递的参数
                th.Start(socketsend);
            }
        }

        //存储ip以及对应的通讯socket
        Dictionary<string, Socket> dicSocket = new Dictionary<string, Socket>();
        /// <summary>
        /// 接收客户端的消息
        /// </summary>
        /// <param name="o"></param>
        void Recieve(object o)//线程中传递变量必须是object类型
        {
            Socket socketsend = o as Socket;

            //储存ip与连接
            dicSocket.Add(socketsend.RemoteEndPoint.ToString(), socketsend);
            //同步到combox
            comboBox1.Items.Add(socketsend.RemoteEndPoint.ToString());

            while (true)
            {
                try
                {
                    byte[] buffer = new byte[1024 * 1024 * 2];
                    //block类型
                    //会刷新buffer 再重新加入新的信息
                    int i = socketsend.Receive(buffer);

                    //断开连接时数据长度为0, 跳出循环
                    //0字节的数据, recieve不响应 or 客户端检查不发送
                    if (i == 0)
                    {
                        comboBox1.Items.Remove(socketsend.RemoteEndPoint.ToString());
                        break;
                    }
                    string str = Encoding.UTF8.GetString(buffer, 0, i);
                    showmsg(socketsend.RemoteEndPoint + ":" + str);
                }
                catch { }
            }
        }
        /// <summary>
        /// 显示提示信息
        /// </summary>
        /// <param name="s"></param>
        void showmsg(string s)
        {
            textBox3.AppendText(s + "\r\n");
        }
        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            string str = textBox4.Text;
            byte[] buffer = Encoding.UTF8.GetBytes(str);
            dicSocket[comboBox1.SelectedItem.ToString()].Send(buffer);

        }
    }
}
