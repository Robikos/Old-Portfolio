using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Arkanoid
{
    public class Brick : Obiekt
    {
        public Brick(int x, int y, int width, int height, bool visible, Bitmap bitmapa)
            : base(x, y, width, height, visible, bitmapa)
        {
         
        }

        public override void draw(Graphics g)
        {
            if (this.visible)
                g.DrawImage(this.bitmapa, this.x, this.y, this.width, this.height);
        }

        public void efektKolizji(int kolizja, Ball pilka, OknoGry okno)
        {
            switch (kolizja)
            {
                case 1:
                case 2:
                    visible = false;
                    pilka.setSpeedY(pilka.getSpeedY() * -1);
                    break;
                case 3:
                case 4:
                    visible = false;
                    pilka.setSpeedX(pilka.getSpeedX() * -1);
                    break;
            }

            if (okno.lotto.Next(100) < 10)//jeśli bonusik
            {
                BonusBrick bonus = new BonusBrick(x, y, width / 2, height / 2, true, okno.bonusBit, 1, 4, okno.lotto.Next(7));
                
                okno.listaBonus.Add(bonus);
            }
            
        }
    }
}
