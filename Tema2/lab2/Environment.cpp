#include "Environment.h"
#include "dependente\freeglut.h"
#include "math.h"

Environment::Environment(void)
{
}

Environment::~Environment(void)
{
}


Environment::Environment(unsigned int gl_program_shader, float levelDistance, float minPositionX, float maxPositionX)
{
	_levelDistance = levelDistance;
	_minPositionX  = minPositionX;
	_maxPositionX  = minPositionX;
	_glProgramShader = gl_program_shader;
}

float Environment::getMinPositionX()
{
	return _minPositionX;
}

float Environment::getMaxPositionX()
{
	return _maxPositionX;
}


// creeza blocurile dein peisajul jocului cu o culoare 
// din spectrul culorii gri
void Environment::createBloc() 
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r < 0.1) { 
		r += 0.2;
	}
	if (r > 0.9) { 
		r -= 0.2;
	}
	float g = r;
	float b = g;
	glColor3f(r, g, b);
	glBegin(GL_QUADS);

		glVertex3f(0, 0, 0);
		glVertex3f(5, 0, 0);
		glVertex3f(5, 0, 7);
		glVertex3f(0, 0, 7);

		glVertex3f(0, 10,    0);
		glVertex3f(5, 10,    0);
		glVertex3f(5, 10,    7);
		glVertex3f(0, 10,    7);

		glVertex3f(5, 0,    0);
		glVertex3f(5, 0,    7);
		glVertex3f(5, 10,   7);
		glVertex3f(5, 10,   0);

		glVertex3f(0, 0,    0);
		glVertex3f(5, 0,    0);
		glVertex3f(5, 10,   0);
		glVertex3f(0, 10,   0);

		glVertex3f(0, 0,    0);
		glVertex3f(0, 0,    7);
		glVertex3f(0, 10,   7);
		glVertex3f(0, 10,   0);


	glEnd();
}


// afiseaza blocurile in peisaj
// acestea se afiseaza doar cand jucatorul se afla la o anumita 
// distanta de ele
void Environment::renderEnvironment(float startZ)
{
	float crtPositionZ = startZ;

	if (fabs(startZ - _lastPositionZ) > 400) {
		_lastPositionZ = startZ;
		for (int i = 0; i < 120 ; i++) {
			srand(i * 1000);
			glPushMatrix();
			glTranslatef(-15 - i % 2, -0.5f, startZ - i * 7.5);
			createBloc();
			glPopMatrix();
		}

		for (int i = 0; i < 120;  i++) {
			srand(i * 600);
			glPushMatrix();
			glTranslatef(21 + i % 2, -0.5f, startZ - i * 7.5);
			createBloc();
			glPopMatrix();
		}
	} else {
		for (int i = 0; i < 120 ; i++) {
			srand(i * 1000);
			glPushMatrix();
			glTranslatef(-15 - i % 2, -0.5f, _lastPositionZ - i * 7.5);
			createBloc();
			glPopMatrix();
		}

		for (int i = 0; i < 120;  i++) {
			srand(i * 600);
			glPushMatrix();
			glTranslatef(21 + i % 2, -0.5f, _lastPositionZ - i * 7.5);
			createBloc();
			glPopMatrix();
		}
	}
}

// creeaza o linie intrerupa ce va fi afisata pe mijlocul
// unei strazi
void Environment::linieIntrerupta()
{
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glVertex3f(0,    0.01f,    0);
		glVertex3f(0.2f, 0.01f,    0);
		glVertex3f(0.2f, 0.01f,    -2.0f);
		glVertex3f(0,    0.01f,    -2.0f);
	glEnd();
}

// creeaza o secventa de linii intrerupte 
// pozitionate la coordonata pe X : positionX
void Environment::genLinieIntrerupta(float positionX) {
	for (int i = 0 ; i < _levelDistance / 5; i ++) {
		glPushMatrix();
		glTranslatef(positionX, 0.01f , - 5 * i);
			linieIntrerupta();
		glPopMatrix();
	}
}

// creeaza llinia despartitioare intre strazi
void Environment::createPavement() 
{
	glColor3f(0.184, 0.310, 0.310);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 0.01F,      0.0f);
		glVertex3f(0.5F, 0.01F,   0.0f);
		glVertex3f(0.5F, 0.01F,  -_levelDistance);
		glVertex3f(0.0f, 0.01F,  -_levelDistance);
	glEnd();
}

// creeaza un drum
void Environment::createARoad() 
{  
	GLint yloc = glGetAttribLocation(prog, "y");
	glBegin(GL_POLYGON);
	glVertexAttrib1d(yloc, 0.0); glColor3d(1.0, 0.0, 0.0); glVertex3d(+2, -1, +0);
	glVertexAttrib1d(yloc, 0.0); glColor3d(0.0, 0.0, 1.0); glVertex3d(+0, -1, +2);
	glVertexAttrib1d(yloc, 1.0); glColor3d(0.0, 1.0, 0.0); glVertex3d(+0, +1, +0);
	glEnd();
	glColor3f(0.502, 0.502, 0.502);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 0.0f,   0.0f);
		glVertex3f(10, 0.0f,  0.0f);
		glVertex3f(10, 0.0f, -_levelDistance);
		glVertex3f(0, 0.0f,  -_levelDistance);
	glEnd();
}

// creeaza cele 3 drumui cu liniile de pe mijloc
// si liniile despartitoare
void Environment::renderRoads(int nrRoads) 
{
	for (int i = 0; i < nrRoads; i ++) {
		glPushMatrix();
		glTranslatef(0 + i * 10, 0.0f ,0.0f);
		createARoad();
		glPopMatrix();
	}

	for (int i = 0; i <= nrRoads; i ++) {
		glPushMatrix();
		glTranslatef(i * 10, 0.0f ,0.0f);
		createPavement();
		glPopMatrix();
	}
}
