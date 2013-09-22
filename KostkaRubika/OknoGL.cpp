#include "OknoGL.h"
#define _USE_MATH_DEFINES
#include <math.h>

extern COknoGL* p_okno;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return p_okno->WndProc(hWnd,message,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow)
{
	POINT polozenieOkna={100,100};
	POINT rozmiarOkna={800,600};
	if (!p_okno->Init(hInstance,polozenieOkna,rozmiarOkna))
	{
		MessageBox(NULL,"Inicjacja okna nie powiodla sie!","Aplikacja OpenGL",MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}
	else return p_okno->Run();
}

LRESULT COkno::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		RECT rect;
		GetClientRect(hWnd,&rect);
		szerokoscObszaruUzytkowania = rect.right - rect.left;
		wysokoscObszaruUzytkowania = rect.bottom - rect.top;
		break;
	default:
		return (DefWindowProc(hWnd,message,wParam,lParam));
	}

	return 0L;
}

bool COkno::Init(HINSTANCE uchwytAplikacji, POINT polozenieOkna, POINT rozmiarOkna)
{
	char nazwaOkna[] = "Aplikacja OpenGL";

	WNDCLASSEX wc;
	wc.cbSize=sizeof(wc);
	wc.style=CS_HREDRAW | CS_VREDRAW | CS_OWNDC;//styl okna
	wc.lpfnWndProc=(WNDPROC)::WndProc;//procedura okna
	wc.cbClsExtra=0;//dodatkowe bajty zarezerwowane za klas¹ okna
	wc.cbWndExtra=0;//dodatkowe bajty zarezerwowane za instancja okna
	wc.hInstance = uchwytAplikacji;//instancja aplikacji
	wc.hIcon=NULL;
	wc.hIconSm=NULL;//uchwyty ikon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//uchwyt kursora
	wc.hbrBackground=NULL;//uchwyt pedzla tla
	wc.lpszMenuName=NULL;//nazwa menu
	wc.lpszClassName= nazwaOkna;// nazwa klasy okna

	//Rejestracja klasy okna
	if(RegisterClassEx(&wc)==0) return false;

	//Tworzenie okna
	uchwytOkna = CreateWindow(
		nazwaOkna, //nazwa klasy okna
		nazwaOkna, //nazwa okna
		WS_OVERLAPPEDWINDOW, //styl okna
		polozenieOkna.x,polozenieOkna.y, //polozenie okna(x,y)
		rozmiarOkna.x,rozmiarOkna.y, //rozmiar okna
		NULL,//uchwyt parenta rodzia
		NULL,//uchwyt menu
		uchwytAplikacji, //uchwyt instancji applikacji
		NULL //parametr komunikatu informujacego o utworzeniu okna
		);

	if(uchwytOkna == NULL) return false;//sprawdzenie powodzenia

	//Pokazanie i aktualizacja okna
	ShowWindow(uchwytOkna,SW_SHOW);
	UpdateWindow(uchwytOkna);

	return true;
}

WPARAM COkno::Run()
{
	//Petla glowna - obsluga komunikatow
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

bool COknoGL::UstalFormatPikseli(HDC uchwytDC) const
{
	PIXELFORMATDESCRIPTOR opisFormatuPikseli;
	ZeroMemory(&opisFormatuPikseli,sizeof(opisFormatuPikseli));
	opisFormatuPikseli.nVersion = 1;
	//w oknie, podwojne buforowanie
	opisFormatuPikseli.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	opisFormatuPikseli.iPixelType = PFD_TYPE_RGBA;//typ koloru RGB
	opisFormatuPikseli.cColorBits = 32; //jakosc kolorów 4 bajty
	opisFormatuPikseli.cDepthBits = 16; //z-buffer
	opisFormatuPikseli.iLayerType = PFD_MAIN_PLANE;
	int formatPikseli = ChoosePixelFormat(uchwytDC, &opisFormatuPikseli);
	if (formatPikseli == 0) return false;
	if (!SetPixelFormat(uchwytDC,formatPikseli,&opisFormatuPikseli)) return false;
	return true;
}

bool COknoGL::InitWGL(HWND uchwytOkna)
{
	uchwytDC = ::GetDC(uchwytOkna);
	//Utworzenie kontekstu renderowania i uczynienie go aktywnym
	if(!UstalFormatPikseli(uchwytDC)) return false;
	uchwytRC = wglCreateContext(uchwytDC);
	if(uchwytRC==NULL) return false;
	if(!wglMakeCurrent(uchwytDC,uchwytRC)) return false;//active
	return true;
}

void COknoGL::UsunWGL()
{
	wglMakeCurrent(NULL,NULL); //active-disactive
	wglDeleteContext(uchwytRC);
	::ReleaseDC(uchwytOkna,uchwytDC);
}

LRESULT COknoGL::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long wynik = COkno::WndProc(hWnd,message,wParam,lParam);

	switch(message)
	{
	case WM_CREATE: //utworzenie okna
		InitWGL(hWnd);
		UstawienieSceny(false);
		break;
	case WM_SIZE:
		UstawienieSceny(false);
		break;
	case WM_PAINT:
		RysujScene();
		ValidateRect(hWnd,NULL);
		break;
	case WM_DESTROY:
		UsunWGL();
		break;
	}

	if(kontrolaKameryPrzezUzytkownika)
	{
		switch(message)
		{
		case WM_RBUTTONDOWN:
			poczatkowaPozycjaKursoraMyszy.x = LOWORD(lParam);
			poczatkowaPozycjaKursoraMyszy.y = HIWORD(lParam);
			break;
		case WM_MOUSEMOVE:
			if (wParam & MK_RBUTTON)
			{
				POINT biezacaPozycjaKursoraMyszy = {LOWORD(lParam),HIWORD(lParam)};
				POINT przesuniecieKursoraMyszy=
				{biezacaPozycjaKursoraMyszy.x - poczatkowaPozycjaKursoraMyszy.x,
				biezacaPozycjaKursoraMyszy.y - poczatkowaPozycjaKursoraMyszy.y};

				if(przesuniecieKursoraMyszy.x == 0 && przesuniecieKursoraMyszy.y == 0) break;

				const float czuloscMyszy=5.0f;
				kameraCelPhi += przesuniecieKursoraMyszy.x/czuloscMyszy;
				float zmianaCelTheta = przesuniecieKursoraMyszy.y/czuloscMyszy;
				if(fabs(kameraCelTheta+zmianaCelTheta)<90) kameraCelTheta += zmianaCelTheta;

				poczatkowaPozycjaKursoraMyszy.x = LOWORD(lParam);
				poczatkowaPozycjaKursoraMyszy.y = HIWORD(lParam);
				RysujScene();
			}
			break;
		case WM_KEYDOWN:
			const float przesuniecie=0.1f;
			switch(wParam)
			{
			case VK_OEM_MINUS:
				natezenie_swiatla_tla -= 0.01f;
				if(natezenie_swiatla_tla<0) natezenie_swiatla_tla=0;
				Oswietlenie();
				break;
			case VK_OEM_PLUS:
			case '=':
				natezenie_swiatla_tla += 0.01f;
				if(natezenie_swiatla_tla>1) natezenie_swiatla_tla=1;
				Oswietlenie();
				break;
			case 'W':
			case VK_UP:
				kameraZ += przesuniecie;
				break;
			case 'S':
			case VK_DOWN:
				kameraZ -= przesuniecie;
				break;
			case 'A':
			case VK_LEFT:
				kameraX += przesuniecie;
				break;
			case 'D':
			case VK_RIGHT:
				kameraX -= przesuniecie;
				break;
			case 'C':
				static bool rzutowanieIzometryczne=false;
				rzutowanieIzometryczne = !rzutowanieIzometryczne;
				UstawienieSceny(rzutowanieIzometryczne);
				break;
			}
			RysujScene();
			break;
		}
	}

	return wynik;
}

void COknoGL::UstawienieSceny(bool rzutowanieIzometryczne)
{
	//okno OpenGL - wnetrze formy
	glViewport(0,0,szerokoscObszaruUzytkowania,wysokoscObszaruUzytkowania);

	//ustawienie punktu projekcji
	glMatrixMode(GL_PROJECTION); //przelaczenie na macierz projekcji
	glLoadIdentity();

	//left,right,bottom,top,znear,zfar (clipping)
	float wsp = wysokoscObszaruUzytkowania /(float)szerokoscObszaruUzytkowania;
	if(!rzutowanieIzometryczne)
		//mnozenie macierzy rzutowania przez macierz perspektywy - ustalania frustum
		glFrustum(-0.1,0.1, wsp*-0.1, wsp*0.1, 0.3, 100.0);
	else
		glOrtho(-3,3,wsp*-3,wsp*3,0.3,100.0);
	//glScalef(1,1,-1);
	glMatrixMode(GL_MODELVIEW); //powrot do macierzy widoku modelu
	glEnable(GL_DEPTH_TEST); // z-buffer aktywny = ukrywanie niewidocznych powierzchni
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	Oswietlenie();
}

void COknoGL::UstawienieKamery()
{
	glLoadIdentity();
	glTranslatef(0.0,0.0,-10.0);
	glRotatef(kameraCelPhi,0,1,0);
	glRotatef(kameraCelTheta,cosDf(kameraCelPhi),0,sinDf(kameraCelPhi));

	glTranslatef(kameraX, kameraY, kameraZ);

	//glRotatef(kameraCelPhi,0,1,0);
	//glRotatef(kameraCelTheta,cosDf(kameraCelPhi),0,sinDf(kameraCelPhi));
}

float COknoGL::cosDf(float deg)
{
	deg = deg * M_PI/180.0f;
	return (float)cos(deg);
}

float COknoGL::sinDf(float deg)
{
	deg = deg * M_PI/180.0f;
	return (float)sin(deg);
}

void COknoGL::RysujScene()
{
	const float x0 = 1.0;
	const float y0 = 1.0;
	const float z0 = 1.0;

	//Przygotowanie bufora
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyœci bufory
	//glLoadIdentity(); //macierz model-widok - macierz jednostkowa
	//glTranslatef(0.0,0.0,-10.0);//odsuniecie sceny o 10
	//to zrobi za nas ustawienie kamery
	
	UstawienieKamery();
	RysujAktorow();
	

	/*
	for(int i=0;i<5;i++)
	{
		glTranslatef(0,2,0);
		glBegin(GL_TRIANGLES);
		glVertex3f(-x0,-y0,0);
		glVertex3f(x0,-y0,0);
		glVertex3f(0,y0,0);
		glEnd();

		glTranslatef(0,-2,0);
		glRotatef(72,0,0,1);
	}
	*/
	/*
	for(int i=0;i<5;i++)
	{
		glPushMatrix();
		glRotatef(72.0f*i,0,0,1);
		glTranslatef(0,2,0);

		glBegin(GL_TRIANGLES);
		glVertex3f(-x0,-y0,0);
		glVertex3f(x0,-y0,0);
		glVertex3f(0,y0,0);
		glEnd();

		glPopMatrix();
	}
	*/

	//Z bufora na ekran
	SwapBuffers(uchwytDC);
}

void COknoGL::Oswietlenie()
{
	glEnable(GL_LIGHTING);

	const float kolor_tla[]={
		natezenie_swiatla_tla,
		natezenie_swiatla_tla,
		natezenie_swiatla_tla};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,kolor_tla);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
}