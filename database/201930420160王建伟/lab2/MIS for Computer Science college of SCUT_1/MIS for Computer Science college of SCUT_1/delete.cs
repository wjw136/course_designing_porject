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

    public partial class delete : Form
    {
        string table;
        public delete()
        {
            InitializeComponent();
        }

        private void uiRadioButton1_ValueChanged(object sender, bool value)
        {
            UIRadioButton sender_1 = (UIRadioButton)sender;
            if (sender_1.Checked == true)
            {
                Console.WriteLine(sender_1.Text);
                table = sender_1.Text;
            }
        }

        private void uiButton1_Click(object sender, EventArgs e)
        {
            string ID = this.uiTextBox1.Text;
            string com = "DELETE from " + table + " where " + table[0] + "ID= " + ID;
            int res = MyDatabase.sqlNoQuery(com);
            if (res > 0)
            {
                MessageBox.Show("成功删除!");
            }
            this.Close();
        }
    }
}
