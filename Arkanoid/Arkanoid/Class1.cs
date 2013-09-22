using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Arkanoid
{
    class Brick
    {
        int x;
        int y;
        int width;
        int height;
        bool visible;
        int value;
        Bitmap bitmapa;
        int shape;

        abstract public void draw();
        abstract public void animate();
        public bool isVisible();
        //public Rectangle getPosition();
        //public void setPosition(Rectangle rect);
    }

    class BonusBrick: Brick
    {
        int visibleTime;
        int speedX;
        int speedY;
        bool move;
        int bonus;

        public void draw();
        //public void move();
        public void animate();
        public void getBonus();
    }

    class FireBrick : Brick
    {
        Bitmap pattern;
        Bitmap fireball;
        int fireX;
        int fireY;
        int fireW;
        int fireH;
        bool fireVisible;
        bool firePoints;

        public void shot();
        public void appearBall();
    }

    class Paddle
    {
        int x;
        int y;
        int width;
        int height;
        Bitmap pattern;
        int color;
        int size;

        public void draw();
        public void move();
    }

    class ReversedPaddle : Paddle
    {
        int reverseSpeed;
        int frequency;

        public void shake();
        public void reverse();
    }

    class Ball
    {
        int x;
        int y;
        int width;
        int height;
        Bitmap bitmapa;
        int background;
        bool visible;
        int visibleLevel;
        int speedX;
        int speedY;
        int balls;

        public void draw();
        public void move();
        public void interact();
        public void ballsLeft();
    }

    class Score
    {
        string name;
        int score;
        int level;
        DateTime data;
        int pos;

        public void createNewScore();
        public void assign();
    }
}
