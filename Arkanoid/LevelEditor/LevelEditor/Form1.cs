using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace LevelEditor
{
    public partial class Form1 : Form
    {
        Graphics g;
        List<Bitmap> bitmapy = new List<Bitmap>();
        List<Brick> lista = new List<Brick>();
        int a, b, width, height = 0;
        string path = "";
        public Form1()
        {
            InitializeComponent();
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            g = Graphics.FromImage(pictureBox1.Image);
            width = 155;
            height = 79;
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            Bitmap temp = new Bitmap(width, height);
            g.Clear(Color.White);
            Graphics.FromImage(temp).Clear(Color.White);
            bitmapy.Add(temp);
            bitmapy.Add(new Bitmap("legoc.jpg"));
            bitmapy.Add(new Bitmap("legoz.jpg"));
            bitmapy.Add(new Bitmap("legon.jpg"));
            bitmapy.Add(new Bitmap("czeko.jpg"));
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox3.Text = "" + pictureBox1.Width / Int32.Parse(textBox1.Text);
            textBox4.Text = "" + pictureBox1.Height / Int32.Parse(textBox2.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            a = Int32.Parse(textBox1.Text);
            b = Int32.Parse(textBox2.Text);
            width = Int32.Parse(textBox3.Text);
            height = Int32.Parse(textBox4.Text);
            lista.Clear();
            g.Clear(Color.White);
            for (int i = 0; i < b; i++)
            {
                for (int j = 0; j < a; j++)
                {
                    g.DrawImage(bitmapy[comboBox1.SelectedIndex], j * width, i * height, width, height);
                    Brick brick = new Brick(j * width, i * height, bitmapy[comboBox1.SelectedIndex], comboBox1.SelectedIndex>0?true:false, comboBox1.SelectedIndex);
                    lista.Add(brick);
                    pictureBox1.Refresh();
                }
            }
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            int x = (e.Location.X / width);
            int y = (e.Location.Y / height);
            if (y * a + x < lista.Count)
            {
                lista[y * a + x].bitmapa = bitmapy[comboBox1.SelectedIndex];
                lista[y * a + x].bitmapaNum = comboBox1.SelectedIndex;
                if (comboBox1.SelectedIndex == 0) lista[y * a + x].visible = false;
                else lista[y * a + x].visible = true;
                g.DrawImage(lista[y * a + x].bitmapa, lista[y * a + x].x, lista[y * a + x].y, width, height);
                pictureBox1.Refresh();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Filter = "Dokument tekstowy|*.txt";
            saveFileDialog1.Title = "Zapisz poziom";
            saveFileDialog1.ShowDialog();
            if (saveFileDialog1.FileName != "")
            {
                System.IO.FileStream plik =
                    (System.IO.FileStream)saveFileDialog1.OpenFile();
                StreamWriter sw = new StreamWriter(plik);
                sw.WriteLine(a);
                sw.WriteLine(b);
                sw.WriteLine(width);
                sw.WriteLine(height);
                string zapis="";
                for (int i=0;i<lista.Count;i++)
                {
                    zapis += lista[i].bitmapaNum;
                    //if ((i + 1) % a == 0) zapis += "\n";
                }
                sw.Write(zapis);
                sw.Close();
                plik.Close();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            lista.Clear();
            g.Clear(Color.White);
            openFileDialog1.Filter = "Dokument tekstowy|*.txt";
            openFileDialog1.Title = "Wczytaj poziom";
            openFileDialog1.ShowDialog();
            string odczyt = "";
            if (openFileDialog1.FileName != "")
            {
                System.IO.FileStream plik =
                    (System.IO.FileStream)openFileDialog1.OpenFile();
                StreamReader sr = new StreamReader(plik);
                a = Int16.Parse(sr.ReadLine());
                MessageBox.Show("" + a);
                b = Int16.Parse(sr.ReadLine());
                MessageBox.Show("" + b);
                width = Int16.Parse(sr.ReadLine());
                MessageBox.Show("" + width);
                height = Int16.Parse(sr.ReadLine());
                MessageBox.Show("" + height);
                odczyt = sr.ReadLine();
                MessageBox.Show(odczyt);
                sr.Close();
                plik.Close();
            }
            for (int i = 0; i < b; i++)
            {
                for (int j = 0; j < a; j++)
                {
                    int k = Int32.Parse(odczyt[i * a + j].ToString());
                    Brick brick = new Brick(j * width, i * height, bitmapy[k], k>0?true:false, k);
                    lista.Add(brick);
                    g.DrawImage(bitmapy[k], j * width, i * height, width, height);
                    pictureBox1.Refresh();
                }
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (path == "") button3.PerformClick();
            else
            {
                System.IO.FileStream plik =
                    new FileStream(path, FileMode.Create);
                StreamWriter sw = new StreamWriter(plik);
                sw.WriteLine(a);
                sw.WriteLine(b);
                sw.WriteLine(width);
                sw.WriteLine(height);
                string zapis = "";
                for (int i = 0; i < lista.Count; i++)
                {
                    zapis += lista[i].bitmapaNum;
                    if ((i + 1) % a == 0) zapis += "\n";
                }
                sw.Write(zapis);
                sw.Close();
                plik.Close();
            }
        }
    }

    public class Brick
    {
        public int x;
        public int y;
        public Bitmap bitmapa;
        public bool visible;
        public int bitmapaNum;

        public Brick(int x, int y, Bitmap bitmapa, bool visible,int bitmapaNum)
        {
            this.x = x;
            this.y = y;
            this.bitmapa = bitmapa;
            this.visible = visible;
            this.bitmapaNum = bitmapaNum;
        }
    }
}
