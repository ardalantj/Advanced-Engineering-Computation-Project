#include "Scene.h"

Scene::Scene(float oneLength, float oneWidth, float oneHeight)
{
	backBoxLength = oneLength;
	backBoxWidth = oneWidth;
	backBoxHeight = oneHeight;

	Volume tempVolume(backBoxLength,backBoxWidth,backBoxHeight);

	volume = tempVolume;

	Obstacle oneObstacle1(100., 50., 100., 20., 10., 5., 255, 0, 0);
	obstacles[0] = oneObstacle1;

	Obstacle oneObstacle2(20., 70., 150., 10., 10., 10., 0, 255, 0);
	obstacles[1] = oneObstacle2;

	Obstacle oneObstacle3(180., 30., 80., 20., 20., 3., 0, 0, 255);
	obstacles[2] = oneObstacle3;

	for (int i = 0; i < size(obstacles); i++)
	{
		float length = obstacles[i].GetObstacleLength();
		float width = obstacles[i].GetObstacleWidth();
		float height = obstacles[i].GetObstacleHeight();

		float* obstacleAnchor = obstacles[i].GetObstacleAnchor();

		float x = obstacleAnchor[0];
		float y = obstacleAnchor[1];
		float z = obstacleAnchor[2];

		for (int j = x; j < x + length; j++)
		{
			for (int k = y; k < y + height; k++)
			{
				for (int l = z; l < z + width; l++)
				{
					volume.GetVolCube(j, k, l)->blocked = true;
				}
			}
		}
	}

	for (int i = 50; i < 100; i++)
	{
		volume.GetPath()->xyz.push_back(vector<float>{ float(i),30.,30. });
	}
	volume.GetPath()->pathStart = vector<float>{ 50.,30.,30. };
	volume.GetPath()->pathEnd = vector<float>{ 99.,30.,30. };

	volume.OffsetPath();

}

void Scene::RunScene(Camera theCamera)
{

	// Clear opengl
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset Everything
	glLoadIdentity();

	// Set Camera
	gluLookAt(theCamera.getCameraX(), theCamera.getCameraY(), theCamera.getCameraZ(),
		theCamera.getCameraaX() + theCamera.getCameraX(), theCamera.getCameraaY() + theCamera.getCameraY(), theCamera.getCameraaZ() + theCamera.getCameraZ(),
		0.0f, 1.0f, 0.0f);

	//GLfloat qaLightPosition[] = { 100.,200.,100.,0.0 };
	//GLfloat qaLightDirection[] = { 0.,-1.,0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, qaLightDirection);

	//volume.DrawPath();

	DrawBackground();

	for (int i = 0; i < size(obstacles); i++)
	{
		obstacles[i].DrawObstacle();
	}

	volume.DrawPath();
	
}

void Scene::DrawBackground()
{
	glShadeModel(GL_SMOOTH);

	float locX = backBoxAnchor[0];
	float locY = backBoxAnchor[1];
	float locZ = backBoxAnchor[2];

	float height = backBoxHeight;
	float width = backBoxWidth;
	float length = backBoxLength;

	float r = float(backBoxColor3ub[0])/255.;
	float g = float(backBoxColor3ub[0])/255.;
	float b = float(backBoxColor3ub[0])/255.;

	float alpha = backBoxAlpha/255.;

	//GLfloat rgba[] = { r,g,b,1. };
	//GLfloat fwhite[] = { 1.,1.,1.,1. };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, rgba);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, rgba);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, fwhite);
	//glMaterialf(GL_FRONT, GL_SHININESS, 60.);

	GLfloat vertices[] = {	locX, locY, locZ,
							locX + length,locY,locZ,
							locX + length,locY,locZ + width,
							locX,locY,locZ + width,

							locX, locY + height, locZ,
							locX + length,locY + height,locZ,
							locX + length,locY + height,locZ + width,
							locX,locY + height,locZ + width};

	GLfloat colors[] = {	r,g,b,
							r,g,b,
							r,g,b,
							r,g,b,
							1.,1.,1.,
							1.,1.,1.,
							1.,1.,1.,
							1.,1.,1.};

	GLfloat normals[] = { 0.,1.,0.,
						0.,1.,0.,
						0.,0.,1.,
						0.,0.,-1.,
						1.,0,0.,
						-1.,0.,0.};

	GLubyte indices[] = {	3,2,1,0,
							4,5,6,7,
							4,7,3,0,
							6,5,1,2,
							5,4,0,1,
							7,6,2,3 };

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glNormalPointer(GL_FLOAT, 0, normals);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);














	//GLfloat vertices[] = {
	//locX, locY, locZ,
	//locX + length,locY,locZ,
	//locX + length,locY,locZ + width,
	//locX,locY,locZ + width,

	//locX,locY + height,locZ + width,
	//locX + length,locY + height,locZ + width,
	//locX + length,locY + height,locZ,
	//locX, locY + height, locZ,

	//locX,locY + height,locZ + width,
	//locX, locY + height, locZ,
	//locX, locY, locZ,
	//locX,locY,locZ + width,

	//locX + length,locY + height,locZ,
	//locX + length,locY + height,locZ + width,
	//locX + length,locY,locZ + width,
	//locX + length,locY,locZ,

	//locX + length,locY + height,locZ + width,
	//locX,locY + height,locZ + width,
	//locX,locY,locZ + width,
	//locX + length,locY,locZ + width,

	//locX, locY + height, locZ,
	//locX + length, locY + height, locZ,
	//locX + length, locY, locZ,
	//locX, locY, locZ };

	//GLfloat colors[] = { r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b,
	//						r,g,b };

	//GLfloat normals[] = { 0.,1.,0.,
	//				0.,-1.,0.,
	//				0.,0.,1.,
	//				0.,0.,1.,
	//				0.,1,0.,
	//				0.,1.,0. };

	//GLubyte indices[] = { 3,2,1,0,
	//						7,6,5,4,
	//						11,10,9,8,
	//						15,14,13,12,
	//						19,18,17,16,
	//						23,22,21,20 };

	//glColorPointer(3, GL_FLOAT, 0, colors);
	//glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glNormalPointer(GL_FLOAT, 0, normals);
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);


	//rgba[0] = r - .3;
	//rgba[1] = g - .3;
	//rgba[2] = b - .3;
	//glMaterialfv(GL_FRONT, GL_AMBIENT, rgba);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, rgba);
	////glMaterialfv(GL_FRONT, GL_SPECULAR, fwhite);
	//glMaterialf(GL_FRONT, GL_SHININESS, 60.);

	int offsetStart = 1;
	for (int i = 0; i < length; i=i+1) {

		for (int j = offsetStart; j < width; j = j+2)
		{
			GLfloat vertices[] = { locX + i, locY+.075, locZ + j,
					locX + i + 1,locY+.075,locZ + j,
					locX + i + 1,locY+.075,locZ + j + 1,
					locX + i,locY+.075,locZ + j + 1 };

			GLfloat colors[12] = { r - .3,g - .3,b - .3,
										r - .3,g - .3,b - .3,
										r - .3,g - .3,b - .3,
										r - .3,g - .3,b - .3 };

			GLfloat normals[] = { 1.};

			GLubyte indices[] = {3, 2, 1, 0};

			glColorPointer(3, GL_FLOAT, 0, colors);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glNormalPointer(GL_FLOAT, 0, normals);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
		}

		if (offsetStart > 0)
		{
			offsetStart = 0;
		}
		else
		{
			offsetStart = 1;
		}

	}

	offsetStart = 0;
	for (int i = 0; i < length; i = i + 1) {

		for (int j = offsetStart; j < width; j = j + 2)
		{
			GLfloat vertices[] = { locX + i, locY+height-.075, locZ + j,
					locX + i + 1,locY+height-.075,locZ + j,
					locX + i + 1,locY + height-.075,locZ + j + 1,
					locX + i,locY + height-.075,locZ + j + 1 };

			GLfloat colors[12] = { r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3 };

			GLubyte indices[] = { 0, 1, 2, 3 };

			glColorPointer(3, GL_FLOAT, 0, colors);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
		}

		if (offsetStart > 0)
		{
			offsetStart = 0;
		}
		else
		{
			offsetStart = 1;
		}

	}


	offsetStart = 0;
	for (int i = 0; i < length; i = i + 1) {

		for (int j = offsetStart; j < height; j = j + 2)
		{
			GLfloat vertices[] = { locX+.075, locY+j, locZ+i,
					locX + .075,locY+j,locZ+i+1,
					locX + .075,locY+j+1,locZ+i+1,
					locX + .075,locY+j+1,locZ+i};

			GLfloat colors[12] = { r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3 };

			GLubyte indices[] = { 3, 2, 1, 0 };

			glColorPointer(3, GL_FLOAT, 0, colors);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
		}

		if (offsetStart > 0)
		{
			offsetStart = 0;
		}
		else
		{
			offsetStart = 1;
		}

	}

	offsetStart = 1;
	for (int i = 0; i < length; i = i + 1) {

		for (int j = offsetStart; j < height; j = j + 2)
		{
			GLfloat vertices[] = { locX + length - .075, locY + j, locZ + i,
					locX + length - .075,locY + j,locZ + i + 1,
					locX + length - .075,locY + j + 1,locZ + i + 1,
					locX + length - .075,locY + j + 1,locZ + i };

			GLfloat colors[12] = { r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3 };

			GLubyte indices[] = { 0, 1, 2, 3 };

			glColorPointer(3, GL_FLOAT, 0, colors);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
		}

		if (offsetStart > 0)
		{
			offsetStart = 0;
		}
		else
		{
			offsetStart = 1;
		}

	}

	offsetStart = 0;
	for (int i = 0; i < length; i = i + 1) {

		for (int j = offsetStart; j < height; j = j + 2)
		{
			GLfloat vertices[] = { locX+i, locY + j, locZ+.075,
					locX+i+1,locY + j,locZ+.075,
					locX+i+1,locY + j + 1,locZ+.075,
					locX+i,locY + j + 1,locZ+.075};

			GLfloat colors[12] = { r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3 };

			GLubyte indices[] = { 0, 1, 2, 3 };

			glColorPointer(3, GL_FLOAT, 0, colors);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
		}

		if (offsetStart > 0)
		{
			offsetStart = 0;
		}
		else
		{
			offsetStart = 1;
		}

	}

	offsetStart = 1;
	for (int i = 0; i < length; i = i + 1) {

		for (int j = offsetStart; j < height; j = j + 2)
		{
			GLfloat vertices[] = { locX + i, locY + j, locZ + width - .075,
					locX + i + 1,locY + j,locZ + width - .075,
					locX + i + 1,locY + j + 1,locZ + width - .075,
					locX + i,locY + j + 1,locZ + width - .075 };

			GLfloat colors[12] = { r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3,
							r - .3,g - .3,b - .3 };

			GLubyte indices[] = { 3, 2, 1, 0 };

			glColorPointer(3, GL_FLOAT, 0, colors);
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
		}

		if (offsetStart > 0)
		{
			offsetStart = 0;
		}
		else
		{
			offsetStart = 1;
		}

	}

}