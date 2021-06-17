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

//客户端
namespace socket
{
    public partial class Form2 : Form
    {
        Socket socketsend;
        public Form2()
        {
            InitializeComponent();
        }
        /// <summary>
        /// 连接
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                //创建用于通讯的socket
                socketsend = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ip = IPAddress.Parse(textBox1.Text);
                IPEndPoint port = new IPEndPoint(ip, Convert.ToInt32(textBox2.Text));

                //连接对应的端口
                socketsend.Connect(port);
                ShowMsg(socketsend.RemoteEndPoint + ": 连接成功!");

                //开辟线程接收信息
                Thread td = new Thread(Receive);
                td.IsBackground = true;
                td.Start();
            }
            catch { }
        }
        /// <summary>
        /// 接收信息
        /// </summary>
        private void Receive()
        {
            while (true)
            {
                try
                {
                    byte[] buffer = new byte[1024 * 1024 * 2];
                    int i = socketsend.Receive(buffer);

                    if (i == 0)
                    {
                        break;
                    }

                    string str = Encoding.UTF8.GetString(buffer, 0, i);
                    ShowMsg(socketsend.RemoteEndPoint + ": " + str);

                }
                catch { }
            }
        }


        public void ShowMsg(string str)
        {
            textBox3.AppendText(str + "\r\n");
        }
        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click_1(object sender, EventArgs e)
        {
            string str = textBox4.Text;
            Byte[] buffer = System.Text.Encoding.UTF8.GetBytes(str);
            //默认阻塞,直到能成功发送返回(内存足够大等等) drawback:不能及时得知错误.
            socketsend.Send(buffer);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
