#pragma once
class Player
{
private:
	float _carPositionX;
	float _carPositionY;
	float _carPositionZ;
	float _maxSpeed;
	float _moveSpeed;
	float _accelerate;
	float _decelerate;
	float _minPositionX;
	float _maxPositionX;
	float _tilt;
	float _radius;
	bool  _moveCar;
	bool  _break;
	bool  _rotateLeft;
	bool  _rotateRight;
public:
	Player(void);
	~Player(void);
	Player::Player(float carPositionX, float carPositionY, float carPositionZ,
		   float maxSpeed, float minPositionX, float maxPositionX);
	void moveCar();
	void render();
	void drawCar();
	void enableMove();
	void disableMove();
	void decelerate();
	void setTilt(float tilt);
	void setMaxSpeed(float maxSpeed);
	bool setRotate(int direction);
	void disableRotate();
	float getSpeed();
	float getPositionZ();
	float getPositionY();
	float getPositionX();
	void setPositionZ(float positionZ);
	void setPositionX(float positionX);
	bool isMoveEnabled();
	bool onSameLane(float pozX);
	bool checkForColision(float posZ, float pozX, float radius); 
};

