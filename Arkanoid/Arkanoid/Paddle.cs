using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Arkanoid
{
    public class Paddle : Obiekt
    {
        public Paddle(int x, int y, int width, int height, Bitmap bitmapa)
            : base(x, y, width, height, true, bitmapa)
        {
        }

        public void move(OknoGry okno)
        {
            x = okno.PointToClient(System.Windows.Forms.Cursor.Position).X - bitmapa.Width / 2;//update belki
            if (x < 0) x = 0;
            else if (x > okno.Width - width) x = okno.Width - width;//kontrola ram okna
        }
    }
}
