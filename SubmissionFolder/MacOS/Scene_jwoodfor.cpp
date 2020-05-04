#include "Scene_jwoodfor.h"


bool Scene::CheckIfGoodObstacle(float x, float y, float z, float length, float width, float height)
{

	float offset = 4.;

	if (userDesStart[0] >= x - offset && userDesStart[0] <= x + length + offset && userDesStart[1] >= y - offset && userDesStart[1] <= y + height + offset && userDesStart[2] >= z - offset && userDesStart[2] <= z + width + offset)
	{
		return false;
	}

	if (userDesEnd[0] >= x - offset && userDesEnd[0] <= x + length + offset && userDesEnd[1] >= y - offset && userDesEnd[1] <= y + height + offset && userDesEnd[2] >= z - offset && userDesEnd[2] <= z + width + offset)
	{
		return false;
	}

	return true;

}

void Scene::LoadScene()
{

	srand(time(NULL));

	for (int i = 0; i < numObstacles; i++)
	{

		bool goodObstacle = false;

		float oneX = 0.;
		float oneY = 0.;
		float oneZ = 0.;
		float oneL = 1.;
		float oneW = 1.;
		float oneH = 1.;

		while (!goodObstacle)
		{
			oneX = float(rand() % int(backBoxLength - 30) + 5);
			oneY = float(rand() % int(backBoxHeight - 30) + 5);
			oneZ = float(rand() % int(backBoxWidth - 30) + 5);

			oneL = float(rand() % 24 + 5);
			oneW = float(rand() % 24 + 5);
			oneH = float(rand() % 24 + 5);

			if (i == 13)
			{
				int fooasdfa = 1;
			}

			goodObstacle = CheckIfGoodObstacle(oneX, oneY, oneZ, oneL, oneW, oneH);

		}

		int oneR = rand() % 255;
		int oneG = rand() % 255;
		int oneB = rand() % 255;

		Obstacle oneObstacle(oneX, oneY, oneZ, oneL, oneW, oneH, oneR, oneG, oneB);
		obstacles[i] = oneObstacle;
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

}

Scene::Scene(float oneLength, float oneWidth, float oneHeight)
{
	backBoxLength = oneLength;
	backBoxWidth = oneWidth;
	backBoxHeight = oneHeight;

	Volume tempVolume(backBoxLength, backBoxWidth, backBoxHeight);

	volume = tempVolume;

	for (int i = 0; i < 3; i++)
	{
		userDesStart.push_back(0.);
		userDesEnd.push_back(0.);
	}

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

	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAllAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaNoDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaNoSpecularLight);

	switch (desPath)
	{

	case rrt:
	{
		if (!pathRRTCheck)
		{

			volume.ClearPathRRTVect();

			long startTime = glutGet(GLUT_ELAPSED_TIME);

			vector<double> startPoint = userDesStart;
			vector<double> endPoint = userDesEnd;

			RRT_connect dronePlanner(startPoint, endPoint, volume.GetVolumeStates(), volume.GetLength(), volume.GetHeight(), volume.GetWidth());

			int length = 0;
			vector<vector<double> > plan = dronePlanner.search(100000, .1, 1, &length);

			if (plan.size() > 0)
			{
				volume.SetPathRRTVect(plan);

				volume.OffsetPathRRT();

				desPath = none;

				pathRRTCheck = true;

				double rrtPathLength = volume.SumPathRRT();

				double totalTime = (glutGet(GLUT_ELAPSED_TIME) - startTime)/1000.;

				cout << "RRT took " << totalTime << " seconds to calculate. Path length of RRT is: " << rrtPathLength << "\n";
			}

		}
		else
		{
			volume.ClearPathRRTVect();
			pathRRTCheck = false;
		}

		break;
	}

	case astar:
	{
		if (!pathAStarCheck)
		{

			volume.ClearPathAStarVect();

			long startTime = glutGet(GLUT_ELAPSED_TIME);

			vector<double> startPoint = userDesStart;
			vector<double> endPoint = userDesEnd;

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
				volume.SetPathAStarVect(planDouble);

				volume.OffsetPathAStar();

				pathAStarCheck = true;

				double aStarPathLength = volume.SumPathAStar();

				double totalTime = (glutGet(GLUT_ELAPSED_TIME) - startTime)/1000.;

				cout << "AStar took " << totalTime << " seconds to calculate. Path length of AStar is: " << aStarPathLength << "\n";
			}

		}
		else
		{
			volume.ClearPathAStarVect();
			pathAStarCheck = false;
		}

		break;
	}


	}

	desPath = none;

	if (pathRRTCheck)
	{
		volume.DrawPathRRT();
	}
	if (pathAStarCheck)
	{
		volume.DrawPathAStar();
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

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

	//// Visualizing Light Position
	//glPushMatrix();
	//glScalef(1., 1., 1.);
	//glTranslatef(qaLightPosition[0], qaLightPosition[1], qaLightPosition[2]);
	//glutSolidCube(1.);
	//glPopMatrix();

	countTime++;

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

	//// NEED TO PUT IN THE MESHES HERE, ROTATE AND TRANSLATE

	//float rgbaCheckerMain[4] = { 50,50,50,255 };
	//float rgbaCheckerOff[4] = { 50,50,50,255 };
	//float shininessChecker = 60.;

}