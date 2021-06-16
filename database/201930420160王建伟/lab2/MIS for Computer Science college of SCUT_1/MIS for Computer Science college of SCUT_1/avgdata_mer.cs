using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class avgdata_mer : Form
    {
        string name;
        string ID;
        public avgdata_mer()
        {
            InitializeComponent();
        }

        private void uiButton5_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void avgdata_mer_Load(object sender, EventArgs e)
        {

        }

        private void uiButton1_Click(object sender, EventArgs e)
        {   
            //this在c#中不是指针,是引用
            name = this.uiTextBox1.Text;
            ID = this.uiTextBox2.Text;
            string com1 = "select cid,Cname,Credit,Grade,CancelYear,Score from student NATURAL JOIN course  NATURAL join choose where sid=" + ID +
                "  and Sname='" + name+"'";
            DataSet ds=MyDatabase.sqlQuery(com1);
            this.dataGridView1.DataSource = ds.Tables[0];
            MessageBox.Show("查询成功!");
        }

        private void uiButton2_Click(object sender, EventArgs e)
        {
            name = this.uiTextBox1.Text;
            ID = this.uiTextBox2.Text;
            string com1 = "select SID,Sname,AVG(Score) from student NATURAL JOIN course  NATURAL join choose where sid=" + ID +
                "  and Sname='" + name + "'";
            DataSet ds = MyDatabase.sqlQuery(com1);
            this.dataGridView1.DataSource = ds.Tables[0];
            MessageBox.Show("查询成功!");
        }

        private void uiButton3_Click(object sender, EventArgs e)
        {
            name = this.uiTextBox1.Text;
            ID = this.uiTextBox2.Text;
            string com1 = "sELECT Class,CID,Cname,AVG(Score)  from student natural join choose NATURAL join course where Class=(select Class from student where sid=" +
                ID + "  and Sname= '" + name + "') GROUP BY CID";
            DataSet ds = MyDatabase.sqlQuery(com1);
            this.dataGridView1.DataSource = ds.Tables[0];
            MessageBox.Show("查询成功!");
        }

        private void uiButton4_Click(object sender, EventArgs e)
        {
            name = this.uiTextBox1.Text;
            ID = this.uiTextBox2.Text;
            string com1 = "SELECT CID,Cname,AVG(Score)  from student natural join choose NATURAL join course where CID IN (select CID from student where sid=" +
                ID + "  and Sname= '" + name + "') GROUP BY CID";
            DataSet ds = MyDatabase.sqlQuery(com1);
            this.dataGridView1.DataSource = ds.Tables[0];
            MessageBox.Show("查询成功!");
        }
    }
}
