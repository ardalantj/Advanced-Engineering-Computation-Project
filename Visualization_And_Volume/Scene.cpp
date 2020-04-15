#include "Scene.h"

Scene::Scene(float oneLength, float oneWidth, float oneHeight)
{
	backBoxLength = oneLength;
	backBoxWidth = oneWidth;
	backBoxHeight = oneHeight;

	Volume tempVolume(backBoxLength,backBoxWidth,backBoxHeight);

	volume = tempVolume;

	//Obstacle oneObstacle1(100., 50., 100., 20., 10., 5., 255, 0, 0);
	//obstacles[0] = oneObstacle1;

	Obstacle oneObstacle1(50., 50., 50., 5., 5., 5., 255, 0, 0.);
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


	GLfloat fwhite[] = { 1.,1.,1.,1. };
	GLfloat fblack[] = { 0.,0.,0.,1. };
	GLfloat qaAmbientLight[] = { .2,.2,.2,1.0 };
	GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };
	GLfloat qaSpecularLight[] = { 1.,1.,1.,1. };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	DrawBackground();

	for (int i = 0; i < size(obstacles); i++)
	{
		obstacles[i].DrawObstacle();
	}

	volume.DrawPath();

	//GLfloat qaLightPosition[] = { backBoxLength/2.,backBoxHeight/1.2,backBoxWidth/2.,.0 };
	//GLfloat qaLightDirection[] = { 0.,-1.,0. };
	//glPushMatrix();
	//glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, qaLightDirection);
	//glPopMatrix();












	GLfloat qaAmbientLight1[] = { 1.,1.,1.,1.0 };
	GLfloat qaDiffuseLight1[] = { 0.,0.,0.,1.0 };
	GLfloat qaSpecularLight1[] = { 0.,0.,0.,1. };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, fwhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, fblack);
	glMaterialfv(GL_FRONT, GL_SPECULAR, fblack);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.);

	//float camX = backBoxLength / 2.;
	//float camZ = backBoxWidth / 2.;
	//float camY = backBoxHeight / 1.2;
	//float normCamDir[3] = { 0.,0.,-1. };

	float camX = 100 * sin(countTime / 150.) + backBoxLength / 2.;
	float camZ = 100 * cos(countTime / 150.) + backBoxWidth / 2.;
	float camY = backBoxHeight / 1.2;

	countTime++;

	float camDir[3] = { 0,0,0 };

	camDir[0] = backBoxLength / 2. - camX;
	camDir[1] = 0. - camY;
	camDir[2] = backBoxWidth / 2. - camZ;

	float* normCamDir = Normalize(camDir);

	GLfloat qaLightPosition[] = { camX,camY,camZ,1.0 };
	GLfloat qaLightDirection[] = { normCamDir[0],normCamDir[1],normCamDir[2] };
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, qaLightDirection);
	glPopMatrix();

	glPushMatrix();
	glScalef(1., 1., 1.);
	glTranslatef(qaLightPosition[0], qaLightPosition[1], qaLightPosition[2]);
	glutSolidCube(1.);
	glPopMatrix();


















	//int X = 100;
	//int Y = 100;
	//int Z = 100;

	//int*** arr3D = new int** [X];
	//for (int i = 0; i < X; i++) {
	//	arr3D[i] = new int* [Y];
	//	for (int j = 0; j < Y; j++) {
	//		arr3D[i][j] = new int[Z];
	//		for (int k = 0; k < Z; k++) {
	//			if (i >= 25 && i < 75 && j >= 25 && j < 75 && k >= 25 && k < 75) arr3D[i][j][k] = 1;
	//		}
	//	}
	//}

	//double* start = new double[3];
	//*start = 50;
	//*(start + 1) = 50;
	//*(start + 2) = 24;
	//double* end = new double[3];
	//*end = 50;
	//*(end + 1) = 50;
	//*(end + 2) = 76;

	//RRT_connect dronePlanner(start, end, arr3D, X, Y, Z);
	//int length = 0;
	//std::vector<std::vector<double>> plan = dronePlanner.search(100000, 0.1, 1, &length);

	//for (int i = 0; i < length; i++)
	//{
	//	double x = plan[i][0];
	//	double y = plan[i][1];
	//	double z = plan[i][2];
	//	std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
	//}

	//for (int i = 0; i < X; ++i) {
	//	for (int j = 0; j < Y; ++j)
	//	{
	//		delete[] arr3D[i][j];
	//	}
	//	delete[] arr3D[i];
	//}


	
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

	float r = float(backBoxColor3ub[0]);
	float g = float(backBoxColor3ub[0]);
	float b = float(backBoxColor3ub[0]);

	float alpha = backBoxAlpha;

	float lwh[3] = { length, width, height };
	float rgbaBack[4] = { r,g,b,alpha };
	float shininessBack = 60.;

	glPushMatrix();
	SetMaterial(rgbaBack, shininessBack);
	DrawCubeInv(lwh, rgbaBack);
	glPopMatrix();

	// NEED TO PUT IN THE MESHES HERE, ROTATE AND TRANSLATE

	float rgbaCheckerMain[4] = { 50,50,50,255 };
	float rgbaCheckerOff[4] = { 50,50,50,255 };
	float shininessChecker = 60.;

	//glPushMatrix();
	//glTranslatef(0., .075, 0.);
	//glRotatef(0, 0, 0, 0);
	//SetMaterial(rgbaCheckerMain, shininessChecker);
	//DrawCheckerGaps(int(backBoxLength), int(backBoxWidth), 1., 1., rgbaCheckerMain,false);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(backBoxLength, backBoxHeight-.075, 0.);
	//glRotatef(180, 0, 0, 1);
	//SetMaterial(rgbaCheckerMain, shininessChecker);
	//DrawCheckerGaps(int(backBoxLength), int(backBoxWidth), 1., 1., rgbaCheckerMain, false);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0., 0., .075);
	//glRotatef(90, 1, 0, 0);
	//glRotatef(90, 0, 1, 0);
	//SetMaterial(rgbaCheckerMain, shininessChecker);
	//DrawCheckerGaps(int(backBoxHeight), int(backBoxLength), 1., 1., rgbaCheckerMain,true);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0, 0., backBoxWidth - .075);
	//glRotatef(90, 1, 0, 0);
	//glRotatef(-180, 0, 1, 0);
	//glRotatef(180, 0, 0, 1);
	//SetMaterial(rgbaCheckerMain, shininessChecker);
	//DrawCheckerGaps(int(backBoxLength), int(backBoxHeight), 1., 1., rgbaCheckerMain, false);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(.075, 0., 0.);
	//glRotatef(90, 1, 0, 0);
	//glRotatef(-180, 0, 1, 0);
	//glRotatef(90, 0, 0, 1);
	//SetMaterial(rgbaCheckerMain, shininessChecker);
	//DrawCheckerGaps(int(backBoxWidth), int(backBoxHeight), 1., 1., rgbaCheckerMain, true);
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(backBoxLength-.075, 0., backBoxWidth);
	//glRotatef(-90, 1, 0, 0);
	//glRotatef(90, 0, 0, 1);
	//SetMaterial(rgbaCheckerMain, shininessChecker);
	//DrawCheckerGaps(int(backBoxWidth), int(backBoxHeight), 1., 1., rgbaCheckerMain, true);
	//glPopMatrix();



	
	//glMaterialfv(GL_FRONT, GL_AMBIENT, rgbaChecker);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, rgbaChecker);
	////glMaterialfv(GL_FRONT, GL_SPECULAR, fwhite);
	//glMaterialf(GL_FRONT, GL_SHININESS, 60.);

	//int offsetStart = 1;
	//for (int i = 0; i < length; i=i+1) {

	//	for (int j = offsetStart; j < width; j = j+2)
	//	{
	//		GLfloat vertices[] = { locX + i, locY+.075, locZ + j,
	//				locX + i + 1,locY+.075,locZ + j,
	//				locX + i + 1,locY+.075,locZ + j + 1,
	//				locX + i,locY+.075,locZ + j + 1 };

	//		GLfloat colors[12] = { r - .3,g - .3,b - .3,
	//									r - .3,g - .3,b - .3,
	//									r - .3,g - .3,b - .3,
	//									r - .3,g - .3,b - .3 };

	//		GLfloat normals[] = { 0.,1.,0.,  0.,1.,0.,  0.,1.,0.,  0.,1.,0.};

	//		GLubyte indices[] = {3, 2, 1, 0};

	//		glColorPointer(3, GL_FLOAT, 0, colors);
	//		glVertexPointer(3, GL_FLOAT, 0, vertices);
	//		glNormalPointer(GL_FLOAT, 0, normals);
	//		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	//	}

	//	if (offsetStart > 0)
	//	{
	//		offsetStart = 0;
	//	}
	//	else
	//	{
	//		offsetStart = 1;
	//	}

	//}

	//offsetStart = 0;
	//for (int i = 0; i < length; i = i + 1) {

	//	for (int j = offsetStart; j < width; j = j + 2)
	//	{
	//		GLfloat vertices[] = { locX + i, locY+height-.075, locZ + j,
	//				locX + i + 1,locY+height-.075,locZ + j,
	//				locX + i + 1,locY + height-.075,locZ + j + 1,
	//				locX + i,locY + height-.075,locZ + j + 1 };

	//		GLfloat colors[12] = { r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3 };

	//		GLfloat normals[] = { 0.,-1.,0.,  0.,-1.,0.,  0.,-1.,0.,  0.,-1.,0. };

	//		GLubyte indices[] = { 0, 1, 2, 3 };

	//		glColorPointer(3, GL_FLOAT, 0, colors);
	//		glVertexPointer(3, GL_FLOAT, 0, vertices);
	//		glNormalPointer(GL_FLOAT, 0, normals);
	//		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	//	}

	//	if (offsetStart > 0)
	//	{
	//		offsetStart = 0;
	//	}
	//	else
	//	{
	//		offsetStart = 1;
	//	}

	//}


	//offsetStart = 0;
	//for (int i = 0; i < length; i = i + 1) {

	//	for (int j = offsetStart; j < height; j = j + 2)
	//	{
	//		GLfloat vertices[] = { locX+.075, locY+j, locZ+i,
	//				locX + .075,locY+j,locZ+i+1,
	//				locX + .075,locY+j+1,locZ+i+1,
	//				locX + .075,locY+j+1,locZ+i};

	//		GLfloat colors[12] = { r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3 };

	//		GLfloat normals[] = { 1.,0.,0.,  1.,0.,0.,  1.,0.,0.,  1.,0.,0. };

	//		GLubyte indices[] = { 3, 2, 1, 0 };

	//		glColorPointer(3, GL_FLOAT, 0, colors);
	//		glVertexPointer(3, GL_FLOAT, 0, vertices);
	//		glNormalPointer(GL_FLOAT, 0, normals);
	//		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	//	}

	//	if (offsetStart > 0)
	//	{
	//		offsetStart = 0;
	//	}
	//	else
	//	{
	//		offsetStart = 1;
	//	}

	//}

	//offsetStart = 1;
	//for (int i = 0; i < length; i = i + 1) {

	//	for (int j = offsetStart; j < height; j = j + 2)
	//	{
	//		GLfloat vertices[] = { locX + length - .075, locY + j, locZ + i,
	//				locX + length - .075,locY + j,locZ + i + 1,
	//				locX + length - .075,locY + j + 1,locZ + i + 1,
	//				locX + length - .075,locY + j + 1,locZ + i };

	//		GLfloat colors[12] = { r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3 };

	//		GLfloat normals[] = { -1.,0.,0.,  -1.,0.,0.,  -1.,0.,0.,  -1.,0.,0. };

	//		GLubyte indices[] = { 0, 1, 2, 3 };

	//		glColorPointer(3, GL_FLOAT, 0, colors);
	//		glVertexPointer(3, GL_FLOAT, 0, vertices);
	//		glNormalPointer(GL_FLOAT, 0, normals);
	//		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	//	}

	//	if (offsetStart > 0)
	//	{
	//		offsetStart = 0;
	//	}
	//	else
	//	{
	//		offsetStart = 1;
	//	}

	//}

	//offsetStart = 0;
	//for (int i = 0; i < length; i = i + 1) {

	//	for (int j = offsetStart; j < height; j = j + 2)
	//	{
	//		GLfloat vertices[] = { locX+i, locY + j, locZ+.075,
	//				locX+i+1,locY + j,locZ+.075,
	//				locX+i+1,locY + j + 1,locZ+.075,
	//				locX+i,locY + j + 1,locZ+.075};

	//		GLfloat colors[12] = { r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3 };

	//		GLfloat normals[] = { 0.,0.,1.,  0.,0.,1.,  0.,0.,1.,  0.,0.,1. };

	//		GLubyte indices[] = { 0, 1, 2, 3 };

	//		glColorPointer(3, GL_FLOAT, 0, colors);
	//		glVertexPointer(3, GL_FLOAT, 0, vertices);
	//		glNormalPointer(GL_FLOAT, 0, normals);
	//		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	//	}

	//	if (offsetStart > 0)
	//	{
	//		offsetStart = 0;
	//	}
	//	else
	//	{
	//		offsetStart = 1;
	//	}

	//}

	//offsetStart = 1;
	//for (int i = 0; i < length; i = i + 1) {

	//	for (int j = offsetStart; j < height; j = j + 2)
	//	{
	//		GLfloat vertices[] = { locX + i, locY + j, locZ + width - .075,
	//				locX + i + 1,locY + j,locZ + width - .075,
	//				locX + i + 1,locY + j + 1,locZ + width - .075,
	//				locX + i,locY + j + 1,locZ + width - .075 };

	//		GLfloat colors[12] = { r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3,
	//						r - .3,g - .3,b - .3 };

	//		GLfloat normals[] = { 0.,0.,-1.,  0.,0.,-1.,  0.,0.,-1.,  0.,0.,-1. };

	//		GLubyte indices[] = { 3, 2, 1, 0 };

	//		glColorPointer(3, GL_FLOAT, 0, colors);
	//		glVertexPointer(3, GL_FLOAT, 0, vertices);
	//		glNormalPointer(GL_FLOAT, 0, normals);
	//		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	//	}

	//	if (offsetStart > 0)
	//	{
	//		offsetStart = 0;
	//	}
	//	else
	//	{
	//		offsetStart = 1;
	//	}

	//}

}