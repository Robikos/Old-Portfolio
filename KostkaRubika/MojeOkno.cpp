#include "MojeOkno.h"
#include "Modele.h"
#include "Varia.h"
#include <time.h>
#include <cstdlib>
#include <cstdio>

void CMojeOknoGL::RysujAktorow()
{
	const float x0 = 1.0;
	const float y0 = 1.0;
	const float z0 = 1.0;

	static GLuint listyWyswietlania=NULL;
	if(!glIsList(listyWyswietlania))
		listyWyswietlania = TworzListeWyswietlania(x0,y0,z0,true);

	//RysujAktorow3(listyWyswietlania);

	static unsigned int czcionkaBitmapowa=NULL;
	if(czcionkaBitmapowa==NULL)
		czcionkaBitmapowa=Varia::StworzCzcionke(false,uchwytOkna,"Arial CE",30,true,false,32,255);

	glCallList(listyWyswietlania+2);//ukladzik

	//YOUR TIME
	kostka.animate(kostka.obrot);
	
}

void CMojeOknoGL::RysujAktorow2()
{
	const float x0 = 1.0;
	const float y0 = 1.0;
	const float z0 = 1.0;
	srand(time(NULL));

	float first[3];
	float second[3];
	float third[3];//kolory

	glRotatef(-30,0,1,1);
	glScalef(0.25,0.25,0);
	glLineWidth(2.0);

	//RysujUklad();

	for(int i=-10;i<=10;i++)
		for(int j=5;j>-5;j--)
		{
			glPushMatrix();
			if(!((i+j)%2)) glScalef(1,-1,1);
			glTranslatef(i*x0,2*j*y0,0); 
				
			losujKolory(first,second,third);
			RysujTrojkat(x0,y0,z0,first,second,third);

			glPopMatrix();
		}
}

void CMojeOknoGL::RysujTrojkat(float x0, float y0, float z0, float* first, float* second, float* third) const
{
	//Rysowanie trójk¹ta
	glBegin(GL_TRIANGLES);
	//ustalanie trzech wierzcholkow trojkata(werteksow xyz)
	//(0,0,z) jest mniej wiecej w srodku ekranu
	//glColor3f(1.0,0.0,0.0);
	glColor3fv(first);
	glVertex3f(-x0,-y0,0); //dolny lewy
	//glColor3f(0.0,0.0,1.0);
	glColor3fv(second);
	glVertex3f(x0,-y0,0); //dolny prawy
	//glColor3f(0.0,1.0,0.0);
	glColor3fv(third);
	glVertex3f(0,y0,0); //górny
	//koniec rysowania figury
	glEnd();
}

void CMojeOknoGL::losujKolory(float* first, float* second, float* third)
{
	for(int i=0;i<3;i++)
	{
		first[i]=rand()%255 / 255.0f;
		second[i] = rand()%255 / 255.0f;
		third[i] = rand()%255 / 255.0f;
	}	
}

LRESULT CMojeOknoGL::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int IDT_TIMER_ANIMACJI=1;
	long wynik = COknoGL::WndProc(hWnd,message,wParam,lParam);

	switch(message)
	{
	case WM_CREATE:
		if (SetTimer(hWnd, IDT_TIMER_ANIMACJI,50,NULL)==0)
			MessageBox(hWnd, "NIE UDALO SIE USTAWIC TIMERA","",MB_OK | MB_ICONERROR);
		przesuniecie = 0;
		poprzedniCzas = GetTickCount();
		break;
	case WM_TIMER:
		switch(wParam)
		{
		case IDT_TIMER_ANIMACJI:
			long biezacyCzas=GetTickCount();
			przesuniecie+=0.0005f*(biezacyCzas-poprzedniCzas);
			poprzedniCzas = biezacyCzas;
			RysujScene();
			break;
		}
		wynik=0;
		break;
	case WM_DESTROY:
		KillTimer(uchwytOkna, IDT_TIMER_ANIMACJI);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case 'Z':
			if(!kostka.anim)
			{
				kostka.obrot[0]=-1;
				kostka.obrot[1]=3;
				kostka.obrot[2]=3;
				kostka.anim = true;
			}
			break;
		case 'X':
			if(!kostka.anim)
			{
				kostka.obrot[0]=0;
				kostka.obrot[1]=3;
				kostka.obrot[2]=3;
				kostka.anim = true;
			}
			break;
		case 'V':
			if(!kostka.anim)
			{
				kostka.obrot[0]=1;
				kostka.obrot[1]=3;
				kostka.obrot[2]=3;
				kostka.anim = true;
			}
			break;
		case 'B':
			if(!kostka.anim)
			{
				kostka.obrot[0]=3;
				kostka.obrot[1]=0;
				kostka.obrot[2]=3;
				kostka.anim = true;
			}
			break;
		case 'N':
			if(!kostka.anim)
			{
				kostka.obrot[0]=3;
				kostka.obrot[1]=-1;
				kostka.obrot[2]=3;
				kostka.anim = true;
			}
			break;
		case 'M':
			if(!kostka.anim)
			{
				kostka.obrot[0]=3;
				kostka.obrot[1]=1;
				kostka.obrot[2]=3;
				kostka.anim = true;
			}
			break;
		case 'G':
			if(!kostka.anim)
			{
				kostka.obrot[0]=3;
				kostka.obrot[1]=3;
				kostka.obrot[2]=-1;
				kostka.anim = true;
			}
			break;
		case 'H':
			if(!kostka.anim)
			{
				kostka.obrot[0]=3;
				kostka.obrot[1]=3;
				kostka.obrot[2]=0;
				kostka.anim = true;
			}
			break;
		case 'J':
			if(!kostka.anim)
			{
				kostka.obrot[0]=3;
				kostka.obrot[1]=3;
				kostka.obrot[2]=1;
				kostka.anim = true;
			}
			break;
		}
	}

	return wynik;
}

unsigned int CMojeOknoGL::TworzListeWyswietlania(float dx, float dy, float dz, bool koloruj) const
{
	GLuint listyWyswietlania = glGenLists(3);

	glNewList(listyWyswietlania,GL_COMPILE);
	Modele::RysujSzescian(dx,koloruj);
	glEndList();

	glNewList(listyWyswietlania+1,GL_COMPILE);
	Modele::Niszczyciel(1.0,1.0,1.0);
	glEndList();

	glNewList(listyWyswietlania+2,GL_COMPILE);
	Modele::RysujUklad();
	glEndList();

	return listyWyswietlania;
}

void CMojeOknoGL::RysujAktorow3(GLuint listyWyswietlania)
{
	
	glPushMatrix();
	Modele::RysujNiebo(1.0,1.0,1.0);
	glScalef(1,-1,1);
	Modele::RysujPodloze(1.0,1.0,1.0);
	glPopMatrix();
	

	glPushMatrix();
	//glRotatef(15,0,1,1);
	Modele::RysujUklad();
	//glRotatef(90,1,0,0);
	//glRotatef(45,0,0,1);
	//Modele::RysujSzescian(2.0,true);
	glRotatef(-15,0,0,1);
	glTranslatef(0,1,-10+przesuniecie);
	glRotatef(-270,1,0,0);
	glCallList(listyWyswietlania+1);
	glPopMatrix();

	
	glColor3f(1,1,1);
	glTranslatef(0,-1,0);
	long biezacyCzas=GetTickCount();
	float katPhi = 0.1f*biezacyCzas;
	float katTheta = 0.01f*biezacyCzas;
	glRotatef(katPhi,0,1,0);
	glRotatef(katTheta,1,0,0);
	glCallList(listyWyswietlania);
	
}

void CMojeOknoGL::NapisyMarymontMatrix(unsigned int czcionkaBitmapowa)
{
	char* napis = "MARYMONT POTOK - AL. KRAKOWSKA P+R";
	if(przesuniecie > 3.0) przesuniecie = 0.0;

	glColor3ub(220,166,3);
	glNormal3f(0,0,1);
	glRasterPos3f(-przesuniecie+1,0,-0.5);
	Varia::Pisz(napis,strlen(napis),czcionkaBitmapowa,32);
	
	glBegin(GL_POINTS);
	glPointSize(1.0);
	glColor3f(0.5,0.5,0.5);
	glVertex3f(0,0,1);
	glEnd();

	float tab[16]={0.0};
	glGetFloatv(GL_MODELVIEW_MATRIX,tab);
	glColor3f(0.75,1.0,0.75);
	glNormal3f(0,0,1);
	for(int j=-1;j<=2;j++)
		for(int i=-1; i<=2;i++)
		{
			char buff[10];
			sprintf(buff,"%.5f",tab[(i+1)+4*(j+1)]);
			glRasterPos3f(j,i,-1); Varia::Pisz(buff,6,czcionkaBitmapowa,32);
		}
}