#include "Varia.h"
#include <math.h>


Varia::Varia(void)
{
}


Varia::~Varia(void)
{
}

float* Varia::Roznica3fv(float p1[3], float p2[3], float w[3])
{
	for(int i=0;i<3;i++) w[i] = p1[i]-p2[i];
	return w;
}

float* Varia::IloczynWektorowy3fv(float a[3], float b[3], float w[3])
{
	w[0] = a[1]*b[2] - a[2]*b[1];
	w[1] = -a[2]*b[0] + a[0]*b[2];
	w[2] = a[0]*b[1] - a[1]*b[0];
	return w;
}

float Varia::DlugoscWektora3fv(float w[3])
{
	return sqrt(w[0]*w[0] + w[1]*w[1] + w[2]*w[2]);
}

float* Varia::NormujWektor3fv(float w[3])
{
	float a = DlugoscWektora3fv(w);
	w[0] /= a;
	w[1] /= a;
	w[2] /= a;
	return w;
}

float* Varia::JednostkowyWektorNormalny(float p1[3], float p2[3], float p3[3], float w[3])
{
	float wektor12[3], wektor13[3];
	return NormujWektor3fv(IloczynWektorowy3fv(Roznica3fv(p1,p2,wektor12),Roznica3fv(p1,p3,wektor13),w));
}

unsigned int Varia::StworzCzcionke(bool czyCzcionka3D, HWND uchwytOkna, char* nazwaCzcionki, int
		wysokoscWPikselach, bool Pogrubiona, bool Kursywa, int kodPierwszegoZnaku, int kodOstatniegoZnaku)
{
	unsigned int indeksPierwszejListy = glGenLists(kodOstatniegoZnaku+1-kodPierwszegoZnaku);

	HFONT uchwytCzcionki = CreateFont(
		wysokoscWPikselach,
		0,
		0,
		0,
		Pogrubiona?FW_BOLD:FALSE,
		Kursywa?TRUE:FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE|DEFAULT_PITCH,
		nazwaCzcionki);

	HDC uchwytDC = GetDC(uchwytOkna);
	HFONT uchwytCzcionkiDC = (HFONT)SelectObject(uchwytDC, uchwytCzcionki);
	if(!czyCzcionka3D)
	{
		wglUseFontBitmaps(uchwytDC,kodPierwszegoZnaku,kodOstatniegoZnaku+1-kodPierwszegoZnaku,indeksPierwszejListy);
	}
	else
	{
		wglUseFontOutlines(uchwytDC,kodPierwszegoZnaku,kodOstatniegoZnaku+1-kodPierwszegoZnaku,indeksPierwszejListy,0.0f,0.2f,WGL_FONT_POLYGONS,NULL);
	}

	SelectObject(uchwytDC, uchwytCzcionkiDC);
	DeleteObject(uchwytCzcionki);

	return indeksPierwszejListy;
}

void Varia::Pisz(char* napis, int iloscLiter, unsigned int czcionka, int kodPierwszegoZnaku)
{
	if (napis == NULL || napis == "") return;

	glPushAttrib(GL_LIST_BIT);
	glListBase(czcionka-kodPierwszegoZnaku);
	glCallLists(iloscLiter,GL_UNSIGNED_BYTE,napis);
	glPopAttrib();
}