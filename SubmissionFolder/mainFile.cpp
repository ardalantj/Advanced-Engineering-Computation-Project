#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


#include "Camera_jwoodfor.h"
#include "Scene_jwoodfor.h"





using namespace std;



// Camera object used to store its information between scenes
float scaleMove = 2.0f;
float deltaAngleXZ = 0.0f;
float deltaAngleY = 0.0f;
float deltaMoveFB = 0;
float deltaMoveLR = 0;
float deltaMoveUD = 0;
unsigned char keyPressed = 0;
int xOrigin = -1;
int yOrigin = -1;
float angleXZ = 0.0f;
float angleY = 0.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float x = 50.0f, y = 50.0f, z = 72.5f;
Camera theCamera;

// Volume for evaluation
float length = 200.;
float width = 200.;
float height = 100.;

// Scenes are made in separate classes
Scene scene(length, width, height);


// Path Type value
//enum pathType { none, rrt, astar};

int passedTime;

// This sets up the camera settings as well as handling resizing the window 
// (technically don't need since we won't be resizing? but I'm keeping this for a template for personal projects)
void changeSize(int w, int h) {

	float screenRatio = w * 1.0 / h;

	// Change to setting camera "lens" values
	glMatrixMode(GL_PROJECTION);

	// Clears matrix to identity matrix
	glLoadIdentity();

	// Setting the window to draw in entirety based upon window size
	glViewport(0, 0, w, h);

	// Setting the perspective (fov, ratio, znear, zfar)
	gluPerspective(70., screenRatio, 0.1, drawDist);

	// Going back to setting camera position values
	glMatrixMode(GL_MODELVIEW);
}

//// Code borrowed from Nestor for loading sound
//void loadSound()
//{
//	char fName[256] = "Nightfall by RyoX.wav";
//
//	if (YSOK != demoSound.LoadWav(fName))
//	{
//		cout << "Failed to read sound file " << fName << endl;
//		soundOK = false;
//	}
//	else
//		soundOK = true;
//
//}




void processNormalKeys(unsigned char key, int xx, int yy) {
	keyPressed = key;

	switch (key)
	{
	case 27:
	{
		exit(0);
	}
	case 'w':
	case 'W':
	{
		deltaMoveFB = scaleMove;
		break;
	}
	case 's':
	case 'S':
	{
		deltaMoveFB = -scaleMove;
		break;
	}
	case 'a':
	case 'A':
	{
		deltaMoveLR = -scaleMove;
		break;
	}
	case 'd':
	case 'D':
	{
		deltaMoveLR = scaleMove;
		break;
	}
	case 'q':
	case 'Q':
	{
		deltaMoveUD = -scaleMove;
		break;
	}
	case 'e':
	case 'E':
	{
		deltaMoveUD = scaleMove;
		break;
	}
	case 'r':
	case 'R':
	{
		scene.SetDesPathType(rrt);
		break;
	}
	case 't':
	case 'T':
	{
		scene.SetDesPathType(astar);
		break;
	}
	case 'n':
	case 'N':
	{
		scene.SetDesPathType(clear);
		//scene.SetCurrPathType(none);
		break;
	}

	}


}

void releaseProcessNormalKeys(unsigned char key, int xx, int yy) {

	switch (key)
	{
	case 'w':
	case 'W':
	{
		deltaMoveFB = 0;
		break;
	}
	case 's':
	case 'S':
	{
		deltaMoveFB = 0;
		break;
	}
	case 'a':
	case 'A':
	{
		deltaMoveLR = 0;
		break;
	}
	case 'd':
	case 'D':
	{
		deltaMoveLR = 0;
		break;
	}
	case 'q':
	case 'Q':
	{
		deltaMoveUD = 0;
		break;
	}
	case 'e':
	case 'E':
	{
		deltaMoveUD = 0;
		break;
	}


	}
}

void pressKey(int key, int xx, int yy) {
	//cout << key << endl;
	//switch (key) {
	//case GLUT_KEY_UP:
	//{
	//	deltaMoveFB = 1.f;
	//	break;
	//}
	//case GLUT_KEY_DOWN:
	//{
	//	deltaMoveFB = -1.f;
	//	break;
	//}
	//case GLUT_KEY_LEFT:
	//{
	//	deltaMoveLR = 1.f;
	//	break;
	//}
	//case GLUT_KEY_RIGHT:
	//{
	//	deltaMoveLR = -1.f;
	//	break;
	//}

	//}
}

void releaseKey(int key, int x, int y) {

	//switch (key) {
	//case GLUT_KEY_UP: deltaMoveFB = 0; break;
	//case GLUT_KEY_DOWN: deltaMoveFB = 0; break;
	//case GLUT_KEY_LEFT: deltaMoveLR = 0; break;
	//case GLUT_KEY_RIGHT: deltaMoveLR = 0; break;
	//}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0 || yOrigin >= 0) {

		// update deltaAngle
		deltaAngleXZ = (x - xOrigin) * 0.001f;
		deltaAngleY = (y - yOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angleXZ + deltaAngleXZ);
		lz = -cos(angleXZ + deltaAngleXZ);
		ly = -sin(angleY + deltaAngleY);
	}
	theCamera.setCameraaXaYaZ(lx, ly, lz);
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angleXZ += deltaAngleXZ;
			angleY += deltaAngleY;
			xOrigin = -1;
			yOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
}

// Camera movements
void computePosFB(float deltaMove) {

	if (x < scene.GetBackBoxLength() - 1 && x > 1 && z < scene.GetBackBoxWidth() - 1 && z > 1)
	{
		x += deltaMove * lx * 0.3f;
		z += deltaMove * lz * 0.3f;

		theCamera.setCameraX(x);
		theCamera.setCameraZ(z);
	}

	if (x < 1)
	{
		x = 1 + .1;
	}
	else if (x > scene.GetBackBoxLength() - 1)
	{
		x = scene.GetBackBoxLength() - 1 - .1;
	}

	if (z < 1)
	{
		z = 1.1;
	}
	else if (z > scene.GetBackBoxWidth() - 1)
	{
		z = scene.GetBackBoxWidth() - 1 - .1;
	}

}
void computePosLR(float deltaMove) {

	if (x < scene.GetBackBoxLength() - 1 && x > 1 && z < scene.GetBackBoxWidth() - 1 && z > 1)
	{
		x += -deltaMove * lz * 0.3f;
		z += deltaMove * lx * 0.3f;

		theCamera.setCameraX(x);
		theCamera.setCameraZ(z);
	}

	if (x < 1)
	{
		x = 1 + .1;
	}
	else if (x > scene.GetBackBoxLength() - 1)
	{
		x = scene.GetBackBoxLength() - 1 - .1;
	}

	if (z < 1)
	{
		z = 1.1;
	}
	else if (z > scene.GetBackBoxWidth() - 1)
	{
		z = scene.GetBackBoxWidth() - 1 - .1;
	}

}
void computePosUD(float deltaMove) {

	if (y < scene.GetBackBoxHeight() - 1 && y > 1)
	{
		y += deltaMove * 0.3f;
		theCamera.setCameraY(y);
	}

	if (y < 1)
	{
		y = 1 + .1;
	}
	else if (y > scene.GetBackBoxHeight() - 1)
	{
		y = scene.GetBackBoxHeight() - 1 - .1;
	}
}





// The bulk of the action
// NOTE: Right now, I have this set as both the display and idle function
// for some reason, doing this is giving me better fps for my terribly optimized code
// despite it should not be. Need further investigation to implement glutPostRedisplay() properly
void renderScene()
{



	// Set the camera	
	theCamera.setCameraX(x);
	theCamera.setCameraY(y);
	theCamera.setCameraZ(z);

	if (deltaMoveFB)
		computePosFB(deltaMoveFB);
	if (deltaMoveLR)
		computePosLR(deltaMoveLR);
	if (deltaMoveUD)
		computePosUD(deltaMoveUD);

	scene.RunScene(theCamera);

	// Get the current passed time from glut
	// Used for limiting fps to 60 as demo is tied to fps and not time for movement
	passedTime = glutGet(GLUT_ELAPSED_TIME);

	//// Displaying the first scene, scene runs for 56 seconds
	//if (passedTime < 56000)
	//{
	//	// If we havene't started the scene yet, we set the camera position and get the start time
	//	if (!scene1.GetCheckScene())
	//	{
	//		//theCamera.setCameraXYZ(0, 50, 72.5);
	//		//theCamera.setCameraaXaYaZ(1, 0, 0);
	//		scene1.SetCheckScene(true);
	//		scene1.SetSceneStart(glutGet(GLUT_ELAPSED_TIME));
	//	}

	//	// Actually running the scene class
	//	scene1.Scene1Run(passedTime, theCamera);
	//}

	//// Displaying the second scene, scene runs from 57 seconds to 137 seconds
	//else if (passedTime > 57000 && passedTime < 137000)
	//{
	//	// If we havene't started the scene yet, we set the camera position and get the start time
	//	if (!scene2.GetCheckScene())
	//	{
	//		//theCamera.setCameraXYZ(143, 53, -18);
	//		//theCamera.setCameraaXaYaZ(0, 0, 1);
	//		scene2.SetCheckScene(true);
	//		scene2.SetSceneStart(glutGet(GLUT_ELAPSED_TIME));
	//	}

	//	// Actually running the scene class
	//	scene2.Scene2Run(passedTime, theCamera);
	//}

	//// If we are over 139 seconds, we are done so exit out of the demo
	//else if (passedTime > 139000)
	//{
	//	exit(0);
	//}

	// Swap the buffer to draw to screen
	glutSwapBuffers();

	// Used to maintain 60 fps maximum since we are tied to framerate for motion
	int FPS = 60;
	int timeSleep = 1000. / FPS - (glutGet(GLUT_ELAPSED_TIME) - passedTime);
	if (timeSleep > 1)
	{
#ifdef _WIN32
		Sleep(timeSleep - 1);
#else
		sleep(timeSleep / 100. - 1);
#endif
	}
}


bool goodInput(vector<double> oneInput)
{
	if (!(oneInput[0] > 0. and oneInput[0] < length))
	{
		return false;
	}

	if (!(oneInput[1] > 0. and oneInput[1] < height))
	{
		return false;
	}

	if (!(oneInput[2] > 0. and oneInput[2] < width))
	{
		return false;
	}

	return true;
}


// Main loop
int main(int argc, char** argv) {

	// Hiding that pesky console window
	// Setting the program type to window instead of console gave me some sort of error
	// This was the easy way to solve it instead of doing it properly
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);

	if (argc == 7)
	{
		vector<double> userStartPoint;
		vector<double> userEndPoint;

		double startX = floor(atof(argv[1]));
		double startY = floor(atof(argv[2]));
		double startZ = floor(atof(argv[3]));

		userStartPoint.push_back(startX);
		userStartPoint.push_back(startY);
		userStartPoint.push_back(startZ);

		if (!goodInput(userStartPoint))
		{
			cout << "Error: Invalid Start Point.\nX must be between 0 and 200.\nY must be between 0 and 100.\nZ must be between 0 and 200.";
			exit(10);
		}

		double endX = floor(atof(argv[4]));
		double endY = floor(atof(argv[5]));
		double endZ = floor(atof(argv[6]));

		userEndPoint.push_back(endX);
		userEndPoint.push_back(endY);
		userEndPoint.push_back(endZ);

		if (!goodInput(userEndPoint))
		{
			cout << "Error: Invalid End Point.\nX must be between 0 and 200.\nY must be between 0 and 100.\nZ must be between 0 and 200.";
			exit(10);
		}

		scene.SetUserDesStart(userStartPoint);
		scene.SetUserDesEnd(userEndPoint);
	}
	else
	{
		cout << "Not enough input arguments. Requires 6. StartX StartY StartZ EndX EndY EndZ";
		exit(10);
	}

	// Loading the scenes
	scene.LoadScene();
	//scene2.Scene2Load();
	//scene1.Scene1Load();

	// Initialize glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1600, 900);

	// Creating the window
	glutCreateWindow("AEC Project");

	// Defining reshape function
	glutReshapeFunc(changeSize);

	// Defining display and idle functions
	// NOTE: I know this is wrong, but it gave me best FPS
	// Still looking into better implementation for my own projects
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	// Key Processing
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(releaseProcessNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL things I am enabling and setting
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//glOrtho(-250, 250, -250, 250, -250, 250);

	// Setting up Lighting
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
	GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };
	GLfloat qaSpecularLight[] = { 1.,1.,1.,1. };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	theCamera.setCameraXYZ(int(length / 2), int(height * 2), int(width / 2));
	theCamera.setCameraaXaYaZ(0, -1, 0);

	gluLookAt(theCamera.getCameraX(), theCamera.getCameraY(), theCamera.getCameraZ(),
		theCamera.getCameraaX() + theCamera.getCameraX(), theCamera.getCameraaY() + theCamera.getCameraY(), theCamera.getCameraaZ() + theCamera.getCameraZ(),
		0.0f, 1.0f, 0.0f);

	GLfloat qaLightPosition[] = { 100.,100.,100.,1.0 };
	GLfloat qaLightDirection[] = { 0.,1.,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, qaLightDirection);

	theCamera.setCameraXYZ(x, y, z);
	theCamera.setCameraaXaYaZ(lx, ly, lz);


	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;

}
