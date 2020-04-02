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

	float r = float(obstacleColor3ub[0]) / 255.;
	float g = float(obstacleColor3ub[1]) / 255.;
	float b = float(obstacleColor3ub[2]) / 255.;

	float alpha = obstacleAlpha / 255.;

	//GLfloat rgba[] = { r,g,b,1. };
	//GLfloat fwhite[] = { 1.,1.,1.,1. };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, rgba);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, rgba);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, fwhite);
	//glMaterialf(GL_FRONT, GL_SHININESS, 60.);

	GLfloat vertices[] = {	
		locX, locY, locZ,
		locX + length,locY,locZ,
		locX + length,locY,locZ + width,
		locX,locY,locZ + width,

		locX,locY + height,locZ + width,
		locX + length,locY + height,locZ + width,
		locX + length,locY + height,locZ,
		locX, locY + height, locZ,
		
		locX,locY + height,locZ + width,
		locX, locY + height, locZ,
		locX, locY, locZ,
		locX,locY,locZ + width,

		locX + length,locY + height,locZ,
		locX + length,locY + height,locZ + width,
		locX + length,locY,locZ + width,
		locX + length,locY,locZ,

		locX + length,locY + height,locZ + width,
		locX,locY + height,locZ + width,
		locX,locY,locZ + width,
		locX + length,locY,locZ + width,

		locX, locY + height, locZ,
		locX+length, locY + height, locZ,
		locX+length, locY, locZ,
		locX, locY, locZ};

	GLfloat colors[] = { r,g,b,
							r,g,b,
							r,g,b,
							r,g,b,
							r,g,b,
							r,g,b,
							r,g,b,
							r,g,b,
							r,g,b, 
							r,g,b, 
							r,g,b,
							r,g,b, 
							r,g,b, 
							r,g,b, 
							r,g,b, 
							r,g,b, 
							r,g,b, 
							r,g,b, 
							r,g,b, 
							r,g,b,
							r,g,b,
							r,g,b,
							r,g,b,
							r,g,b };

	GLfloat normals[] = { 0.,1.,0.,
					0.,-1.,0.,
					1.,0.,0.,
					-1.,0.,0.,
					0.,0,1.,
					0.,0.,-1. };

	GLubyte indices[] = {	0,1,2,3,
							4,5,6,7,
							8,9,10,11,
							12,13,14,15,
							16,17,18,19,
							20,21,22,23 };

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normals);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	

}
