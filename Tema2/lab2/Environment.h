#pragma once


class Environment
{

private:
	float _levelDistance;
	float _minPositionX;
	float _maxPositionX;
	float _lastPositionZ;
	unsigned int	  _glProgramShader;
public:
	Environment(void);
	~Environment(void);
	Environment(unsigned int gl_program_shader, float levelDistance, float minPositionX, float maxPositionX);

	float getMinPositionX();
	float getMaxPositionX();
	void createBloc();
	void renderEnvironment(float startZ);
	void linieIntrerupta();
	void genLinieIntrerupta(float positionX);
	void createPavement();
	void createARoad();
	void renderRoads(int nrRoads);
};

