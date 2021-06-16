using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Sunny.UI;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class modify : Form
    {
        private string table;
        public modify()
        {
            InitializeComponent();
        }

        private void uiButton2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void uiButton1_Click(object sender, EventArgs e)
        {
            string column = this.uiTextBox1.Text;
            string ID = this.uiTextBox2.Text;
            string ud = this.uiTextBox3.Text;


            string com = "UPDATE " + table + " SET " + column + "=" + ud + " WHERE " + table[0] + "ID=" + ID;
            int res = MyDatabase.sqlNoQuery(com);
            if (res > 0)
            {
                MessageBox.Show("成功修改!");
            }
            this.Close();


        }
        //vc回调函数配合radiobutton
        private void uiRadioButton3_ValueChanged(object sender, bool value)
        {

            UIRadioButton sender_1 = (UIRadioButton)sender;
            if (sender_1.Checked == true)
            {
                Console.WriteLine(sender_1.Text);
                table = sender_1.Text;
            }
        }

        private void uiLabel3_Click(object sender, EventArgs e)
        {

        }
    }
}
