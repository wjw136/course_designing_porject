using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class cho_add : Form
    {
        public cho_add()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void cho_add_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string CID = this.textBox1.Text;
            string SID = this.textBox2.Text;
            string TID = this.textBox3.Text;
            string grade = this.textBox4.Text;
            string year = DateTime.Now.Year.ToString();
            if (grade == "") grade = "null";
            string com = "insert into choose values(" + SID + "," + CID + "," + TID + "," + grade + "," + year + ")";
            int res=MyDatabase.sqlNoQuery(com);
            if (res > 0)
                MessageBox.Show("成功插入!");
            else
            {

            }
            this.Close();
        }
    }
}
