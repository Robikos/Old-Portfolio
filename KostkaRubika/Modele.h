#pragma once
#include "OknoGL.h"
class Modele
{
public:
	static void RysujProstopadloscian(float dx,float dy, float dz, bool koloruj);
	static void RysujSzescian(float dx, bool koloruj);
	static void Niszczyciel(float x0, float y0, float z0);
	static void RysujPodloze(float x0, float y0, float z0);
	static void RysujUklad();
	static void RysujNiebo(float x0, float y0, float z0);
	Modele(void);
	~Modele(void);
};

