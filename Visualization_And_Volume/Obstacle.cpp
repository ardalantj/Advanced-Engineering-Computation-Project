#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(float x, float y, float z, float length, float width, float height, int r, int g, int b)
{

	obstacleAnchor[0] = x;
	obstacleAnchor[1] = y;
	obstacleAnchor[2] = z;

	obstacleLength = length;
	obstacleWidth = width;
	obstacleHeight = height;

	obstacleColor3ub[0] = r;
	obstacleColor3ub[1] = g;
	obstacleColor3ub[2] = b;

}

void Obstacle::DrawObstacle()
{

	glShadeModel(GL_SMOOTH);

	float locX = obstacleAnchor[0];
	float locY = obstacleAnchor[1];
	float locZ = obstacleAnchor[2];

	float height = obstacleHeight;
	float width = obstacleWidth;
	float length = obstacleLength;

	float r = float(obstacleColor3ub[0]);
	float g = float(obstacleColor3ub[1]);
	float b = float(obstacleColor3ub[2]);

	float alpha = obstacleAlpha;

	float lwh[3] = { length, width, height };
	float rgba[4] = { r,g,b,alpha };
	float shininessObstacle = 60.;

	glPushMatrix();
	glTranslatef(locX, locY, locZ);
	glRotatef(0, 0, 0, 0);
	SetMaterial(rgba, shininessObstacle);
	DrawCube(lwh, rgba);
	glPopMatrix();

}
