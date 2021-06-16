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
    public partial class tch_login : Form
    {
        public string Tname;
        public string course;
        public tch_login()
        {
            InitializeComponent();
            string command1 = "SELECT course,Tname from teacher WHERE tid=" + MyDatabase.TID;
            MySqlDataAdapter data1 = new MySqlDataAdapter(command1, MyDatabase.giricon);
            DataSet ds = new DataSet()
; data1.Fill(ds, "teacher");
            DataTable dt = ds.Tables["teacher"];
            DataRowCollection drc = dt.Rows;
            DataRow dr = drc[0];
            this.Tname = (string)dr[1]; this.course = (string)dr[0];
        }
        /*
         * 退出
         */
        private void button5_Click(object sender, EventArgs e)
        {
            this.Close();
            MyDatabase.f1.Show();
        }
        /*
         * 查询个人信息
         */
        private void button1_Click(object sender, EventArgs e)
        {
            string command = "select * from teacher where TID=" + MyDatabase.TID;//自定义sql查询语言 
            Console.WriteLine(command);
            MySqlCommand mySqlCommand = new MySqlCommand(command, MyDatabase.giricon);
            MySqlDataAdapter sda = new MySqlDataAdapter(command, MyDatabase.giricon);
            DataSet ds = new DataSet();
            sda.Fill(ds);
            this.dataGridView1.DataSource = ds.Tables[0];
        }
        /*
         * 查询课程平均成绩
         */
        private void button3_Click(object sender, EventArgs e)
        {
            string command1 = "SELECT cid,cname,tname,avg(score)from choose NATURAL join course NATURAL join teacher WHERE tid=" + MyDatabase.TID;
            MySqlDataAdapter mda = new MySqlDataAdapter(command1, MyDatabase.giricon);
            DataSet ds = new DataSet();
            mda.Fill(ds, "result");
            this.dataGridView1.DataSource = ds.Tables["result"];
        }
        /*
         * 查询学生信息
         */
        private void button2_Click(object sender, EventArgs e)
        {
            string command2 = "SELECT Sname,sid, class,SchoolAge,SchoolYear,Cname,cid,score from teacher NATURAL join choose NATURAL join student NATURAL join course WHERE tid=" + MyDatabase.TID;
            Console.WriteLine(command2);
            MySqlDataAdapter mda = new MySqlDataAdapter(command2, MyDatabase.giricon);
            DataSet ds = new DataSet();
            mda.Fill(ds, "result2");
            this.dataGridView1.DataSource = ds.Tables["result2"];
        }

        private void button4_Click(object sender, EventArgs e)
        {
            modify_grade mg = new modify_grade();
            //this.Enabled = false;
            mg.ShowDialog();

        }

        private void tch_login_FormClosed(object sender, FormClosedEventArgs e)
        {

        }
    }
}
