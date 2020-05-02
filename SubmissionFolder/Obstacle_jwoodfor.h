#pragma once

#include <GL/glut.h>

#include "Drawing_jwoodfor.h"

class Obstacle
{

private:

	float obstacleWidth = 200.;
	float obstacleHeight = 100.;
	float obstacleLength = 200.;
	float obstacleAnchor[3] = { 0., 0., 0. };
	int obstacleAlpha = 255;
	int obstacleColor3ub[3] = { 255, 0, 0 };

	




public:

	void SetObstacleWidth(float oneWidth) { obstacleWidth = oneWidth; }
	float GetObstacleWidth() { return obstacleWidth; }

	void SetObstacleLength(float oneLength) { obstacleLength = oneLength; }
	float GetObstacleLength() { return obstacleLength; }

	void SetObstacleHeight(float oneHeight) { obstacleHeight = oneHeight; }
	float GetObstacleHeight() { return obstacleHeight; }

	void SetobstacleAnchor(float x, float y, float z) { obstacleAnchor[0] = x; obstacleAnchor[1] = y; obstacleAnchor[2] = z; }
	float* GetObstacleAnchor() { return obstacleAnchor; }

	Obstacle();

	Obstacle(float x, float y, float z, float length, float width, float height, int r, int g, int b);

	void DrawObstacle();

};

