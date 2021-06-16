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
    public partial class modify_grade : Form
    {
        public modify_grade()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string SID = this.textBox1.Text;
            string CID = this.textBox2.Text;
            string grade = this.textBox3.Text;
            string com1 = "SELECT Tid from choose where sid= " + SID + " and CID=" + CID;
            MySqlDataAdapter ada = new MySqlDataAdapter(com1, MyDatabase.giricon);
            DataSet ds = new DataSet();
            ada.Fill(ds, "TID");
            string TID_tmp = (string)ds.Tables["TId"].Rows[0][0];
            if (TID_tmp == MyDatabase.TID)
            {
                string com2 = "UPDATE choose SET Score=" + grade + " WHERE sid=" + SID + " and cid=" + CID;
                MySqlCommand msc = new MySqlCommand(com2, MyDatabase.giricon);
                int a=msc.ExecuteNonQuery();
                if (a > 0)
                {
                    MessageBox.Show("成功修改!");
                }
                else
                {
                    MessageBox.Show("无对应项!");
                }
            }
            else
            {
                MessageBox.Show("缺少修改权限!");
            }
            this.Close();

        }

        private void modify_grade_Load(object sender, EventArgs e)
        {

        }

        private void modify_grade_FormClosed(object sender, FormClosedEventArgs e)
        {
            Console.WriteLine("close!");
            //this.Dispose();
        }
    }
}
