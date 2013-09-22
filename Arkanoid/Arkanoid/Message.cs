using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Arkanoid
{
    public class Message : Obiekt
    {
        protected string text;
        protected Font font;
        protected int visibleTime;
        protected bool statyczny;
        protected Color kolor;

        public void setText(string val) { this.text = val; }

        public Message(int x, int y, int width, int height, bool visible, string text, Font font, int visibleTime, Bitmap bitmapa, bool statyczny, Color kolor) :
            base(x, y, width, height, visible, bitmapa)
        {
            this.text = text;
            this.font = font;
            this.visibleTime = visibleTime;
            this.statyczny = statyczny;
            this.kolor = kolor;
        }

        public Message(int x, int y, string text, int visibleTime, bool statyczny, Color kolor):
            base(x, y, 10, 10,true,new Bitmap(10,10))
        {
            this.text = text;
            this.font = new Font("Times New Roman", 16.0f);
            this.visibleTime = visibleTime;
            this.statyczny = statyczny;
            this.kolor = kolor;
        }//przeciążony konstruktor

        public override void draw(Graphics g)
        {
            if (visible)
            {
                g.DrawString(text, font, new SolidBrush(this.kolor), new Point(x, y));
                if(!statyczny)visibleTime -= 10;
                if (visibleTime <= 0) schowaj();
            }
        }

        public void schowaj()
        {
            visibleTime = 0;
            visible = false;
        }
    }
}
