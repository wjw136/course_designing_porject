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
    public partial class course_choose : Form
    {
        public course_choose()
        {
            InitializeComponent();
        }

        private void fontDialog1_Apply(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
        /*
         * 添加
         */
        private void button1_Click(object sender, EventArgs e)
        {
            string str_course = this.textBox2.Text;
            string command = "SELECT count(CID) from course where CID=" + str_course;//自定义sql查询语言 
            MySqlCommand mySqlCommand = new MySqlCommand(command, MyDatabase.giricon);
            int i = Convert.ToInt32(mySqlCommand.ExecuteScalar());
            if (i == 0) MessageBox.Show("课程不存在");
            else
            {
                string command1 = "SELECT TID from teacher NATURAL JOIN course WHERE CID=" + str_course;
                MySqlDataAdapter data1 = new MySqlDataAdapter(command1, MyDatabase.giricon);
                DataSet ds = new DataSet();
                data1.Fill(ds,"TID");
                DataTable dtable= ds.Tables["TID"];
                DataRowCollection drows = dtable.Rows;
                DataRow drow = drows[0];
                String TID = (String)drow[0];
                //Console.WriteLine(TID);
                DateTime currentTime = System.DateTime.Now;
                string defaultYear = currentTime.Year.ToString("d4");
                string command2 = string.Format("INSERT into choose(SID,CID,TID,ChooseYear) VALUES(" + MyDatabase.SID + "," + str_course + "," + TID + ","+defaultYear+")");
                Console.WriteLine(command2);
                MySqlCommand com1 =new  MySqlCommand(command2, MyDatabase.giricon);
                com1.ExecuteNonQuery();
                MessageBox.Show("选课成功!");
                this.Close();
            }
        }

        private void course_choose_Load(object sender, EventArgs e)
        {

        }
        /*
         * 退出
         */
        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
