#include "Modele.h"
#include "Varia.h"


Modele::Modele(void)
{
}


Modele::~Modele(void)
{
}

void Modele::RysujProstopadloscian(float dx,float dy, float dz, bool koloruj)
{
	dx /= 2;
	dy /= 2;
	dz /= 2;

	glBegin(GL_QUADS);
	if(koloruj) glColor3f(1.0f,0.0f,0.0f);

	//dolna
	glNormal3f(0,-1,0);
	glVertex3f(-dx,-dy,-dz);
	glVertex3f(dx,-dy,-dz);
	glVertex3f(dx,-dy,dz);
	glVertex3f(-dx,-dy,dz);

	//gorna
	glNormal3f(0,1,0);
	glVertex3f(-dx,dy,dz);
	glVertex3f(dx,dy,dz);
	glVertex3f(dx,dy,-dz);
	glVertex3f(-dx,dy,-dz);

	if(koloruj) glColor3f(0.0f,1.0f,0.0f);
	//left
	glNormal3f(-1,0,0);
	glVertex3f(-dx,-dy,dz);
	glVertex3f(-dx,dy,dz);
	glVertex3f(-dx,dy,-dz);
	glVertex3f(-dx,-dy,-dz);

	//right
	glNormal3f(1,0,0);
	glVertex3f(dx,-dy,-dz);
	glVertex3f(dx,dy,-dz);
	glVertex3f(dx,dy,dz);
	glVertex3f(dx,-dy,dz);
    
	if(koloruj) glColor3f(0.0f, 0.0f, 1.0f);
	//front
	glNormal3f(0,0,1);
	glVertex3f(-dx,-dy,dz);
	glVertex3f(dx,-dy,dz);
	glVertex3f(dx,dy,dz);
	glVertex3f(-dx,dy,dz);

	//back
	glNormal3f(0,0,-1);
	glVertex3f(-dx,-dy,-dz);
	glVertex3f(-dx,dy,-dz);
	glVertex3f(dx,dy,-dz);
	glVertex3f(dx,-dy,-dz);

	glEnd();
}

void Modele::RysujSzescian(float dx, bool koloruj)
{
	RysujProstopadloscian(dx,dx,dx,koloruj);
}

void Modele::Niszczyciel(float x0, float y0, float z0)
{
	float punkt1[3]={0,y0,0};
	float punkt2[3]={-x0,-0.9f*y0,0};
	float punkt3[3]={0,-y0,-0.2f*z0};
	float punkt4[3]={x0,-0.9f*y0,0};
	float punkt5[3]={0,-y0,0.2f*z0};
	float punkt6[3]={-x0,-0.9f*y0,0};

	float normalna[3];

	//kad³ub
	glBegin(GL_TRIANGLE_FAN);
	Varia::JednostkowyWektorNormalny(punkt1,punkt3,punkt2,normalna);
	glNormal3fv(normalna);
	glColor3ub(100,200,50);
	glVertex3fv(punkt1);
	glVertex3fv(punkt2);
	glVertex3fv(punkt3);

	Varia::JednostkowyWektorNormalny(punkt1,punkt4,punkt3,normalna);
	glNormal3fv(normalna);
	glColor3ub(10,20,30);
	glVertex3fv(punkt1);
	glVertex3fv(punkt4);
	glVertex3fv(punkt3);

	Varia::JednostkowyWektorNormalny(punkt1,punkt5,punkt4,normalna);
	glNormal3fv(normalna);
	glColor3ub(150,150,30);
	glVertex3fv(punkt1);
	glVertex3fv(punkt4);
	glVertex3fv(punkt5);

	//CHUJ WIE W TYM MOMENCIE
	glColor3ub(200,210,220);
	glVertex3fv(punkt1);
	glVertex3fv(punkt5);
	glVertex3fv(punkt6);
	glEnd();

	//rufa
	glBegin(GL_TRIANGLE_STRIP);
	glColor3ub(70,70,70);
	glVertex3fv(punkt3);
	glVertex3fv(punkt4);
	glVertex3fv(punkt2);
	glVertex3fv(punkt5);
	glEnd();

	glPushMatrix();

	//nadbudówka
	glTranslatef(0,-0.5f*y0,0.13f*z0);
	RysujProstopadloscian(0.55f*x0,0.55f*y0,0.1f*z0,true);

	//mostek
	glTranslatef(0,-0.29f*y0,0.13f*z0);
	RysujProstopadloscian(0.15f*x0,0.3f*y0,0.25f*z0,true);
	glTranslatef(0,0.1f*y0,0.1f*z0);
	RysujProstopadloscian(0.4f*x0,0.1f*y0,0.1f*z0,true);

	glPopMatrix();
}

void Modele::RysujUklad()
{
	const float x0 = 1.0;
	const float y0 = 1.0;
	const float z0 = 1.0;

	glBegin(GL_LINES);
	glVertex3f(-10*x0,0,0);
	glVertex3f(10*x0,0,0);
	glVertex3f(0,10*y0,0);
	glVertex3f(0,-10*y0,0);
	for(int i=-10;i<=10;i++)
	{
		glVertex3f(i,0.1,0);
		glVertex3f(i,-0.1,0);
		glVertex3f(0.1,i,0);
		glVertex3f(-0.1,i,0);
	}
	glEnd();
}

void Modele::RysujPodloze(float x0, float y0, float z0)
{
	const int nx=10;
	const int nz=10;

	for(int ix=-nx+1;ix<nx;ix++)
	{
		glBegin(GL_QUAD_STRIP);
		for(int iz=-nz+1;iz<nz;iz++)
		{
			glColor3f(0,0.2f,0);
			if( (ix+iz)%2==0) glColor3f(0.2f, 0.3f, 0);
			glVertex3f( (ix)*x0, 3*y0, iz*z0);
			glVertex3f( (ix+1)*x0,3*y0,iz*z0);
		}
		glEnd();
	}
}

void Modele::RysujNiebo(float x0, float y0, float z0)
{
	const int nx=10;
	const int nz=10;

	for(int ix=-nx+1;ix<nx;ix++)
	{
		glBegin(GL_QUAD_STRIP);
		for(int iz=-nz+1;iz<nz;iz++)
		{
			glColor3f(0,0.8f,1);
			if( (ix+iz)%2==0) glColor3f(0, 1, 1);
			glVertex3f( (ix)*x0, 3*y0, iz*z0);
			glVertex3f( (ix+1)*x0,3*y0,iz*z0);
		}
		glEnd();
	}
}