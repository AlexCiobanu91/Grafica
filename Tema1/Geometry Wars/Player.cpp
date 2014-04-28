//implementarea clasei Transform2D - trebuie sa fie treaba studentilor

#include "Player.h"
#include "math.h"
#include <iostream>
using namespace std;

Player::Player(Point2D point2DPosition, Color colorPlayerColor)
{
	floatCenterX = point2DPosition.x;
	floatCenterY = point2DPosition.y;
	floatRotation = 0;
	floatRadius   = 20;
	floatMaxSpeed = 40;
	circle2DShield = new Circle2D(Point2D(floatCenterX, floatCenterY), 
								  25, colorPlayerColor, false);

	polygon2DBody= new Polygon2D(colorPlayerColor, false);
	
	Point2D point2DTemp = Point2D(floatCenterX - 10, floatCenterY);
	polygon2DBody->addPoint(point2DTemp);

	point2DTemp = Point2D(floatCenterX , floatCenterY + 20);
	polygon2DBody->addPoint(point2DTemp);

	point2DTemp = Point2D(floatCenterX + 20, (float) (floatCenterY + 7.5));
	polygon2DBody->addPoint(point2DTemp);
	
	point2DTemp = Point2D(floatCenterX + 5, floatCenterY + 16);
	polygon2DBody->addPoint(point2DTemp);

	/////////////////// MiJLOC ///////////////////////////////////
	point2DTemp = Point2D(floatCenterX , floatCenterY);
	polygon2DBody->addPoint(point2DTemp);
	//////////////////////////////////////////////////////////////

	point2DTemp = Point2D(floatCenterX + 5, floatCenterY - 16);
	polygon2DBody->addPoint(point2DTemp);

	point2DTemp = Point2D(floatCenterX + 20, (float) (floatCenterY - 7.5));
	polygon2DBody->addPoint(point2DTemp);
	
	point2DTemp = Point2D(floatCenterX, floatCenterY - 20);
	polygon2DBody->addPoint(point2DTemp);
	
	polygon2DDrill = new Polygon2D(colorPlayerColor, true);

	point2DTemp = Point2D(floatCenterX + 90, floatCenterY);
	polygon2DDrill->addPoint(point2DTemp);

	point2DTemp = Point2D(floatCenterX + 30, floatCenterY - 20);
	polygon2DDrill->addPoint(point2DTemp);

	point2DTemp = Point2D(floatCenterX + 30, floatCenterY + 20);
	polygon2DDrill->addPoint(point2DTemp);

	deactivateWeapon();
}

void Player::rotateBody(float floatSpeed)
{ 	
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(- floatCenterX, - floatCenterY);
	Transform2D::rotateMatrix(floatSpeed);
	Transform2D::translateMatrix(floatCenterX, floatCenterY);

	Transform2D::applyTransform_o(polygon2DBody);
	Transform2D::applyTransform_o(circle2DShield);	
	Transform2D::applyTransform_o(polygon2DDrill);	
	floatRotation += floatSpeed;
}

void Player::moveBody(float floatWidth, float floatHeight)
{
	if (boolWeapon) {
		floatSpeed = floatWeaponSpeed;
	} else {
		floatSpeed = floatNormalSpeed;
	}

	floatSpeedX = floatSpeed * cos(floatRotation);
	floatSpeedY = floatSpeed * sin(floatRotation);
		
	if (isMovePossible(floatWidth, floatHeight)) {
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(floatSpeedX, floatSpeedY);

		Transform2D::applyTransform_o(polygon2DBody);
		Transform2D::applyTransform_o(circle2DShield);	
		Transform2D::applyTransform_o(polygon2DDrill);
	
		floatCenterX += floatSpeedX;
		floatCenterY += floatSpeedY;
	}
}

void Player::scaleBody(float floatScale) 
{
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(- floatCenterX, -floatCenterY);
	Transform2D::scaleMatrix(floatScale, floatScale);
	Transform2D::translateMatrix(floatCenterX, floatCenterY);
	Transform2D::applyTransform_o(polygon2DBody);
	Transform2D::applyTransform_o(circle2DShield);	
	Transform2D::applyTransform_o(polygon2DDrill);

	floatRadius *= floatScale;
}

// verifica daca jucatorul nu iese in afara ecranului
bool Player::isMovePossible(float floatWidth, float floatHeight) 
{
	// padding
	float floatStartX = 10;
	float floatStartY = 10;

	floatWidth  -= 40;
	floatHeight -= 40;
	if (floatCenterX + floatSpeedX - floatStartX > floatWidth ||
		floatCenterX + floatSpeedX - floatRadius < 0) {
		return false;
	}

	if (floatCenterY + floatSpeedY - floatStartY > floatHeight ||
		floatCenterY + floatSpeedY - floatRadius < 0) {
		return false;
	}

	return true;
	
}

// activeaza arma
void Player::activateWeapon() 
{
	boolWeapon = true;
}

void Player::deactivateWeapon() 
{
	boolWeapon = false;
}

// viteza fara arma
void Player::setNormalSpeed(float floatNSpeed)
{
	floatNormalSpeed = floatNSpeed;
}

// viteza cu arma
void Player::setWeaponSpeed(float floatWSpeed)
{
	floatWeaponSpeed = floatWSpeed;
}

// intoarce true daca arma e activata
bool Player::getWeaponState() 
{
	return boolWeapon;
}

// verifica daca a avut loc o coliziune intre corpului figurii geometrice
// si alta figura geometrica
bool  Player::hasColidedShip(float floatEnemyX, float floatEnemyY, 
							 float floatRadiusEnemy)
{
	float floatX = abs(floatCenterX - floatEnemyX);
	float floatY = abs(floatCenterY - floatEnemyY);
	float floatDistance = sqrt(floatX * floatX + floatY * floatY );
	if (floatDistance  <= floatRadiusEnemy + floatRadius) {
		return true;
	}
	return false;
}

// verifica daca a avut loc o coliziune intre arma jucatorului
// si alta figura geometrica
bool  Player::hasColidedWeapon(float floatEnemyX, float floatEnemyY)
{
	float floatMaxX = -FLT_MAX;
	float floatMaxY = -FLT_MAX;

	float floatMinX = FLT_MAX;
	float floatMinY = FLT_MAX;

	for ( unsigned int i = 0; i < polygon2DDrill->transf_points.size() ; i ++) {
		if (floatMaxX < polygon2DDrill->transf_points[i]->x) {
			floatMaxX = polygon2DDrill->transf_points[i]->x;
		}

		if (floatMaxY < polygon2DDrill->transf_points[i]->y) {
			floatMaxY = polygon2DDrill->transf_points[i]->y;
		}

		if (floatMinX > polygon2DDrill->transf_points[i]->x) {
			floatMinX = polygon2DDrill->transf_points[i]->x;
		}

		if (floatMinY > polygon2DDrill->transf_points[i]->y) {
			floatMinY = polygon2DDrill->transf_points[i]->y;
		}
	}

	if (floatEnemyX > floatMinX && floatEnemyX < floatMaxX &&
		floatEnemyY > floatMinY && floatEnemyY < floatMaxY) {
		return true;
	}
	return false;
}

float Player::getNormalSpeed() 
{
	return floatNormalSpeed;
}

float Player::getDistance(float floatX, float floatY)
{
	float floatXTemp = abs(floatCenterX - floatX);
	float floatYTemp = abs(floatCenterY - floatY);
	return sqrt(floatXTemp * floatXTemp + floatYTemp * floatYTemp );
}

// seteaza o nout pozitie pentru jucator
void Player::setPosition(float floatX, float floatY)
{
	float floatDiffX = floatX - floatCenterX;
	float floatDiffY = floatY - floatCenterY;

	floatCenterX += floatDiffX;
	floatCenterY += floatDiffY;

	for (int i = 0 ; i < polygon2DBody->transf_points.size(); i ++) {
		float floatCrtX = polygon2DBody->transf_points[i]->x;
		float floatCrtY = polygon2DBody->transf_points[i]->y;
		polygon2DBody->transf_points[i] = new Point2D(floatCrtX + floatDiffX,
													  floatCrtY + floatDiffY);
	}

	for (int i = 0 ; i < circle2DShield->transf_points.size(); i ++) {
		float floatCrtX = circle2DShield->transf_points[i]->x;
		float floatCrtY = circle2DShield->transf_points[i]->y;
		circle2DShield->transf_points[i] = new Point2D(floatCrtX + floatDiffX,
													   floatCrtY + floatDiffY);
	}
}