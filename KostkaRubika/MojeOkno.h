#pragma once
#include "OknoGL.h"
#include "KostkaRubika.h"

class CMojeOknoGL : public COknoGL
{
private:
	float przesuniecie;
	long poprzedniCzas;
	KostkaRubika kostka;
	void RysujTrojkat(float x0, float y0, float z0, float* first, float* second, float* third) const;
	void losujKolory(float* first, float* second, float* third);
public:
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void RysujAktorow();
	void RysujAktorow2();
	void RysujAktorow3(GLuint listyWyswietlania);
	void NapisyMarymontMatrix(unsigned int czcionkaBitmapowa);
	unsigned int TworzListeWyswietlania(float dx, float dy, float dz, bool koloruj) const;
}okno;

COknoGL* p_okno = &okno;