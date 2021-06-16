using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySqlConnector;//调用MySQL动态库
using System.Windows.Forms;
using MySqlConnector;//调用MySQL动态库

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class main_menu : Form
    {
        MySqlConnection giricon = MyDatabase.giricon;
        public main_menu()
        {
            InitializeComponent();
        }
        public void reload()
        {
            this.textBox1.Text = "";
            this.textBox2.Text = "";
            this.radioButton1.Checked = false;
            this.radioButton2.Checked = false;
            this.radioButton3.Checked = false;
        }
        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        //登录
        private void button1_Click(object sender, EventArgs e)
        {
            if (radioButton1.Checked == true)
            {
                string strtxt1 = this.textBox1.Text;
                string command = "select SID from permission1 where SID=" + strtxt1;//自定义sql查询语言 
                MySqlCommand mySqlCommand = new MySqlCommand(command, giricon);
                int i = Convert.ToInt32(mySqlCommand.ExecuteScalar());//把查询结果转换成数字，如果没有查询到相应MID的账号，查询结果为0  
                if (i == 0) MessageBox.Show("用户不存在");
                else
                {
                    string strtxt2 = this.textBox2.Text;
                    command = "select SID from permission1 where SID=" + strtxt1 + " and SPW=" + strtxt2;
                    MySqlCommand sql = new MySqlCommand(command, giricon);//sqlcommand执行sql命令，注意函参  
                    int j = Convert.ToInt32(sql.ExecuteScalar());
                    if (j != 0)
                    {
                        MessageBox.Show("成功");//弹出提示框，显示成功  
                        MyDatabase.SID = strtxt1;
                        stu_login f4 = new stu_login();//跳转到第另一个写好的界面  
                        MyDatabase.stu1 = f4;
                        this.Hide();//关闭登录界面  
                        f4.ShowDialog();
                    }
                    else
                        MessageBox.Show("密码错误");
                }
            }
            else if (radioButton2.Checked == true)
            {
                string strtxt1 = this.textBox1.Text;
                string command = "select TID from permission2 where TID=" + strtxt1;//自定义sql查询语言  
                MySqlCommand mySqlCommand = new MySqlCommand(command, giricon);
                int i = Convert.ToInt32(mySqlCommand.ExecuteScalar());//把查询结果转换成数字，如果没有查询到相应MID的账号，查询结果为0  
                if (i == 0) MessageBox.Show("用户不存在");
                else
                {
                    string strtxt2 = this.textBox2.Text;
                    command = "select TID from permission2 where TID=" + strtxt1 + " and TPW=" + strtxt2;
                    MySqlCommand sql = new MySqlCommand(command, giricon);//sqlcommand执行sql命令，注意函参  
                    int j = Convert.ToInt32(sql.ExecuteScalar());
                    if (j != 0)
                    {
                        MessageBox.Show("成功");//弹出提示框，显示成功  
                        MyDatabase.TID = strtxt1;
                        tch_login f4 = new tch_login();//跳转到第另一个写好的界面  
                        MyDatabase.tch1 = f4;
                        this.Hide();//关闭登录界面  
                        f4.ShowDialog();
                    }
                    else
                        MessageBox.Show("密码错误");
                }
            }
            else if (radioButton3.Checked == true)
            {
                string strtxt1 = this.textBox1.Text;
                string command = "select MID from permission3 where MID=" + strtxt1;//自定义sql查询语言  
                MySqlCommand mySqlCommand = new MySqlCommand(command, giricon);
                int i = Convert.ToInt32(mySqlCommand.ExecuteScalar());//把查询结果转换成数字，如果没有查询到相应MID的账号，查询结果为0  
                if (i == 0) MessageBox.Show("用户不存在");
                else
                {
                    string strtxt2 = this.textBox2.Text;
                    command = "select MID from permission3 where MID=" + strtxt1 + " and MPW=" + strtxt2;
                    MySqlCommand sql = new MySqlCommand(command, giricon);//sqlcommand执行sql命令，注意函参  
                    int j = Convert.ToInt32(sql.ExecuteScalar());
                    if (j != 0)
                    {
                        MessageBox.Show("成功");//弹出提示框，显示成功  
                        MyDatabase.MID = strtxt1;
                        mer_login f4 = new mer_login();//跳转到第另一个写好的界面  
                        MyDatabase.mer1 = f4;
                        /*
                         * 主页面的切换(要把之前的主页面hide,并保存)
                         * 保存的页面放在公共类中,便于后续再次调用
                         */
                        MyDatabase.f1.Hide();//关闭登录界面  
                        f4.ShowDialog();
                    }
                    else
                        MessageBox.Show("密码错误");
                }
            }
            
        }
        //退出
        private void button2_Click(object sender, EventArgs e)
            {
                //this.Close();
                Application.Exit();
            }
        
    } 
}
