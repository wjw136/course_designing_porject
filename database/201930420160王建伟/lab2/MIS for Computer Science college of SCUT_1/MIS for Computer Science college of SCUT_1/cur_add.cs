using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class cur_add : Form
    {
        public cur_add()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void cur_add_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string CID = this.textBox1.Text;
            string name = this.textBox3.Text;
            string TID = this.textBox5.Text;
            string credit = this.textBox2.Text;
            string grade = this.textBox4.Text;
            string time = this.textBox6.Text;
            string com = "INSERT into course VALUES(" + CID + ",'" + name + "'," + TID + "," + credit + "," + grade + "," + time + ")";
            if (MyDatabase.sqlNoQuery(com) > 0)
            {
                MessageBox.Show("插入成功!");
            }
            this.Close();
        }
    }
}
