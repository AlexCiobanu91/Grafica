#pragma once
#include "../Framework/Object2D.h"
#include "../Framework/Circle2D.h"
#include "../Framework/Polygon2D.h"
#include "../Framework/Transform2d.h"
#include <math.h>
#define LEFT  1
#define RIGHT 0

using namespace std;

class Enemy
{
private:
	float floatRotationAngle;
	float floatRotation;
	float floatSpeedX;
	float floatSpeedY;
	float floatSpeed;
	int   intEnemyNo;

	Polygon2D* polygon2DTemp;
	Circle2D*  circle2DTemp;
	Point2D	   point2DTemp;

public:
	float floatCenterX; 
	float floatCenterY; 
	float floatRadius;
	bool  boolPlayerCollision;
	vector<Object2D*> object2DComponents;
	
	Enemy(Point2D point2DPosition);
	~Enemy() {};

	void rotateBody ();
	void moveBody(float floatWidth, float floatHeight);
	void translateBody(float floatWidth, float floatHeight);
	void scaleBody(float floatScale);
	void checkMargins(float floatWidth, float floatHeight);
	void createEnemy(int intNumEnemy);
	void setSpeed(float floatSpeed1, float floatSpeed2);
	void setRotation(float floatAngle);
	void changeDirection();
	bool hasColidedShip(float floatEnemyX, float floatEnemyY, 
						float floatRadius);
	int  getEnemyNo();
};