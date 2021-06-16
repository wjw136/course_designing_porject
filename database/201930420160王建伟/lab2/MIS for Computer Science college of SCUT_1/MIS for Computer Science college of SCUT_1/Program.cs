using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySqlConnector;//调用MySQL动态库
using System.Data;
using MIS_for_Computer_Science_college_of_SCUT_1;
using System.Runtime.InteropServices;
namespace MIS_for_Computer_Science_college_of_SCUT_1
{

    static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [DllImport("kernel32.dll")]
        public static extern Boolean AllocConsole();
        [DllImport("kernel32.dll")]
        public static extern Boolean FreeConsole();
        [STAThread]
        static void Main()
        {

            AllocConsole();
            //Console.WriteLine("111122222222222222222222222");

            Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //string str = "server=localhost;User Id=william;password=123456;Database=MDB";//连接MySQL的字符串
            MySqlConnection giricon = MyDatabase.giricon;
            //giricon = new MySqlConnection(str);//实例化链接
            while (true)
            {
                try
                {

                    giricon.Open();//开启连接
                                   //MySqlCommand mycmd = new MySqlCommand("select * from Student;", giricon);
                    if (giricon.State == ConnectionState.Open)
                    {
                        MessageBox.Show("连接成功！");
                    }
                    //Console.ReadLine();
                    break;
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    MessageBox.Show("数据库连接异常！");
                }
            }
            //Application.
            MyDatabase.f1 = new main_menu();
            //f1=new main_menu();
            Application.Run(MyDatabase.f1);
            giricon.Close();//关闭
        }
    }

    //数据类
    public class MyDatabase
    {

        static string str = "server=localhost;User Id=william;password=123456;Database=MDB";//连接MySQL的字符串
        static public MySqlConnection giricon = new MySqlConnection(str);

        //页面
        static public main_menu f1;
        static public stu_login stu1;
        static public tch_login tch1;
        static public mer_login mer1;
        static public string SID;
        static public string TID;
        static public string MID;
        static public DataSet sqlQuery(string s)
        {
            Console.WriteLine(s);
            MySqlDataAdapter sda;
            DataSet ds = new DataSet();
            /*
             * try-catch-finally在数据库查询以及程序调试中的作用--可以避免提前终止
             * exception e;e.message;
             */
            try
            {
                sda = new MySqlDataAdapter(s, MyDatabase.giricon);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                return ds;
            }
            sda.Fill(ds, "course");
            return ds;
        }
        static public int sqlNoQuery(string s)
        {
            Console.WriteLine(s);
            MySqlCommand com = new MySqlCommand(s, giricon);
            try
            {
                com.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                return -1;
            }

            return 1;
        }
    }
}
