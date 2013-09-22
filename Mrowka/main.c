#include <allegro.h>

int moves[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//tablica okreslaj¹ca ruch w gore, prawo,dol,lewo,kolejnosc
//ruchow zgodna ze wskazowkami zegara
int a=10;//wielkosc kwadratu
int x,y; //wspolrzedne mrowki
int direction;//zwrot mrowki - 0-gora,1-prawo,2-dol,3-lewo
int width=640;
int height=700;//wielkosc okna
int bialy;
int czarny;//kody kolorów
char napis[20];
char str[10];
int main() 
{	
	allegro_init();
	install_keyboard();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	
		bialy=makecol(200,200,200);
	czarny=makecol(0,0,0);//ustawienie kodow kolorow
	
	BITMAP *buffer = create_bitmap(width, height);
	clear_to_color(buffer, bialy);
	
	x=width/2;
	y=height/2;//ustawienie mrowki w centrum
	direction=0;//mrowka zwrocona poczatkowo w gore
	
            while (!keypressed()) {             
                  
                  if(getpixel(buffer,x,y)==bialy)//jesli mrowka znajduje sie na polu bialym
                  {
                  //allegro_message("BIALY"); 
                  direction = (direction+3)%4;//obrot w lewo
                  rectfill(buffer,x-0.5*a,y-0.5*a,x+0.5*a,y+0.5*a,czarny);//zamalowanie pola na czarno                                          
                  }
                  else{
                  direction = (direction+5)%4;//obrot w prawo
                  rectfill(buffer,x-0.5*a,y-0.5*a,x+0.5*a,y+0.5*a,bialy);//zamalowanie pola na bialo
                  }
                  
                   x += a*moves[direction][0];
                  y += a*moves[direction][1];//przesuniecie mrowki w zadanym kierunku
                  
                  strcpy(napis,"X: ");
                  strcat(napis,itoa(x,str,10));
                  strcat(napis," Y: ");
                  strcat(napis,itoa(y,str,10));
                  strcat(napis," D: ");
                  strcat(napis,itoa(direction,str,10));
                   textout_centre_ex(buffer, font, napis,
                        SCREEN_W / 2, 0,
                        makecol(255, 0, 0), makecol(0, 0, 0));
                  
                  if(x<0.5*a || y<0.5*a || x>width-0.5*a || y>height-0.5*a)break;
                  //ochrona przed wyjsciem mrowki poza ramy ekranu
                  
                  blit(buffer, screen, 0, 0, 0, 0, 640, 700);//wklejenie bufora na ekran
                  rest(10);//odczekanie pomiêdzy kolejnym ruchem
            }
	readkey();
	destroy_bitmap(buffer);
	
	return 0;
}
END_OF_MAIN();
