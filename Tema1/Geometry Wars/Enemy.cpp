//implementarea clasei Transform2D - trebuie sa fie treaba studentilor

#include "Enemy.h"
#include "math.h"
#include <time.h>
using namespace std;


Enemy::Enemy(Point2D point2DPosition)
{
	floatCenterX = point2DPosition.x;
	floatCenterY = point2DPosition.y;
	floatRotation = 0;
	floatRotationAngle = 0;;
	floatSpeedX = 0;
	floatSpeedY = 0;
	floatRadius = 0;
	boolPlayerCollision = false;
	intEnemyNo = rand() % 6;
	createEnemy(intEnemyNo);
}

// roteste figura geometrica cu numarul primit ca parametru
void Enemy::rotateBody()
{ 	
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(-floatCenterX, -floatCenterY);
	Transform2D::rotateMatrix(floatRotationAngle);
	Transform2D::translateMatrix(floatCenterX,   floatCenterY);

	for (unsigned int i = 0; i < object2DComponents.size();i++) {
		Transform2D::applyTransform_o(object2DComponents[i]);
	}

	floatRotation += floatRotationAngle;
}

// translateaza figura geometrica
void Enemy::moveBody(float floatWidth, float floatHeight)
{
	checkMargins(floatWidth, floatHeight);

	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(floatSpeedX, floatSpeedY);
	for (unsigned int i = 0; i < object2DComponents.size(); i++) {
		Transform2D::applyTransform_o(object2DComponents[i]);
	}
	floatCenterX += floatSpeedX;
	floatCenterY += floatSpeedY;
}

// schimba directia de mers in momentul in care tinde sa iasa din cran
void Enemy::checkMargins(float floatWidth, float floatHeight) 
{
	if (floatCenterX + floatSpeedX + 20 > floatWidth ||
		floatCenterX + floatSpeedX - 20 < 0) {
		floatSpeedX = -floatSpeedX;
	}

	if (floatCenterY + floatSpeedY + 20 >= floatHeight ||
		floatCenterY + floatSpeedY - 20 < 0) {
			floatSpeedY = -floatSpeedY;
	}	
}

// scaleaza figura geometrica
void Enemy::scaleBody(float floatScale) 
{
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(-floatCenterX, -floatCenterY);
	Transform2D::scaleMatrix(floatScale, floatScale);
	Transform2D::translateMatrix(floatCenterX, floatCenterY);
	for (unsigned int i = 0; i < object2DComponents.size(); i++) {
		Transform2D::applyTransform_o(object2DComponents[i]);
	}
	floatRadius *= floatScale;
}

// creaza o figura geometrica in functie de numarul acesteia
void Enemy::createEnemy(int intNumEnemy)
{
	switch (intNumEnemy) {
		case 0:

				// 1st triangle
				polygon2DTemp = new Polygon2D(Color(1,0,0), true);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX - 20, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				object2DComponents.push_back(polygon2DTemp);

				//2nd triangle
				polygon2DTemp = new Polygon2D(Color(0,1,0), true);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX + 20, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				object2DComponents.push_back(polygon2DTemp);

				//3rd triangle
				polygon2DTemp = new Polygon2D(Color(0,0,1), true);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX + 20, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX + 20, floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				object2DComponents.push_back(polygon2DTemp);

				//4th triangle
				polygon2DTemp = new Polygon2D(Color(1,0,1), true);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20, floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				object2DComponents.push_back(polygon2DTemp);
				floatRadius = 20;
		break;
		case 1:
				//1th romb
				polygon2DTemp = new Polygon2D(Color(1, 0, 1), true);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX + 20 , floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX , floatCenterY - 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20 , floatCenterY - 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);
				object2DComponents.push_back(polygon2DTemp);

				//2th romb
				polygon2DTemp = new Polygon2D(Color(1,0,0), true);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX + 20 , floatCenterY - 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX , floatCenterY - 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20 , floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);
				object2DComponents.push_back(polygon2DTemp);

				//1st patrat
				polygon2DTemp = new Polygon2D(Color(1,1,0), false);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX + 20, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX + 20, floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20, floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				object2DComponents.push_back(polygon2DTemp);
				floatRadius = 20;
		break;
		case 2:
				//1st patrat
				polygon2DTemp = new Polygon2D(Color(1,0,0.5), true);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 10, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX + 10, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX + 10, floatCenterY - 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 10, floatCenterY - 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 10, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);

				object2DComponents.push_back(polygon2DTemp);

				//2nd cerc
				circle2DTemp = new Circle2D(Point2D(floatCenterX, floatCenterY), 
											20, Color(0, 0, 1), true);

				object2DComponents.push_back(circle2DTemp);
				floatRadius = 20;

		break;
		case 3:
			//1th romb
				polygon2DTemp = new Polygon2D(Color(0.5, 0, 0.5), true);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX + 40 , floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX , floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 40 , floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);
				object2DComponents.push_back(polygon2DTemp);
				floatRadius = 20;
		break;
		case 4:
			//1th romb

				polygon2DTemp = new Polygon2D(Color(1, 1, 0.5), true);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX + 40 , floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX , floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 40 , floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);
				object2DComponents.push_back(polygon2DTemp);
				circle2DTemp = new Circle2D(Point2D(floatCenterX, floatCenterY), 
											20, Color(1, 0, 1), true);

				object2DComponents.push_back(circle2DTemp);
				floatRadius = 20;
		break;
		case 5:
				polygon2DTemp = new Polygon2D(Color(0, 1, 0.5), true);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX + 20 , floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX , floatCenterY - 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20 , floatCenterY - 10);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX, floatCenterY + 10);
				polygon2DTemp->addPoint(point2DTemp);
				object2DComponents.push_back(polygon2DTemp);

				polygon2DTemp = new Polygon2D(Color(0,0,1), true);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX - 20, floatCenterY - 20);
				polygon2DTemp->addPoint(point2DTemp);

				object2DComponents.push_back(polygon2DTemp);

				polygon2DTemp = new Polygon2D(Color(1,0,1), true);
	
				point2DTemp = Point2D(floatCenterX, floatCenterY);
				polygon2DTemp->addPoint(point2DTemp);
				
				point2DTemp = Point2D(floatCenterX, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				point2DTemp = Point2D(floatCenterX + 20, floatCenterY + 20);
				polygon2DTemp->addPoint(point2DTemp);

				object2DComponents.push_back(polygon2DTemp);

				

				circle2DTemp = new Circle2D(Point2D(floatCenterX, floatCenterY), 
											10, Color(0, 1, 1), true);

				object2DComponents.push_back(circle2DTemp);
				circle2DTemp = new Circle2D(Point2D(floatCenterX, floatCenterY), 
											20, Color(1, 0, 0), true);

				object2DComponents.push_back(circle2DTemp);
				floatRadius = 20;
		break;
	}
}

// seteaza viteza de miscare
void Enemy::setSpeed(float floatSpeed1, float floatSpeed2)
{
	floatSpeedX = floatSpeed1;
	floatSpeedY = floatSpeed2;
}

// seteaza unghiul de rotire
void Enemy::setRotation(float floatAngle)
{
	floatRotationAngle = floatAngle;
}

// intoarca numarul figurii geometrice
int Enemy::getEnemyNo(){
	return intEnemyNo;
}

// la coliziunea cu alt inamic isi schimba directia de mers
void Enemy::changeDirection() 
{
	if (!boolPlayerCollision) {
		floatSpeedX = -floatSpeedX;
		floatSpeedY = -floatSpeedY;

		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(floatSpeedX, floatSpeedY);
		for (unsigned int i = 0; i < object2DComponents.size(); i++) {
			Transform2D::applyTransform_o(object2DComponents[i]);
		}
		floatCenterX += floatSpeedX;
		floatCenterY += floatSpeedY;
	} else {
		boolPlayerCollision = false;

		floatSpeedX = -floatSpeedX;
		floatSpeedY = -floatSpeedY;

		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(floatSpeedX * 10, floatSpeedY * 10);
		for (unsigned int i = 0; i < object2DComponents.size(); i++) {
			Transform2D::applyTransform_o(object2DComponents[i]);
		}

		floatCenterX += floatSpeedX * 10;
		floatCenterY += floatSpeedY * 10;
	}
}
	
// verifica coliziunea cu alt inamic
bool Enemy::hasColidedShip(float floatEnemyX, float floatEnemyY, 
							 float floatRadiusEnemy)
{
	float floatX = abs(floatCenterX - floatEnemyX);
	float floatY = abs(floatCenterY - floatEnemyY);
	float floatDistance = sqrt(floatX * floatX + floatY * floatY );
	if (floatDistance  <= floatRadiusEnemy  + floatRadius) {
		return true;
	}
	return false;
}