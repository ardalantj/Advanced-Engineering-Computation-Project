#pragma once

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>

#include "yssimplesound.h"
#include "Camera_jwoodfor.h"
#include "Volume.h"
#include "Obstacle.h"

#include "Drawing_jwoodfor.h"

#include "RRT_connect.h"


using namespace std;

class Scene
{

private:

	float backBoxWidth = 200.;
	float backBoxHeight = 100.;
	float backBoxLength = 200.;
	float backBoxAnchor[3] = { 0., 0., 0.};
	int backBoxAlpha = 255;
	int backBoxColor3ub[3] = { 200, 200, 200 };

	Volume volume;

	Obstacle obstacles[3];

	long countTime = 0;

public:

	void SetBackBoxAlpha(float alpha) { backBoxAlpha = alpha; }
	float GetBackBoxAlpha() { return backBoxAlpha; }

	void SetBackBoxColor3ub(float r, float g, float b) { backBoxColor3ub[0] = r; backBoxColor3ub[1] = g; backBoxColor3ub[2] = b; }
	int* GetBackBoxColor3ub() { return backBoxColor3ub; }

	void SetBackBoxWidth(float width) { backBoxWidth = width; }
	float GetBackBoxWidth() { return backBoxWidth; }

	void SetBackBoxHeight(float height) { backBoxHeight = height; }
	float GetBackBoxHeight() { return backBoxHeight; }

	void SetBackBoxLength(float length) { backBoxLength = length; }
	float GetBackBoxLength() { return backBoxLength; }

	void SetBackBoxAnchor(float x, float y, float z) { backBoxAnchor[0] = x; backBoxAnchor[1] = y; backBoxAnchor[2] = z;}
	float* GetBackBoxAnchor() { return backBoxAnchor; }

	void DrawBackground();

	Scene(float oneLength, float oneWidth, float oneHeight);

	void RunScene(Camera theCamera);

};

