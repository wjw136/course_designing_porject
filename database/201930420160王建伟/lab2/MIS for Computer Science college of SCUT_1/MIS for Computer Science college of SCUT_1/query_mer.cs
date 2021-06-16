using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class query_mer : Form
    {
        int flag = -1;
        
        public query_mer()
        {
            InitializeComponent();
        }

        private void uiButton2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void uiRadioButtonGroup1_ValueChanged(object sender, int index, string text)
        {

        }

        private void uiButton1_Click(object sender, EventArgs e)
        {
            string name = this.uiTextBox2.Text;
            string ID = this.uiTextBox1.Text;
            //string必须赋值(对象 初始化,即分配!内存!,后面才能重新赋值and so on)
            //基本类型 自动分配内存(自动赋值),可以不初始化(xxxx)
            //int 也要 c#
            string com1="";
            int a;
            switch (flag)
            {
                case 1:
                    com1 = "select SID,Sname,CID,Cname from student NATURAL JOIN course  NATURAL join choose where sid=" + ID + "  and Sname='" + name + "'";
                    break;
                case 2:
                    com1 = "select SID,Sname,CID,Cname from student NATURAL JOIN course  NATURAL join choose NATURAL join teacher where tid=" + ID + " and tname='" + name + "'";
                    break;
                case 3:
                    com1 = "select SID,Sname,class from student NATURAL JOIN course  NATURAL join choose where cid=" + ID + "  and cname='" + name + "'";
                    break;
                case 4:
                    com1 = "select Cname,score from student NATURAL JOIN course  NATURAL join choose where sid=" + ID + "  and sname='" + name + "'";
                    break;
            }
            //Console.WriteLine(a);
            DataSet ds = MyDatabase.sqlQuery(com1);
            this.uiDataGridView1.DataSource = ds.Tables[0];
            MessageBox.Show("成功查询!");
        }

        private void uiRadioButton1_ValueChanged(object sender, bool value)
        {
            if (this.uiRadioButton1.Enabled = true)
            {
                flag = 1;
            }
        }

        private void uiRadioButton2_ValueChanged(object sender, bool value)
        {
            if (this.uiRadioButton2.Enabled = true)
            {
                flag = 2;
            }
        }

        private void uiRadioButton3_ValueChanged(object sender, bool value)
        {
            if (this.uiRadioButton3.Enabled = true)
            {
                flag = 3;
            }
        }

        private void uiRadioButton4_ValueChanged(object sender, bool value)
        {
            if (this.uiRadioButton4.Enabled = true)
            {
                flag = 4;
            }
        }
    }
}
