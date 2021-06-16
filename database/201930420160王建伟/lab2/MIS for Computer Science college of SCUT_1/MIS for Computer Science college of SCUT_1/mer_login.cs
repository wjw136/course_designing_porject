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
    public partial class mer_login : Form
    {
        public mer_login()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void mer_login_Load(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }
        /*
         * 退出
         */
        private void button9_Click(object sender, EventArgs e)
        {
            this.Close();
            MyDatabase.f1.Show();
        }
        /*
         * 查询学生信息
         */
        private void button1_Click(object sender, EventArgs e)
        {
            string name = this.textBox2.Text;
            string ID = this.textBox3.Text;
            string com_que = "select * from student where sid= " + ID + " and Sname='" + name + "'";
            Console.WriteLine(com_que);
            MySqlDataAdapter sda = new MySqlDataAdapter(com_que, MyDatabase.giricon);
            DataSet ds = new DataSet();
            sda.Fill(ds, "student");
            this.dataGridView1.DataSource = ds.Tables["student"];

        }

        private void button2_Click(object sender, EventArgs e)
        {
            string name = this.textBox2.Text;
            string ID = this.textBox3.Text;
            string com_que = "select * from teacher where tid= " + ID + " and tname= '" + name + "'";
            MySqlDataAdapter sda = new MySqlDataAdapter(com_que, MyDatabase.giricon);
            DataSet ds = new DataSet();
            sda.Fill(ds, "teacher");
            this.dataGridView1.DataSource = ds.Tables["teacher"];
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string name = this.textBox2.Text;
            string ID = this.textBox3.Text;
            string com_que = "select * from course where cid= " + ID + " and cname= '" + name + "'";
            MySqlDataAdapter sda = new MySqlDataAdapter(com_que, MyDatabase.giricon);
            DataSet ds = new DataSet();
            sda.Fill(ds, "course");
            this.dataGridView1.DataSource = ds.Tables["course"];
        }

        private void button8_Click(object sender, EventArgs e)
        {
            mode md = new mode();
            md.ShowDialog();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            modify mf = new modify();
            mf.ShowDialog();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            delete de = new delete();
            de.ShowDialog();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            query_mer qm = new query_mer();
            this.Hide();
            qm.ShowDialog();
            this.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            avgdata_mer av = new avgdata_mer();
            this.Hide();
            av.ShowDialog();
            this.Show();
        }
    }
}
