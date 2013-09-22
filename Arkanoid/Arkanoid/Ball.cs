using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace Arkanoid
{
    public class Ball : Obiekt
    {
        protected int speedX;
        protected int speedY;
        protected int balls;


        public Ball(int x, int y, int width, int height, Bitmap bitmapa, bool visible, int speedX, int speedY) :
            base(x, y, width, height, visible, bitmapa)
        {
            this.speedX = speedX;
            this.speedY = speedY;
        }

        public int getSpeedX() { return this.speedX; }
        public int getSpeedY() { return this.speedY; }
        public void setSpeedX(int val) { this.speedX = val; }
        public void setSpeedY(int val) { this.speedY = val; }
        public int getBalls() { return this.balls; }
        public void setBalls(int val) { this.balls = val; }

        public void move(Paddle belka, OknoGry okno)
        {
            if (!okno.gra)
            {
                x = belka.getX() + belka.getWidth() / 2 - width / 2;
            }
            else
            {
                x += speedX;
                y += speedY;//poruszanie sie pilki
                if (x < 0)
                {
                    x = 0;
                    speedX *= -1;
                }
                else if (x > okno.Width - width)
                {
                    x = okno.Width - width;
                    speedX *= -1;
                }
                if (y < 0)
                {
                    y = 0;
                    speedY *= -1;
                }
                else if (y > okno.Height - height)
                {
                    okno.gra = false;
                    setStart(belka, okno);
                    Message poziom = new Message(okno.Width / 2, okno.Height / 2, "Tracisz zycie!", 1000, false, Color.Black);
                    okno.listaMessage.Add(poziom);//dodanie wiadomości
                    okno.pilka.setBalls(okno.pilka.getBalls() - 1);

                    if (okno.pilka.getBalls() <= 0)
                    {
                        MessageBox.Show("Przegrana!");
                        Application.Exit();
                    }
                    
                }//sprawdzenie czy nie wychodzi poza ramy
                if(this*belka>0)
                {
                    speedY *= -1;
                }//kolizja z belka

                
            }
        }

        public void setStart(Paddle belka, OknoGry okno)
        {
            setX(belka.getX() + belka.getWidth() / 2 - width / 2);
            setY(okno.Height - belka.getHeight() - height - 40);
            setSpeedX(6);
            setSpeedY(-6);
            belka.setWidth(belka.getBitmap().Width);
        }
    }
}
