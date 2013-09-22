using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Arkanoid
{
    public class BonusBrick : Brick
    {
        protected int speedX;
        protected int speedY;
        protected int bonus;

        public BonusBrick(int x, int y, int width, int height, bool visible, Bitmap bitmapa, int speedX, int speedY, int bonus) :
            base(x, y, width, height, visible, bitmapa)
        {
            this.speedX = speedX;
            this.speedY = speedY;
            this.bonus = bonus;
        }

        public void move(OknoGry okno, Paddle belka)
        {
            if (visible)
            {
                x += speedX;
                y += speedY;

                if (x < 0)
                {
                    x = 0;
                    speedX *= -1;
                }
                else if (x + width > okno.Width)
                {
                    x = okno.Width - width;
                    speedX *= -1;
                }

                if (((x > belka.getX() && x < belka.getX() + belka.getWidth()) || (x + width > belka.getX() && x + width < belka.getX() + belka.getWidth())) &&
                    (y + height > belka.getY() && y + height < belka.getY() + belka.getHeight()))//warunek zderzenia z belka
                {
                    applyBonus(bonus, belka, okno.pilka, okno.lista, okno);
                    dezaktywuj();
                }
                else if (y + height > okno.Height)
                {
                    dezaktywuj();
                }
            }
        }

        private void applyBonus(int bonus, Paddle belka, Ball pilka, List<Brick>lista, OknoGry okno)
        {
            if (bonus == 2)
            {
                belka.setWidth(belka.getWidth() + 50);
                Message bonusInfo = new Message(okno.Width / 2, okno.Height / 2, "Zwiększenie belki!", 500, false, Color.Black);
                okno.listaMessage.Add(bonusInfo);//dodanie wiadomości
            }
            else if (bonus == 3)
            {
                pilka.setSpeedX(pilka.getSpeedX() + 3);
                pilka.setSpeedY(pilka.getSpeedY() + 3);
                Message bonusInfo = new Message(okno.Width / 2, okno.Height / 2, "Przyspieszenie!", 500, false, Color.Black);
                okno.listaMessage.Add(bonusInfo);//dodanie wiadomości
            }
            else if (bonus == 4)
            {
                pilka.setSpeedX(pilka.getSpeedX() - 3);
                pilka.setSpeedY(pilka.getSpeedY() - 3);
                if (pilka.getSpeedX() == 0) pilka.setSpeedX(-1);
                if (pilka.getSpeedY() == 0) pilka.setSpeedY(-1);//blokada przed ruchem poziomym i pionowym
                Message bonusInfo = new Message(okno.Width / 2, okno.Height / 2, "Zmiana kierunku piłki!", 500, false, Color.Black);
                okno.listaMessage.Add(bonusInfo);//dodanie wiadomości
            }
            else if (bonus == 5)
            {
                foreach (Brick brick in lista)
                {
                    brick.setY(brick.getY() + brick.getHeight());
                }
                Message bonusInfo = new Message(okno.Width / 2, okno.Height / 2, "Obniżenie stropu!", 500, false, Color.Black);
                okno.listaMessage.Add(bonusInfo);//dodanie wiadomości
            }
            else if (bonus == 6)
            {
                foreach (Brick brick in lista)
                {
                    brick.setHeight(brick.getHeight() / 2);
                }
                Message bonusInfo = new Message(okno.Width / 2, okno.Height / 2, "Zmiana rozmiaru kafelków", 500, false, Color.Black);
                okno.listaMessage.Add(bonusInfo);//dodanie wiadomości
            }
            else if (bonus == 7)
            {
                foreach (Brick brick in lista)
                {
                    brick.setHeight(brick.getHeight() * 3 / 2);
                }
                Message bonusInfo = new Message(okno.Width / 2, okno.Height / 2, "Zwiększenie rozmiaru kafelków",500, false, Color.Black);
                okno.listaMessage.Add(bonusInfo);//dodanie wiadomości
            }

        }

        public void dezaktywuj()
        {
            visible = false;
        }
    }
}
