using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class stu_add : Form
    {
        public stu_add()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string id = this.textBox1.Text;
            string name = this.textBox2.Text;
            string sex = this.textBox3.Text;
            string time = this.textBox4.Text;
            string age = this.textBox5.Text;
            string class1 = this.textBox6.Text;
            string com = "insert into Student values('" + id + "','" + name + "','" + sex + "','" + time + "','" + age + "','" + class1+"')";
            int a=MyDatabase.sqlNoQuery(com);
            if (a > 0) MessageBox.Show("成功插入!");
            this.Close();

        }


    }
}
