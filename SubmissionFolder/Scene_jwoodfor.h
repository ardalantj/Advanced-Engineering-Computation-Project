#pragma once

#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <time.h>

#include "Camera_jwoodfor.h"
#include "Volume_jwoodfor.h"
#include "Obstacle_jwoodfor.h"

#include "Drawing_jwoodfor.h"

#include "RRT_connect.h"
#include "AStar.h"

using namespace std;

enum pathType { none, rrt, astar };

class Scene
{

private:

	float backBoxWidth = 200.;
	float backBoxHeight = 100.;
	float backBoxLength = 200.;
	float backBoxAnchor[3] = { 0., 0., 0.};
	int backBoxAlpha = 255;
	int backBoxColor3ub[3] = { 200, 200, 200 };
	
	vector<double> userDesStart;
	vector<double> userDesEnd;

	pathType currPath = none;
	pathType desPath = none;

	Volume volume;

	static const int numObstacles = 4;

	Obstacle obstacles[numObstacles];

	long countTime = 0;

public:

	void SetUserDesStart(vector<double> oneStart) { userDesStart = oneStart; }
	vector<double> GetUserDesStart() { return userDesStart; }

	void SetUserDesEnd(vector<double> oneEnd) { userDesEnd = oneEnd; }
	vector<double> GetUserDesEnd() { return userDesEnd; }

	void SetCurrPathType(pathType onePathType) { currPath = onePathType; }
	pathType GetCurrPathType() { return currPath; }

	void SetDesPathType(pathType onePathType) { desPath = onePathType; }
	pathType GetDesPathType() { return desPath; }

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

	//vector<vector<int> > aStarSearch(vector<vector<vector<int> > > grid, vector<int> startVec, vector<int> endVec);

	void RunScene(Camera theCamera);

};

