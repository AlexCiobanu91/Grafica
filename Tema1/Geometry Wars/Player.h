#pragma once
#include "../Framework/Object2D.h"
#include "../Framework/Circle2D.h"
#include "../Framework/Polygon2D.h"
#include "../Framework/Transform2d.h"
#include <math.h>
#define LEFT  1
#define RIGHT 0

using namespace std;

class Player
{
private:
	float floatRotation;
	float floatSpeedX;
	float floatSpeedY;
	float floatSpeed;
	float floatWeaponSpeed;
	float floatNormalSpeed;
	float floatMaxSpeed;
	bool  boolWeapon;

public:

	float floatCenterX; 
	float floatCenterY; 
	float floatRadius;
	Circle2D*  circle2DShield;
	Polygon2D* polygon2DBody;
	Polygon2D* polygon2DDrill;
	
	Player(Point2D point2DPosition, Color colorPlayerColor);
	~Player() {};

	void rotateBody (float floatSpeed);
	void moveBody (float floatWidth, float floatHeight);
	void scaleBody (float floatScale);
	void activateWeapon();
	void deactivateWeapon();
	void setNormalSpeed(float floatSpeed);
	void setWeaponSpeed(float floatSpeed);
	bool isMovePossible(float floatWidth, float floatHeight);
	bool getWeaponState();
	bool hasColidedShip(float floatCenterX, 
						float flatCenterY, 
						float floatRadius);
	bool hasColidedWeapon(float floatCenterX, 
						  float flatCenterY);
	float getNormalSpeed();
	float getDistance(float floatX, float floatY);
	void setPosition(float floatX, float floatY); 
};