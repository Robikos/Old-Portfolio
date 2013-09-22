using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Potencjal
{
    public partial class Form1 : Form
    {
        Graphics g;

        int k = 10; //stala przyciagania
        List<Mass> lista = new List<Mass>();

        public class Mass
        {
            public int x;
            public int y;
            public int m;//masa
            public int r;//promien na rysunku
            public Mass(int x, int y, int m) { this.x = x; this.y = y; this.m = m; this.r = 5 * this.m;}
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            g = Graphics.FromImage(pictureBox1.Image);
            //g = pictureBox1.CreateGraphics();
            g.Clear(Color.White);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Random rnd = new Random();
            //g.DrawLine(new Pen(new SolidBrush(Color.Black)),new Point(rnd.Next(pictureBox1.Width),rnd.Next(pictureBox1.Height)),new Point(rnd.Next(pictureBox1.Width),rnd.Next(pictureBox1.Height)));
            //pictureBox1.Refresh();

            if (listBox1.SelectedIndex >= 0)
            {
                lista.RemoveAt(listBox1.SelectedIndex);
                reloadPicture();
                reloadPotencjal();
                pictureBox1.Refresh();
                reloadBox();
            }
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            Mass m = new Mass(e.Location.X, e.Location.Y, Int32.Parse(textBox1.Text));
            lista.Add(m);
            reloadPicture();
            //tu bedzie reloadPicture() z wyliczeniem kropek i potem linii
            reloadPotencjal();
            pictureBox1.Refresh();
            reloadBox();
        }

        private void reloadBox()
        {
            listBox1.Items.Clear();
            for (int i = 0; i < lista.Count; i++)
            {
                listBox1.Items.Add("X: " + lista[i].x + "; Y: " + lista[i].y + "; M: " + lista[i].m);
            }
        }

        private void reloadPicture()
        {
            g.Clear(Color.White);
            for (int i = 0; i < lista.Count; i++)
            {
                Mass m = lista[i];
                g.DrawEllipse(new Pen(new SolidBrush(Color.Blue)), m.x - m.r, m.y - m.r, 2 * m.r, 2 * m.r);
            }
        }

        private double distance(int pX, int pY, int sX, int sY)
        {
            return Math.Sqrt((pX - sX) * (pX - sX) + (pY - sY) * (pY - sY));
        }

        private bool isFree(int pX, int pY)
        {
            for (int i = 0; i < lista.Count; i++)
                if (distance(pX, pY, lista[i].x, lista[i].y) <= lista[i].r) return false;
            return true;
        }

        private double potencjal(int pX, int pY)
        {
            double p = 0.0;
            for (int i = 0; i < lista.Count; i++) p += k * lista[i].m / distance(pX, pY, lista[i].x, lista[i].y);
            return p;
        }

        private void reloadPotencjal()
        {
            for(int x=0;x<pictureBox1.Width;x++)
                for (int y = 0; y < pictureBox1.Height; y++)
                {
                    if (isFree(x, y))
                    {
                        //MessageBox.Show("" + potencjal(x, y));
                        int k = (int)(100*potencjal(x, y));
                        if (k % 10 <= 1 || k % 10 >= 8)
                        {
                            g.DrawEllipse(new Pen(new SolidBrush(Color.Black)), x, y, 1, 1);
                        }
                    }
                }
        }
    }
}
