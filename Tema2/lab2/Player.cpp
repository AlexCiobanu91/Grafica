#include "Player.h"
#include "dependente\freeglut.h"
#include <iostream>
using namespace std;
Player::Player(void)
{
	_minPositionX  = 0;
	_maxPositionX  = 0;
	_carPositionX = 0;
	_carPositionY = 0;
	_carPositionZ = 0;
	_moveSpeed    = 0;
	_accelerate   = 0;
	_decelerate   = 0;
	_tilt         = 0;
	_rotateLeft   = false;
	_rotateRight  = false;
	_moveCar      = false;
}

// constructorul clasei ce initiallizeaza principalele caracteristici ale
// jucatorului
Player::Player(float carPositionX, float carPositionY, float carPositionZ,
		   float maxSpeed, float minPositionX, float maxPositionX)
{
	_carPositionX = carPositionX;
	_carPositionY = carPositionY;
	_carPositionZ = carPositionZ;
	_maxSpeed     = maxSpeed;
	_moveSpeed    = 0;
	_accelerate   = 0;
	_decelerate   = 0;
	_tilt         = 0;
	_radius       = 10;
	_minPositionX  = minPositionX;
	_maxPositionX  = maxPositionX;

	_rotateLeft   = false;
	_rotateRight  = false;
	_moveCar      = false;
	_break        = false;
}

Player::~Player(void)
{

}

// functie de mutare a masinii daca variabial _moveCar este true
// altfel masina se va opri din inertie
// la apasarea tastei "Down" masina va frana
void Player::moveCar() 
{
	if (_moveCar) {
		_decelerate = 0;
		// in urma unui bonus viteza va scadea pana la 
		// valoarea maxima admisa
		if (_moveSpeed < _maxSpeed) {
			_accelerate  += 0.001;
			_moveSpeed   += _accelerate;
		} else {
			_accelerate = 0;
			_moveSpeed -= 0.06;
		}
	} else if (_break) {
		_accelerate = 0;
		_decelerate -= 0.06;
		_moveSpeed += _decelerate;
		if (_moveSpeed < 0) {
			_moveSpeed = 0;
		}
	} else {
		_accelerate = 0;
		_decelerate = 0;
		_moveSpeed -= 0.06;
		if (_moveSpeed < 0) {
			_moveSpeed = 0;
		}
	}
	_carPositionZ -= _moveSpeed;
}

// afiseaza pe ecran masina si rotirile acesteia
// in functie de tastele apasate
void Player::render() 
{
	glPushMatrix();
	glTranslatef(_carPositionX , _carPositionY, _carPositionZ);
	if (_rotateLeft) {
		glRotatef(+45, 0, 1, 0);
	}
	if (_rotateRight) {
		glRotatef(-45, 0, 1, 0);
	}
	drawCar();
	glPopMatrix();

}

// functia de desenare a masinii
void Player::drawCar() {

	glColor3f(1.0f, 0, 0);

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

void Player::enableMove()
{
	_moveCar = true;
	_break = false;
}

void Player::disableMove()
{
	_moveCar = false;
	_decelerate = false;
}

// la apasarea tastelor left sau right masina
// se va roti in directia corespunzatoare si va
// schimba banda
bool Player::setRotate(int direction)
{
	if (direction == 0) {
		_rotateLeft = true;
		if (_carPositionX > _minPositionX) {
			_carPositionX -= 5;
			return true;
		}
	} else {
		_rotateRight = true;
		if (_carPositionX < _maxPositionX) {
			_carPositionX += 5;
			return true;
		}
	}
	return false;
}

void Player::disableRotate() 
{
	_rotateLeft  = false;
	_rotateRight = false;
}

float Player::getSpeed()
{
	return _moveSpeed;
}

float Player::getPositionZ()
{
	return _carPositionZ;
}

bool Player::isMoveEnabled()
{
	return _moveCar;
}

float Player::getPositionY()
{
	return _carPositionY;
}

float Player::getPositionX()
{
	return _carPositionX;
}

void Player::setTilt(float tilt)
{
	_tilt += tilt;
}

// verifica daca masina si inamicul se afla pe aceeasi banda
bool Player::onSameLane(float positionX)
{
	return fabs(_carPositionX - positionX) < 4;
}

// verifica coliziunea intre masina si un obstacol
// aceasta se face prin verificarea daca sunt pe aceeasi
// banda si daca distanta dintre ele este mai mica
// decat raza cercului virtual de colizune
bool Player::checkForColision(float posZ, float pozX, float radius)
{
	float distance = fabs(_carPositionZ - posZ);
	return onSameLane(pozX) && distance < _radius + radius;
}

void Player::setMaxSpeed(float maxSpeed)
{
	_maxSpeed = maxSpeed;
}

void Player::setPositionZ(float positionZ)
{
	_carPositionZ = positionZ;
}

void Player::setPositionX(float positionX)
{
	_carPositionX = positionX;
}

void Player::decelerate() 
{
	_break = true;
}