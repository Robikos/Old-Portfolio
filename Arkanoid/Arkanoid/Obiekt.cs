using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Arkanoid
{
    public abstract class Obiekt
    {
        protected int x;
        protected int y;
        protected int width;
        protected int height;
        protected bool visible;
        protected Bitmap bitmapa;

        public Obiekt(int x, int y, int width, int height, bool visible, Bitmap bitmapa)
        {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
            this.visible = visible;
            this.bitmapa = bitmapa;
        }

        public int getX() { return this.x; }
        public int getY() { return this.y; }
        public int getWidth() { return this.width; }
        public int getHeight() { return this.height; }
        public bool getVisible() { return this.visible; }
        public Bitmap getBitmap() { return this.bitmapa; }
        public void setX(int val) { this.x = val; }
        public void setY(int val) { this.y = val; }
        public void setWidth(int val) { this.width = val; }
        public void setHeight(int val) { this.height = val; }
        public void setVisible(bool val) { this.visible = val; }
        public void setBitmap(Bitmap val) { this.bitmapa = val; }

        public virtual void draw(Graphics g)
        {
            g.DrawImage(this.bitmapa, this.x, this.y, this.width, this.height);
        }

        public static int operator*(Obiekt klocek, Obiekt pilka)
        {
            //z gory
            if (pilka.getY() < klocek.y && pilka.getY() > klocek.y - pilka.getHeight() && pilka.getX() > klocek.x - pilka.getWidth() && pilka.getX() < klocek.x + klocek.width && klocek.visible)
            {
                return 1;
            }
            //z dolu
            else if (pilka.getY() < klocek.y + klocek.height && pilka.getY() > klocek.y + klocek.height - pilka.getHeight() && pilka.getX() > klocek.x - pilka.getWidth() && pilka.getX() < klocek.x + klocek.width && klocek.visible)
            {
                return 2;
            }
            //z lewej
            if (pilka.getX() < klocek.x && pilka.getX() + pilka.getWidth() > klocek.x && pilka.getY() > klocek.y && pilka.getY() < klocek.y + klocek.height && klocek.visible)
            {
                return 3;
            }
            //z prawej
            else if (pilka.getX() < klocek.x + klocek.width && pilka.getX() + pilka.getWidth() > klocek.x + klocek.width && pilka.getY() > klocek.y && pilka.getY() < klocek.y + klocek.height && klocek.visible)
            {
                return 4;
            }
            return 0;
        }
    }
}
