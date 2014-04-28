#pragma once
class Enemy
{
private:
	float _carPositionX;
	float _carPositionY;
	float _carPositionZ;
	float _moveSpeed;
	float _radius;
	int   _carNumber;
	int   _carDirection;
public:
	Enemy();
	~Enemy(void);

	Enemy(float carPositionX, float carPositionY, float carPositionZ,
			 float moveSpeed, int carDirection, int carNumber);
	void move();
	void render();
	void createCar();
	void createSphere();
	void createCube();
	void createTorus();
	void createTeapot();
	void createBonus();
	void setPositionZ(float positionZ);
	float getRadius();
	float getDistance(float positionZ);
	float getPositionX();
	float getPositionZ();
	int getNumber();
	bool isInFront(float positionZ, float fieldOfView);
};

