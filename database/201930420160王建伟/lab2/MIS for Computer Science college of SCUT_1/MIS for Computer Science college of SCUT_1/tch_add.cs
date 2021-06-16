using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class tch_add : Form
    {
        public tch_add()
        {
            InitializeComponent();
        }

        private void add_info1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string ID = this.textBox1.Text;
            string name = this.textBox2.Text;
            string course = this.textBox3.Text;
            string com = "INSERT into teacher VALUES(" + ID + "," + name + "," + course + ")";
            int res=MyDatabase.sqlNoQuery(com);
            if (res > 0)
            {
                MessageBox.Show("成功插入!");
            }
            this.Close();
        }
    }
}
