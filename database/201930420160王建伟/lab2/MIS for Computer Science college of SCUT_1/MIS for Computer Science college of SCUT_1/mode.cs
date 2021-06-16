using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MIS_for_Computer_Science_college_of_SCUT_1
{
    public partial class mode : Form
    {
        public mode()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (this.radioButton2.Checked == true)
            {
                stu_add sad = new stu_add();
                sad.ShowDialog();
                

            }else if(this.radioButton3.Checked == true)
            {
                tch_add tad = new tch_add();
                tad.ShowDialog();

            }
            else if(this.radioButton4.Checked == true)
            {
                cur_add cad = new cur_add();
                cad.ShowDialog();
            }
            else
            {
                cho_add cad2 = new cho_add();
                cad2.ShowDialog();
            }
            this.Close();
        }
    }
}
