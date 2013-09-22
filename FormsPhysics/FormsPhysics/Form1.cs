using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FormsPhysics
{
    public partial class Form1 : Form
    {
        int k = 0;
        double t = 0.0;
        double funkcjaR = 0.0;
        double funkcjaI = 0.0;
        double wynik = 0.0;
        double maxwynik = 0.0;
        Bitmap bufor = new Bitmap(300, 300);
        Graphics g;
        Pen p = new Pen(Color.Black);
        Pen p2 = new Pen(Color.Black);
        Point prev, next;
        
        int red,green,blue;


        List<int> lista = new List<int>();

        public Form1()
        {
            InitializeComponent();
            g = Graphics.FromImage(bufor);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            k++;
            lista.Add(Int32.Parse(textBox1.Text));
            listBox1.Items.Add("n =" + textBox1.Text);
            if (label2.Text == "Brak")
            {
                label2.Text = "F(" + textBox1.Text + ") ";
            }
            else
            {
                label2.Text += "+ F(" + textBox1.Text + ") ";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            timer1.Stop();
            k = 0;
            lista.Clear();
            listBox1.Items.Clear();
            label2.Text = "Brak";
            maxwynik = 0.0;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            t += 0.05;
            prev = new Point(0, 0);
            g.Clear(Color.White);

            for (int x = 1; x <= 300; x++)
            {
                funkcjaR = 0.0;
                funkcjaI = 0.0;
                wynik = 0.0;
                foreach (int n in lista)
                {
                    funkcjaR += Math.Cos(0.577934 * n * t) * Math.Sin(0.01046 * n * x);
                    funkcjaI += Math.Sin(0.577934 * n * t) * Math.Sin(0.01046 * n * x);
                }
                wynik = Math.Pow(funkcjaR, 2) + Math.Pow(funkcjaI, 2);
                wynik = wynik / (double)(k*k);//normalizacja

                if (wynik > maxwynik)
                {
                    maxwynik = wynik;
                    label4.Text = maxwynik.ToString();
                }
                
                toRGB(wynik*359.9, 0.8, 0.8); 
                wynik = wynik * 300;

                

                next = new Point(x,300- (int)wynik);
                g.DrawLine(p, prev, next);//rysowanie na buforze
                p2.Color = Color.FromArgb(red, green, blue);
                g.DrawLine(p2, next, new Point(x, 300));
                prev = next;
            }
            pictureBox1.Image = bufor;

        }

        private void button3_Click(object sender, EventArgs e)
        {
            k = lista.Count;
            label5.Text = k.ToString();
            maxwynik = 0.0;
            timer1.Start();
        }

        private void toRGB(double h, double s, double v)
        {
            if (v == 0)
            {
                red = 0;
                green = 0;
                blue = 0;
            }
            else
            {
                h = h / (double)60;
                int i = (int)h;
                double f = h - (float)i;
                double p = v * (1 - s);
                double q = v * (1 - (s * f));
                double t = v * (1 - (s * (1 - f)));
                if (i == 0) { red = (int)(v * 255); green = (int)(t * 255); blue = (int)(p * 255); }
                else if (i == 1) { red = (int)(q * 255); green = (int)(v * 255); blue = (int)(p * 255); }
                else if (i == 2) { red = (int)(p * 255); green = (int)(v * 255); blue = (int)(t * 255); }
                else if (i == 3) { red = (int)(p * 255); green = (int)(q * 255); blue = (int)(v * 255); }
                else if (i == 4) { red = (int)(t * 255); green = (int)(p * 255); blue = (int)(v * 255); }
                else if (i == 5) { red = (int)(v * 255); green = (int)(p * 255); blue = (int)(q * 255); }

            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            timer1.Start();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            timer1.Stop();
        }
    }
}
