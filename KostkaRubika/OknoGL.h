#pragma once
#include <windows.h>
#include <gl/gl.h>

class COkno
{
protected:
	long szerokoscObszaruUzytkowania, wysokoscObszaruUzytkowania;
public:
	virtual LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool Init(HINSTANCE uchwytAplikacji, POINT polozenieOkna, POINT rozmiarOkna);
	HWND uchwytOkna;
	WPARAM Run();
};

class COknoGL : public COkno
{
protected:
	bool kontrolaKameryPrzezUzytkownika;
private:
	HGLRC uchwytRC; //uchwut kontekstu renderingu
	HDC uchwytDC; //uchwyt prywatnego kontekstu urzadzenia GDI
	POINT poczatkowaPozycjaKursoraMyszy;
	float kameraCelPhi, kameraCelTheta;
	float kameraX, kameraY, kameraZ;
	float sinDf(float deg);
	float cosDf(float deg);
public:
	COknoGL():COkno(),uchwytRC(NULL),uchwytDC(NULL),
	kontrolaKameryPrzezUzytkownika(true),
	poczatkowaPozycjaKursoraMyszy(POINT()),
	kameraCelPhi(0),kameraCelTheta(0),
	kameraX(0),kameraY(0),kameraZ(0),
	natezenie_swiatla_tla(1.0f){};

	virtual LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool UstalFormatPikseli(HDC uchwytDC) const;
	bool InitWGL(HWND uchwytOkna);
	void UsunWGL();
	void UstawienieSceny(bool rzutowanieIzometryczne); //domyslnie false
	void RysujScene();
	void UstawienieKamery();
	void Oswietlenie();

	virtual void RysujAktorow() = 0;

	float natezenie_swiatla_tla;
};