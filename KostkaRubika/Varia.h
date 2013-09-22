#pragma once
#include "OknoGL.h"
class Varia
{
public:
	Varia(void);
	~Varia(void);
	static float* Roznica3fv(float p1[3], float p2[3], float w[3]);
	static float* IloczynWektorowy3fv(float a[3], float b[3], float w[3]);
	static float DlugoscWektora3fv(float w[3]);
	static float* NormujWektor3fv(float w[3]);
	static float* JednostkowyWektorNormalny(float p1[3], float p2[3], float p3[3], float w[3]);
	static unsigned int StworzCzcionke(bool czyCzcionka3D, HWND uchwytOkna, char* nazwaCzcionki, int
		wysokoscWPikselach, bool Pogrubiona, bool Kursywa, int kodPierwszegoZnaku, int kodOstatniegoZnaku);
	static void Pisz(char* napis, int iloscLiter, unsigned int czcionka, int kodPierwszegoZnaku);
};

