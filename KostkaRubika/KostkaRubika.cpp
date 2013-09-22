#include "KostkaRubika.h"


KostkaRubika::KostkaRubika(void)
{
	anim = false;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{ 
			tab[0][i][j].kolor[0]=1;
			tab[2][i][j].kolor[0]=2;
			tab[i][0][j].kolor[1]=3;
			tab[i][2][j].kolor[1]=4;
			tab[i][j][0].kolor[2]=5;
			tab[i][j][2].kolor[2]=6;
		}
}


KostkaRubika::~KostkaRubika(void)
{
}

void KostkaRubika::TranslateToColor(int c)
{
	switch(c)
	{
	case 0:
		glColor3ub(0,0,0);
		//czarny - puste pole
		break;
	case 1:
		glColor3ub(7,205,22);
		//zielony
		break;
	case 2:
		glColor3ub(255,255,0);
		//zolty
		break;
	case 3:
		glColor3ub(255,255,255);
		//bialy
		break;
	case 4:
		glColor3ub(0,128,192);
		//niebieski
		break;
	case 5:
		glColor3ub(255,0,0);
		//czerwony
		break;
	case 6:
		glColor3ub(255,127,39);
		//pomaranczowy
		break;
	}
}

Brick* KostkaRubika::GetBrick(int x,int y, int z)
{
	return &tab[x+1][y+1][z+1];
}

int* KostkaRubika::GetNextBrick(int x, int y, int z, int* w)
{//xyz obrot
	int v[3] = {w[0],w[1],w[2]};
	if(x<2)
	{
		w[1] = -v[2];
		w[2] = v[1];
	}
	else if(y<2)
	{
		w[0] = -v[2];
		w[2] = v[0];
	}
	else if(z<2)
	{
		w[0] = -v[1];
		w[1] = v[0];
	}

	return w;
}



void KostkaRubika::SetBrick(int* w, int kolorX, int kolorY, int kolorZ)
{
	GetBrick(w[0],w[1],w[2])->kolor[0] = kolorX;
	GetBrick(w[0],w[1],w[2])->kolor[1] = kolorY;
	GetBrick(w[0],w[1],w[2])->kolor[2] = kolorZ;
}

void KostkaRubika::RysujPlaszczyzne(int x,int y,int z)//,int angle
{
	//ewentualny obrot
	if(x<2)
	{
		for(int j=-1;j<=1;j++)
			for(int k=-1;k<=1;k++)
			{
				glPushMatrix();
				glTranslatef(x/2.0f,j/2.0f,k/2.0f);
				RysujSzescian(0.5,GetBrick(x,j,k));
				glPopMatrix();
			}
	}
	else if(y<2)
	{
		for(int j=-1;j<=1;j++)
			for(int k=-1;k<=1;k++)
			{
				glPushMatrix();
				glTranslatef(j/2.0f,y/2.0f,k/2.0f);
				RysujSzescian(0.5,GetBrick(j,y,k));
				glPopMatrix();
			}
	}
	else if(z<2)
	{
		for(int j=-1;j<=1;j++)
			for(int k=-1;k<=1;k++)
			{
				glPushMatrix();
				glTranslatef(j/2.0f,k/2.0f,z/2.0f);
				RysujSzescian(0.5,GetBrick(j,k,z));
				glPopMatrix();
			}
	}
}
//push -> rotate -> plaszczyzna -> pop -> pozostale plaszczyzny

void KostkaRubika::AktualizujKolory(int x, int y, int z)
{
	
	if(x<2)
	{
		WymienX(x,-1,-1);
		WymienX(x,-1,0);
	}
	else if(y<2)
	{
		WymienY(-1,y,-1);
		WymienY(-1,y,0);
	}
	else if(z<2)
	{
		WymienZ(-1,-1,z);
		WymienZ(-1,0,z);
	}
}

void KostkaRubika::WymienX(int x, int y, int z)
{
	int temp[3]={0};
	int p[3],n[3];
	p[0]=n[0]=x;
	p[1]=n[1]=y;
	p[2]=n[2]=z;
		temp[0] = GetBrick(x,y,z)->kolor[0];
		temp[1] = GetBrick(x,y,z)->kolor[1];
		temp[2] = GetBrick(x,y,z)->kolor[2]; // temp 1kolor
		for(int i=0;i<3;i++){
			GetNextBrick(x,3,3,n);
		SetBrick(p,GetBrick(n[0],n[1],n[2])->kolor[0],
			GetBrick(n[0],n[1],n[2])->kolor[2],
			GetBrick(n[0],n[1],n[2])->kolor[1]);
			p[0] = n[0];
			p[1] = n[1];
			p[2] = n[2];
		}
		GetNextBrick(x,3,3,n);
		SetBrick(p,temp[0],
			temp[2],
			temp[1]);
}

void KostkaRubika::WymienY(int x, int y, int z)
{
	int temp[3]={0};
	int p[3],n[3];
	p[0]=n[0]=x;
	p[1]=n[1]=y;
	p[2]=n[2]=z;
		temp[0] = GetBrick(x,y,z)->kolor[0];
		temp[1] = GetBrick(x,y,z)->kolor[1];
		temp[2] = GetBrick(x,y,z)->kolor[2]; // temp 1kolor
		for(int i=0;i<3;i++){
			GetNextBrick(3,y,3,n);
		SetBrick(p,GetBrick(n[0],n[1],n[2])->kolor[2],
			GetBrick(n[0],n[1],n[2])->kolor[1],
			GetBrick(n[0],n[1],n[2])->kolor[0]);
			p[0] = n[0];
			p[1] = n[1];
			p[2] = n[2];
		}
		GetNextBrick(3,y,3,n);
		SetBrick(p,temp[2],
			temp[1],
			temp[0]);
}

void KostkaRubika::WymienZ(int x, int y, int z)
{
	int temp[3]={0};
	int p[3],n[3];
	p[0]=n[0]=x;
	p[1]=n[1]=y;
	p[2]=n[2]=z;
		temp[0] = GetBrick(x,y,z)->kolor[0];
		temp[1] = GetBrick(x,y,z)->kolor[1];
		temp[2] = GetBrick(x,y,z)->kolor[2]; // temp 1kolor
		for(int i=0;i<3;i++){
			GetNextBrick(3,3,z,n);
		SetBrick(p,GetBrick(n[0],n[1],n[2])->kolor[1],
			GetBrick(n[0],n[1],n[2])->kolor[0],
			GetBrick(n[0],n[1],n[2])->kolor[2]);
			p[0] = n[0];
			p[1] = n[1];
			p[2] = n[2];
		}
		GetNextBrick(3,3,z,n);
		SetBrick(p,temp[1],
			temp[0],
			temp[2]);
}

void KostkaRubika::RysujSzescian(float dx, Brick* brick)
{
	dx -= 0.01;
	dx /= 2;

	glBegin(GL_QUADS);

	TranslateToColor(brick->kolor[1]);
	//dolna
	glNormal3f(0,-1,0);
	glVertex3f(-dx,-dx,-dx);
	glVertex3f(dx,-dx,-dx);
	glVertex3f(dx,-dx,dx);
	glVertex3f(-dx,-dx,dx);

	//gorna
	glNormal3f(0,1,0);
	glVertex3f(-dx,dx,dx);
	glVertex3f(dx,dx,dx);
	glVertex3f(dx,dx,-dx);
	glVertex3f(-dx,dx,-dx);

	TranslateToColor(brick->kolor[0]);
	//left
	glNormal3f(-1,0,0);
	glVertex3f(-dx,-dx,dx);
	glVertex3f(-dx,dx,dx);
	glVertex3f(-dx,dx,-dx);
	glVertex3f(-dx,-dx,-dx);

	//right
	glNormal3f(1,0,0);
	glVertex3f(dx,-dx,-dx);
	glVertex3f(dx,dx,-dx);
	glVertex3f(dx,dx,dx);
	glVertex3f(dx,-dx,dx);
    
	TranslateToColor(brick->kolor[2]);
	//front
	glNormal3f(0,0,1);
	glVertex3f(-dx,-dx,dx);
	glVertex3f(dx,-dx,dx);
	glVertex3f(dx,dx,dx);
	glVertex3f(-dx,dx,dx);

	//back
	glNormal3f(0,0,-1);
	glVertex3f(-dx,-dx,-dx);
	glVertex3f(-dx,dx,-dx);
	glVertex3f(dx,dx,-dx);
	glVertex3f(dx,-dx,-dx);

	glEnd();
}

void KostkaRubika::animate(int* obrot)
{
	static float angle=0.0f;
	if(anim)
	{
		angle += 1.5f;
		if(angle > 90)
		{
			anim = false;
			angle = 0.0f;
			AktualizujKolory(obrot[0],obrot[1],obrot[2]);
		}
		if(obrot[0]<2)
		{
			for(int i=-1;i<obrot[0];i++) RysujPlaszczyzne(i,3,3);
			glPushMatrix();
			glRotatef(-angle,1,0,0);
			RysujPlaszczyzne(obrot[0],3,3);
			glPopMatrix();
			for(int i=obrot[0]+1;i<2;i++) RysujPlaszczyzne(i,3,3);
		}
		else if(obrot[1]<2)
		{
			for(int i=-1;i<obrot[1];i++) RysujPlaszczyzne(3,i,3);
			glPushMatrix();
			glRotatef(angle,0,1,0);
			RysujPlaszczyzne(3,obrot[1],3);
			glPopMatrix();
			for(int i=obrot[1]+1;i<2;i++) RysujPlaszczyzne(3,i,3);
		}
		else if(obrot[2]<2)
		{
			for(int i=-1;i<obrot[2];i++) RysujPlaszczyzne(3,3,i);
			glPushMatrix();
			glRotatef(angle,0,0,1);
			RysujPlaszczyzne(3,3,obrot[2]);
			glPopMatrix();
			for(int i=obrot[2]+1;i<2;i++) RysujPlaszczyzne(3,3,i);
		}

	}
	else
	{
		RysujPlaszczyzne(-1,3,3);
		RysujPlaszczyzne(0,3,3);
		RysujPlaszczyzne(1,3,3);
	}
}