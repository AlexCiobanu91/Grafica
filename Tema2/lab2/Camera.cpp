#include "Camera.h"
#include "dependente\freeglut.h"

Camera::Camera(void)
{

}

Camera::Camera(float camPositionX, float camPositionY, float camPositionZ,
			   float cameraLookX,  float cameraLookY,  float cameraLookZ)
{
	_cameraLookX  = cameraLookX;
	_cameraLookY  = cameraLookY;
	_cameraLookZ  = cameraLookZ;
	_camPositionX = camPositionX;
	_camPositionY = camPositionY;
	_camPositionZ = camPositionZ;
	_tilt         = 0;
}

Camera::~Camera(void)
{
}

void Camera::play()
{
	gluLookAt(_camPositionX, _camPositionY, _camPositionZ + 10, 
			  _cameraLookX, _cameraLookY,  _cameraLookZ - 1.0f,
			  0.0f + _tilt , 1,  0.0f );
}

void Camera::setTilt(float tilt)
{
	_tilt += tilt;
}

void Camera::moveCameraZ(float speed)
{
	_camPositionZ -= speed;
	_cameraLookZ  -= speed;
}

void Camera::moveCameraX(float moveSpeed)
{
	_camPositionX += moveSpeed;
	_cameraLookX  += moveSpeed;
}