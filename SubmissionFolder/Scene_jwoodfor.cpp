#include "Scene_jwoodfor.h"
#include <queue>


Scene::Scene(float oneLength, float oneWidth, float oneHeight)
{
	backBoxLength = oneLength;
	backBoxWidth = oneWidth;
	backBoxHeight = oneHeight;

	Volume tempVolume(backBoxLength, backBoxWidth, backBoxHeight);

	volume = tempVolume;

	//Obstacle oneObstacle1(100., 50., 100., 20., 10., 5., 255, 0, 0);
	//obstacles[0] = oneObstacle1;

	Obstacle oneObstacle1(50., 50., 50., 5., 5., 5., 255, 0, 0.);
	obstacles[0] = oneObstacle1;

	Obstacle oneObstacle2(20., 70., 150., 10., 10., 10., 0, 255, 0);
	obstacles[1] = oneObstacle2;

	Obstacle oneObstacle3(180., 30., 80., 20., 20., 3., 0, 0, 255);
	obstacles[2] = oneObstacle3;

	Obstacle oneObstacle4(70., 5., 25., 20., 20., 100., 255, 0, 255);
	obstacles[3] = oneObstacle4;

	for (int i = 0; i < 3; i++)
	{
		userDesStart.push_back(0.);
		userDesEnd.push_back(0.);
	}

	for (int i = 0; i < numObstacles; i++)
	{
		float length = obstacles[i].GetObstacleLength();
		float width = obstacles[i].GetObstacleWidth();
		float height = obstacles[i].GetObstacleHeight();

		float* obstacleAnchor = obstacles[i].GetObstacleAnchor();

		float offset = 2.;

		float minX = obstacleAnchor[0] - offset;
		float maxX = obstacleAnchor[0] + length + offset;

		if (minX < 0)
		{
			minX = 0.;
		}
		if (maxX > volume.GetLength())
		{
			maxX = volume.GetLength();
		}

		float minY = obstacleAnchor[1] - offset;
		float maxY = obstacleAnchor[1] + height + offset;

		if (minY < 0)
		{
			minY = 0.;
		}
		if (maxY > volume.GetHeight())
		{
			maxY = volume.GetHeight();
		}

		float minZ = obstacleAnchor[2] - offset;
		float maxZ = obstacleAnchor[2] + width + offset;

		if (minZ < 0)
		{
			minZ = 0.;
		}
		if (maxZ > volume.GetWidth())
		{
			maxZ = volume.GetWidth();
		}

		//float y = obstacleAnchor[1] - offset;
		//float z = obstacleAnchor[2] - offset;




		for (int j = minX; j < maxX; j++)
		{
			for (int k = minY; k < maxY; k++)
			{
				for (int l = minZ; l < maxZ; l++)
				{
					volume.GetVolCube(j, k, l)->blocked = true;
				}
			}
		}
	}

	//const vector<double> startPoint = { 50.,30.,30. };
	//const vector<double> endPoint = { 99.,70.,30. };

	//RRT_connect dronePlanner(startPoint, endPoint, volume.GetVolumeStates(), volume.GetLength(), volume.GetHeight(), volume.GetWidth());

	//int length = 0;
	//vector<vector<double> > plan = dronePlanner.search(100000, .1, 1, &length);

	//volume.SetPathVect(plan);

	////for (int i = 50; i < 100; i++)
	////{
	////	volume.GetPath()->xyz.push_back(vector<double>{ double(i),30.,30. });
	////}
	////volume.GetPath()->pathStart = vector<double>{ 50.,30.,30. };
	////volume.GetPath()->pathEnd = vector<double>{ 99.,30.,30. };

	//volume.OffsetPath();

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
	GLfloat qaAmbientLight[] = { .2,.2,.2,1. };
	GLfloat qaAllAmbientLight[] = { 1.,1.,1.,1. };
	GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,1. };
	GLfloat qaNoDiffuseLight[] = { 0.8,0.8,0.8,1. };
	GLfloat qaSpecularLight[] = { 1.,1.,1.,1. };
	GLfloat qaNoSpecularLight[] = { 0.,0.,0.,0. };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	DrawBackground();

	for (int i = 0; i < numObstacles; i++)
	{
		obstacles[i].DrawObstacle();
	}

	//enum pathType { none, rrt, astar };

	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAllAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaNoDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaNoSpecularLight);
	switch (desPath)
	{

	case none:
	{
		volume.ClearPathVect();
		break;
	}

	case rrt:
	{
		if (desPath != currPath)
		{

			volume.ClearPathVect();

			int startPointArr[3] = { 50.,30.,30. };
			int endPointArr[3] = { 99.,70.,30. };

			vector<double> startPoint;
			vector<double> endPoint;

			for (int countD = 0; countD < 3; countD++)
			{
				startPoint.push_back(startPointArr[countD]);
				endPoint.push_back(endPointArr[countD]);
			}

			RRT_connect dronePlanner(startPoint, endPoint, volume.GetVolumeStates(), volume.GetLength(), volume.GetHeight(), volume.GetWidth());

			int length = 0;
			vector<vector<double> > plan = dronePlanner.search(100000, .1, 1, &length);

			if (plan.size() > 0)
			{
				volume.SetPathVect(plan);

				volume.OffsetPath();

				currPath = desPath;
			}

		}

		volume.DrawPath();

		break;
	}

	case astar:
	{
		if (desPath != currPath)
		{

			volume.ClearPathVect();

			int startPointArr[3] = { 50.,30.,30. };
			int endPointArr[3] = { 99.,70.,30. };

			vector<double> startPoint;
			vector<double> endPoint;

			for (int countD = 0; countD < 3; countD++)
			{
				startPoint.push_back(startPointArr[countD]);
				endPoint.push_back(endPointArr[countD]);
			}

			vector<int> startPointInt;
			for (double i : startPoint)
			{
				startPointInt.push_back(int(i));
			}

			vector<int> endPointInt;
			for (double i : endPoint)
			{
				endPointInt.push_back(int(i));
			}

			vector<vector<int> > planInt = aStarSearch(volume.GetVolumeStates(), startPointInt, endPointInt);

			vector<vector<double> > planDouble;
			for (vector<int> onePoint : planInt)
			{
				vector<double> tempVector;
				for (int onePartPoint : onePoint)
				{
					tempVector.push_back(double(onePartPoint));
				}
				planDouble.push_back(tempVector);
			}

			if (planDouble.size() > 0)
			{
				volume.SetPathVect(planDouble);

				volume.OffsetPath();

				currPath = desPath;
			}

		}

		volume.DrawPath();

		break;
	}


	}
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	//volume.DrawPath();

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

	float camX = backBoxLength / 2.;
	float camZ = backBoxWidth / 2.;
	float camY = backBoxHeight / 1.2;
	float normCamDir[3] = { 0.,0.,-1. };

	//float camX = 100 * sin(countTime / 150.) + backBoxLength / 2.;
	//float camZ = 100 * cos(countTime / 150.) + backBoxWidth / 2.;
	//float camY = backBoxHeight / 1.2;

	countTime++;

	//float camDir[3] = { 0,0,0 };

	//camDir[0] = backBoxLength / 2. - camX;
	//camDir[1] = 0. - camY;
	//camDir[2] = backBoxWidth / 2. - camZ;

	//float* normCamDir = Normalize(camDir);

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
	//std::vector<std::vector<double> > plan = dronePlanner.search(100000, 0.1, 1, &length);

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





//#define ROW 200 
//#define COL 100
//#define HEI 200
//
//class Node {
//
//public:
//
//	int gridX;
//	int gridY;
//	int gridZ;
//
//	double gCost;
//	double hCost;
//
//	Node* parent;
//
//	Node(int _gridX, int _gridY, int _gridZ) {
//		gridX = _gridX;
//		gridY = _gridY;
//		gridZ = _gridZ;
//	}
//
//	int fCost() const {
//
//		return gCost + hCost;
//
//	}
//
//	~Node()
//	{
//		// cout<<"\n Destructor called";
//	   // delete parent;
//	}
//
//	bool operator==(const Node& t) const
//	{
//		if (this->gridX == t.gridX && this->gridY == t.gridY && this->gridZ == t.gridZ) {
//			printf("Comes Here\n");
//			return true;
//		}
//	}
//
//	bool operator!=(const Node& t) const
//	{
//		if (!(this->gridX == t.gridX && this->gridY == t.gridY && this->gridZ == t.gridZ)) {
//			return true;
//		}
//	}
//
//};
//
//struct compareFValue {
//	bool operator()(Node* p1, Node* p2)
//	{
//		if (p1->fCost() == p2->fCost()) {
//			return p1->hCost > p2->hCost;
//		}
//		return p1->fCost() > p2->fCost(); //> for the lowest element at the top. 
//	}
//};
//
//vector<vector<int> > RetracePath(Node* startNode, Node* endNode) {
//
//	vector<vector<int> > path;
//
//	Node* currentnode = endNode;
//
//	currentnode->parent = endNode->parent;
//
//	long totalLength = ROW * COL * HEI;
//
//	int i = 0;
//
//	while (!(currentnode->gridX == startNode->gridX && currentnode->gridY == startNode->gridY && currentnode->gridZ == startNode->gridZ)) {
//
//		path.push_back({ currentnode->gridX, currentnode->gridY, currentnode->gridZ });
//		currentnode = currentnode->parent;
//
//		i = i + 1;
//	}
//
//	reverse(path.begin(), path.end());
//	delete(startNode);
//	// delete()
//	for (int i = 0; i < path.size(); i++)
//		printf("\n -> (%d,%d,%d) ", path[i][0], path[i][1], path[i][2]);
//
//	return path;
//}
//
//static bool isValid(int row, int col, int hei)
//{
//
//	return (row >= 0) && (row < ROW) &&
//		(col >= 0) && (col < COL) &&
//		(hei >= 0) && (hei < HEI);
//}
//
//bool isUnBlocked(vector<vector<vector<int> > > grid, int i, int j, int k)
//{
//	if (grid[i][j][k] == 1)
//		return (true);
//	else
//		return (false);
//}
//
//
//
//
//double GetDistance(Node* nodeA, Node* nodeB)
//{
//	int dstX = (nodeA->gridX - nodeB->gridX);
//	int dstY = (nodeA->gridY - nodeB->gridY);
//	int dstZ = (nodeA->gridZ - nodeB->gridZ);
//
//	return (sqrt(dstX * dstX + dstY * dstY + dstZ * dstZ));
//}
//
//
//
//vector<vector<int> > Scene::aStarSearch(vector<vector<vector<int> > > grid, vector<int> startVec, vector<int> endVec) {
//
//	vector<vector<int> > helloa;
//
//
//
//	if (isValid(startVec[0], startVec[1], startVec[2]) == false)
//	{
//		printf("Source is invalid\n");
//		// return; 
//	}
//
//	if (isValid(endVec[0], endVec[1], endVec[2]) == false)
//	{
//		printf("Destination is invalid\n");
//		// return; 
//	}
//
//	if (isUnBlocked(grid, startVec[0], startVec[1], startVec[2]) == true ||
//		isUnBlocked(grid, endVec[0], endVec[1], endVec[2]) == true)
//	{
//		printf("Source or the destination is blocked\n");
//		// return; 
//	}
//
//	if ((startVec[0] == endVec[0] && startVec[1] == endVec[1] && startVec[2] == endVec[2]))
//	{
//		printf("We are already at the destination\n");
//		// return; 
//	}
//
//	priority_queue <Node*, vector<Node*>, compareFValue> openSet;
//
//	//int openSetMap[ROW][COL][HEI];
//	vector<vector<vector<int> > > openSetMap;
//	vector<vector<vector<int> > > closedSetMap;
//	for (int i = 0; i < ROW; i++)
//	{
//		vector<vector<int> > tempTwo;
//		for (int j = 0; j < COL; j++)
//		{
//			vector<int> tempOne;
//			for (int k = 0; k < HEI; k++)
//			{
//				tempOne.push_back(0);
//			}
//			tempTwo.push_back(tempOne);
//		}
//		openSetMap.push_back(tempTwo);
//		closedSetMap.push_back(tempTwo);
//	}
//	//memset(openSetMap, 0, totalLenkgth);
//
//	//int closedSetMap[ROW][COL][HEI];
//	//vector<vector<vector<int> > > closedSetMap;
//	//for (int i = 0; i < ROW; i++)
//	//{
//	//	vector<vector<int> > tempTwo;
//	//	for (int j = 0; j < COL; j++)
//	//	{
//	//		vector<int> tempOne;
//	//		for (int k = 0; k < HEI; k++)
//	//		{
//	//			tempOne.push_back(0);
//	//		}
//	//		tempTwo.push_back(tempOne);
//	//	}
//	//	closedSetMap.push_back(tempTwo);
//	//}
//	//memset(closedSetMap, 0, totalLength);
//
//
//	Node* startNode = new Node(startVec[0], startVec[1], startVec[2]);
//
//	Node* endNode = new Node(endVec[0], endVec[1], endVec[2]);
//
//	startNode->gCost = 0.0;
//	startNode->hCost = 0.0;
//	//startNode->parent = NULL;
//
//	openSet.push(startNode);
//	openSetMap[startVec[0]][startVec[1]][startVec[2]] = 1;
//
//	while (!openSet.empty()) {
//
//		Node* node = openSet.top();
//
//		openSetMap[node->gridX][node->gridY][node->gridZ] = 0;
//		openSet.pop();
//
//		closedSetMap[node->gridX][node->gridY][node->gridZ] = 1;
//
//		if (node->gridX == endNode->gridX && node->gridY == endNode->gridY && node->gridZ == endNode->gridZ) {
//
//			vector<vector<int> > result = RetracePath(startNode, node);
//			//delete(startNode);
//			//delete(endNode);
//
//			// if(startNode)	cout<<"\nstill not deleted:"<< startNode->gridX;
//
//			return result;
//			// delete(startNode);
//			// delete
//
//		}
//
//		int i = node->gridX;
//		int j = node->gridY;
//		int k = node->gridZ;
//
//		int vi, vj, vk;
//
//		vector<int> dx{ -1, -1, -1,  0,  0,  1, 1, 1, 0,-1, -1, -1,  0,  0,  1, 1, 1, 0,-1, -1, -1,  0,  0,  1, 1, 1, 0 };
//		vector<int> dy{ -1,  0,  1, -1,  1, -1, 0, 1, 0, -1,  0,  1, -1,  1, -1, 0, 1, 0, -1,  0,  1, -1,  1, -1, 0, 1, 0 };
//		vector<int> dz{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
//
//		for (int index = 0; index < 27; index++) {
//
//			vi = i + dx[index];
//			vj = j + dy[index];
//			vk = k + dz[index];
//
//			if (isValid(vi, vj, vk) == true) {
//
//				Node* neighbor = new Node(vi, vj, vk);
//
//				if (grid[vi][vj][vk] == 0 or closedSetMap[neighbor->gridX][neighbor->gridY][neighbor->gridZ] == 1) {
//
//					delete(neighbor);
//					continue;
//				}
//
//				double newCostToneighbor = node->gCost + GetDistance(node, neighbor);
//
//				if (newCostToneighbor < neighbor->gCost || openSetMap[vi][vj][vk] == 0) {
//					neighbor->gCost = newCostToneighbor;
//					neighbor->hCost = GetDistance(neighbor, endNode);
//					neighbor->parent = node;
//
//					if (openSetMap[vi][vj][vk] == 0) {
//
//						openSetMap[vi][vj][vk] = 1;
//						openSet.push(neighbor);
//					}
//
//					else {
//						delete(neighbor);
//						// delete(neighbor->parent);
//					}
//
//				}
//			}
//
//		}
//
//	}
//
//}