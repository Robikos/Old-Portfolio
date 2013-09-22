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

namespace Arkanoid
{
    public partial class OknoGry : Form
    {
        public List<Brick> lista = new List<Brick>();
        public List<BonusBrick> listaBonus = new List<BonusBrick>();
        public List<Message> listaMessage = new List<Message>();
        List<Bitmap> bitmapy = new List<Bitmap>();
        List<string> poziomy = new List<string>();

        const string path = "Dane/poziomy.txt";

        Bitmap bitmapa = new Bitmap("Dane/poziom.jpg");
        Bitmap klocekBit = new Bitmap("Dane/klocek.jpg");
        Bitmap belkaBit = new Bitmap("Dane/belka.jpg");
        Bitmap pilkaBit = new Bitmap("Dane/kulka.jpg");
        public Bitmap bonusBit = new Bitmap("Dane/legon.jpg");
        Graphics g, h;
        Bitmap surface;
        Pen p = new Pen(Color.Black);
        public Paddle belka;
        public Ball pilka;
        public Random lotto = new Random();

        int level = 1;
        int ileLevel = 0;
        public bool gra = false;
        Message zycia;

        public OknoGry()
        {
            InitializeComponent();

            h = this.CreateGraphics();
            surface = new Bitmap(Width, Height);
            g = Graphics.FromImage(surface);//surface - bufor, g-obsluga bufora, h-obsluga formy

            pilkaBit.MakeTransparent(Color.White);
            belka = new Paddle(Width / 2 - belkaBit.Width / 2, Height - belkaBit.Height - 40, belkaBit.Width, belkaBit.Height, belkaBit);
            pilka = new Ball(Width / 2, Height - belkaBit.Height - 40 - pilkaBit.Height, 20, 20, pilkaBit, true, 6, -6);
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            Bitmap temp = new Bitmap(klocekBit.Width, klocekBit.Height);
            g.Clear(Color.White);
            Graphics.FromImage(temp).Clear(Color.White);
            bitmapy.Add(temp);
            bitmapy.Add(new Bitmap("Dane/legoc.jpg"));
            bitmapy.Add(new Bitmap("Dane/legoz.jpg"));
            bitmapy.Add(new Bitmap("Dane/legon.jpg"));
            bitmapy.Add(new Bitmap("Dane/czeko.jpg"));//dodanie bitmap klockow do listy

            skompletujLevele();
            wczytajLevel(level);
            timer1.Start();
        }

        private void skompletujLevele()
        {
            poziomy.Clear();
            string odczyt = "";
            System.IO.FileStream plik;
            try
            {
                plik = new FileStream(path, FileMode.Open);
                StreamReader sr = new StreamReader(plik);
                odczyt = sr.ReadLine();
                //ileLevel++;
                while (odczyt != null)
                {
                    ileLevel++;
                    poziomy.Add(odczyt);
                    odczyt = sr.ReadLine();
                }
                sr.Close();
                plik.Close();
            }
            catch (FileNotFoundException)
            {
                MessageBox.Show("Brak pliku!");
                Application.Exit();
            }

            pilka.setBalls(5);
            
        }

        private void move()
        {
            belka.move(this);//poruszanie belką
            pilka.move(belka, this);//poruszanie pilką
            int k=0;//zmienna pomocnicza

            g.DrawImage(bitmapa, 0, 0, bitmapa.Width, bitmapa.Height);//rysuj tlo
            belka.draw(g);//belka
            pilka.draw(g);//rysowanie pilki

            foreach (Brick brick in lista)
            {
                k = brick * pilka;
                if (k > 0)
                {
                    brick.efektKolizji(k, pilka, this);
                }
                brick.draw(g);//rysuj cegielke
            }
            //pilkaParzy();
            foreach (BonusBrick bonus in listaBonus)
            {
                bonus.move(this, belka);
                bonus.draw(g);//rysuj bonus
            }

            //update żyć
            zycia.setText("Piłki :" + pilka.getBalls());

            foreach (Message message in listaMessage)
            {
                message.draw(g);
            }

            usuwajNieaktywne();
            //kontrola zasobow

            sprawdzWygrana();
 
            h.DrawImage(surface, 0, 0);//na bufor
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            move();
        }

        private void Form1_Click(object sender, EventArgs e)
        {
            gra = true;
        }

        private void wczytajLevel(int level)
        {
            if (level > ileLevel)
            {
                MessageBox.Show("Wygrałeś! Gratulujemy.");
                Application.Exit();
            }
            lista.Clear();
            listaBonus.Clear();
            listaMessage.Clear();
            gra = false;
            string odczyt = "";
            System.IO.FileStream plik =
                    new FileStream("Dane/"+poziomy[level-1], FileMode.Open);//otwarcie pliku odpowiedzialnego za kolejny poziom
            StreamReader sr = new StreamReader(plik);
            int a = Int16.Parse(sr.ReadLine());
            int b = Int16.Parse(sr.ReadLine());
            int width = Int16.Parse(sr.ReadLine());
            int height = Int16.Parse(sr.ReadLine());
            odczyt = sr.ReadLine();
            tworzMape(a, b, width, height, odczyt);

            Message poziom = new Message(Width / 2, Height / 2, "Poziom :" + level, 1000, false, Color.Black);
            listaMessage.Add(poziom);//dodanie wiadomości

            zycia = new Message(20, 400, "Piłki :" + pilka.getBalls(), 10, true, Color.White);//statyczny tekst
            listaMessage.Add(zycia);
            

            pilka.setX(Width / 2);
            pilka.setY(Height - belkaBit.Height - 40 - pilkaBit.Height);//ustawienie poczatkowe pilki
        }

        public void tworzMape(int a, int b, int width, int height, string odczyt)
        {
            for (int i = 0; i < b; i++)
            {
                for (int j = 0; j < a; j++)
                {
                    int k = Int32.Parse(odczyt[i * a + j].ToString());
                    if (k > 0)
                    {
                        Brick brick = new Brick(j * width*2, i * height*2, width*2, height*2, true, bitmapy[k]);//razy dwa bo skalowanie
                        lista.Add(brick);
                    }
                }
            }
        }

        public void usuwajNieaktywne()
        {
            if (listaBonus.Count > 0 && listaBonus[0].getVisible() == false) listaBonus.RemoveAt(0);
            if (listaMessage.Count > 0 && listaMessage[listaMessage.Count-1].getVisible() == false) listaMessage.RemoveAt(listaMessage.Count-1);
        }

        public void sprawdzWygrana()
        {
            int licz = 0;
            foreach (Brick brick in lista)
            {
                if (brick.getVisible() == false) licz++;
            }
            if (licz == lista.Count)
            {
                level++;
                wczytajLevel(level);
            }
        }

    }
}