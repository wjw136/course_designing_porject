using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using MySqlConnector;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class stu_login : Form
    {
        public stu_login()
        {
            InitializeComponent();
        }
        /*
         * 选课
         */
        private void button1_Click(object sender, EventArgs e)
        {
            course_choose c_h = new course_choose();
            //this.Enabled = false;
            c_h.ShowDialog();
        }
        /**
         * 退出
         */
        private void button5_Click(object sender, EventArgs e)
        {
            MyDatabase.stu1.Close();
            MyDatabase.f1.Show();
            MyDatabase.f1.reload();
        }
        /*
         * 查询个人信息
         */
        private void button2_Click(object sender, EventArgs e)
        {
            string command = "select * from student where SID=" + MyDatabase.SID;//自定义sql查询语言 
            Console.WriteLine(command);
            MySqlCommand mySqlCommand = new MySqlCommand(command, MyDatabase.giricon);
            MySqlDataAdapter sda = new MySqlDataAdapter(command, MyDatabase.giricon);
            DataSet ds = new DataSet();
            sda.Fill(ds);
            this.dataGridView1.DataSource = ds.Tables[0];
            //dataGridView1.ReadOnly = true;
        }
        /*
         * 查询选课信息
         */
        private void button3_Click(object sender, EventArgs e)
        {
            string command = "select CID,Cname,CancelYear, Credit, (case when (ChooseYear is null) then NULL else ChooseYear end) as ChooseYear from choose NATURAL JOIN course where SID=" + MyDatabase.SID;//自定义sql查询语言 
            Console.WriteLine(command);
            MySqlCommand mySqlCommand = new MySqlCommand(command, MyDatabase.giricon);
            MySqlDataAdapter sda = new MySqlDataAdapter(command, MyDatabase.giricon);
            DataSet ds = new DataSet();
            sda.Fill(ds);
            this.dataGridView1.DataSource = ds.Tables[0];
        }
        /*
         * 查询成绩
         */
        private void button4_Click(object sender, EventArgs e)
        {
            string command = "select CID,Cname,Credit,Score from choose NATURAL JOIN course where score is not NULL and SID=" + MyDatabase.SID;//自定义sql查询语言 
            Console.WriteLine(command);
            MySqlCommand mySqlCommand = new MySqlCommand(command, MyDatabase.giricon);
            MySqlDataAdapter sda = new MySqlDataAdapter(command, MyDatabase.giricon);
            DataSet ds = new DataSet();
            sda.Fill(ds);
            this.dataGridView1.DataSource = ds.Tables[0];
        }
    }
}
