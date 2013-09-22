#pragma once
#include "OknoGL.h"

class Brick
{
public:
	int kolor[3];//kolory w trzech wymiarach
	Brick()
	{
		kolor[0]=kolor[1]=kolor[2]=0;
	}
};//klocek : )

class KostkaRubika
{
public:
	inline void TranslateToColor(int c);
	KostkaRubika(void);
	~KostkaRubika(void);
	bool anim;
	int obrot[3];

	Brick tab[3][3][3];
	Brick* GetBrick(int x, int y, int z);
	void SetBrick(int* w, int kolorX, int kolorY, int kolorZ);
	int* GetNextBrick(int x, int y, int z, int* w);
	void RysujPlaszczyzne(int x,int y,int z);
	void RysujSzescian(float dx, Brick* brick);
	void AktualizujKolory(int x, int y, int z);

	void WymienX(int x, int y, int z);
	void WymienY(int x, int y, int z);
	void WymienZ(int x, int y, int z);

	void animate(int* obrot);
};
