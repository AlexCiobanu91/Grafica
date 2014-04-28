#include "Enemy.h"
#include "dependente\freeglut.h"
#include <math.h>
#include <time.h>
Enemy::Enemy()
{
	_carPositionX = 0;
	_carPositionY = 0;
	_carPositionZ = 0;
	_moveSpeed    = 0;
	_carNumber    = 0;
	_carDirection = 0;
};

Enemy::~Enemy(void)
{

}

Enemy::Enemy(float carPositionX, float carPositionY, float carPositionZ,
			 float moveSpeed, int carDirection, int carNumber)
{
	_carPositionX = carPositionX;
	_carPositionY = carPositionY;
	_carPositionZ = carPositionZ;
	_moveSpeed    = moveSpeed;
	_carNumber    = carNumber;
	_carDirection = carDirection;
	_radius = 2;
}

// deplaseaza inamicul in directia stabilita in constructor
void Enemy::move()
{
	if (_carDirection == 0) {
		_carPositionZ -= _moveSpeed;
	} else {
		_carPositionZ += _moveSpeed;
	}
}


// afiseaza pe ecran inamicul sau bonusul
// in functie de numarul acestuia din constructor
void Enemy::render()
{
	glPushMatrix();
	glTranslatef(_carPositionX , _carPositionY, _carPositionZ);
	switch(_carNumber) {
		case 0: 
			// daca inamicul este o masina si este pe o banda stanga o rotim
			// cu 180 de grade astfel ca fata ei sa fie indreptaa spre jucator
			if (_carDirection == 1) {
				glRotatef(180,0,1,0);
			}
			createCar(); 
		break;

		case 1: 
			createSphere(); 
		break;

		case 2: 
			createCube();
		break;

		case 3: 
			createTorus();
		break;

		case 4: 
			// se afiseaza bonusul, acesta va avea o culoarea diferita la fiecare
			// instantiere
			srand(time(NULL));
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			glColor3f(r, g, b);
			createBonus();
		break;
	}
	glPopMatrix();
}

// intoarce distanta fata de un punct situat 
// pe axa Oz la pozitia positionZ
float Enemy::getDistance(float positionZ)
{
	return _carPositionZ - positionZ;
}

//verifica daca inamicul se afla in fata masinii jucatorului
// folosita pentru afisarea inamicului doar cand acesta se afla 
// in fata jucatorului
bool Enemy::isInFront(float positionZ, float fieldOfView)
{
	float distance = _carPositionZ - positionZ ;
	return (distance < 0) && (fabs(distance) < fieldOfView);
}

void Enemy::createSphere()
{
	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslatef(1.0f ,1, 0.0f);
	glutWireSphere(1, 10, 10);
	glPopMatrix();
}

void Enemy::createCube()
{
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(1.0f, 1, 0.0f);
	glutSolidCube(3);
	glPopMatrix();
}

void Enemy::createTorus()
{
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(1.0f, 1.2, 0.0f);
	glutWireTorus(0.5,1,20,20);
	glPopMatrix();
}

void Enemy::createTeapot()
{
	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(1.0f ,1, 0.0f);
	glutWireTeapot(1);
	glPopMatrix();
}

void Enemy::createBonus()
{
	
	glPushMatrix();
	glTranslatef(1.0f, 1, 0.0f);
	glutSolidCube(1);
	glPopMatrix();
	_radius = 4;
}

// functie ce creeaza o masina
void Enemy::createCar()
{
	glPushMatrix();
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutWireSphere(0.2, 10, 10);
	glPopMatrix();

	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslatef(1.0f ,0.75f, 0.0f);
	glutWireSphere(0.2, 10, 10);
	glPopMatrix();

	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(1.0f ,0.75f, -2.0f);
	glutWireSphere(0.2, 10, 10);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0.75f, -2.0f);
	glutWireSphere(0.2, 10, 10);
	glPopMatrix();

	// corp 
	glColor3f(0.000, 0.392, 0.000);
	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	glBegin(GL_QUADS);
		glVertex3f(0,    0,  0);
		glVertex3f(1, 0,    0);
		glVertex3f(1, 0,    -2);
		glVertex3f(0,    0, -2);
	glEnd();
	glPopMatrix();


	glColor3f(0.000, 0.392, 0.000);
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glBegin(GL_QUADS);
		glVertex3f(0,    0,  0);
		glVertex3f(1, 0,    0);
		glVertex3f(1, 0,    -2);
		glVertex3f(0,    0, -2);
	glEnd();
	glPopMatrix();
	
	glColor3f(0.000, 0.392, 0.000);
	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	glBegin(GL_QUADS);
		glVertex3f(0, 0,  0);
		glVertex3f(0, 0,  -2);
		glVertex3f(0, 0.25,  -2);
		glVertex3f(0, 0.25, 0);
	glEnd();
	glPopMatrix();


	glColor3f(0.000, 0.392, 0.000);
	glPushMatrix();
	glTranslatef(1, 0.75, 0);
	glBegin(GL_QUADS);
		glVertex3f(0, 0,  0);
		glVertex3f(0, 0,  -2);
		glVertex3f(0, 0.25,  -2);
		glVertex3f(0, 0.25, 0);
	glEnd();
	glPopMatrix();

	glColor3f(0.000, 0.38, 0.000);
	glPushMatrix();
	glTranslatef(1, 0.75, 0);
	glBegin(GL_QUADS);
		glVertex3f(0, 0,  0);
		glVertex3f(0, 0,  -2);
		glVertex3f(0, 0.25,  -2);
		glVertex3f(0, 0.25, 0);
	glEnd();
	glPopMatrix();


	glColor3f(0.000, 0.392, 0.000);
	glPushMatrix();
	glTranslatef(0.5, 1.5, -0.5);
	glutSolidCube(1);
	glPopMatrix();


	glColor3f(0.000, 0, 0);
	glPushMatrix();
	glTranslatef(0, 1, -2);
	glBegin(GL_QUADS);
		glVertex3f(0, 0,  0);
		glVertex3f(1, 0,  0);
		glVertex3f(1, 1,  1);
		glVertex3f(0, 1,  1);
	glEnd();
	glPopMatrix();
}

float Enemy::getRadius()
{
	return _radius;
}

float Enemy::getPositionX()
{
	return _carPositionX;
}

float Enemy::getPositionZ()
{
	return _carPositionZ;
}

int Enemy::getNumber()
{
	return _carNumber;
}

void Enemy::setPositionZ(float positionZ)
{
	_carPositionZ = positionZ;
}