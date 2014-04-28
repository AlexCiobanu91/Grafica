#pragma once
class Camera
{
private:
float _camPositionX;
float _camPositionY;
float _camPositionZ;
float _cameraLookX;
float _cameraLookY;
float _cameraLookZ;
float _tilt;
public:
	Camera(void);
	Camera(float camPositionX, float camPositionY, float camPositionZ,
		   float cameraLookX,  float cameraLookY,  float cameraLookZ);

	~Camera(void);
	void moveCameraZ(float moveSpeed);
	void moveCameraX(float moveSpeed);
	void play();
	void setTilt(float tilt);
};
