#pragma once

#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Drawing_jwoodfor.h"

using namespace std;

class Volume
{

	struct volCube
	{
		float x = 0.;
		float y = 0.;
		float z = 0.;
		float centerX = 0.;
		float centerY = 0.;
		float centerZ = 0.;
		bool blocked = false;
		bool partOfPath = false;
		bool pathStart = false;
		bool pathEnd = false;
	};

	struct path
	{
		vector<vector<double> > xyz;
		vector<vector<double> > centerXYZ;
		vector<double> pathStart;
		vector<double> pathEnd;
	};

private:

	float height = 0.;
	float length = 0.;
	float width = 0.;
	double PI = 3.141562653;

	vector<vector<vector<volCube> > > vol;
	path pathAStar;
	path pathRRT;



public:

	

	void SetHeight(float oneHeight) { height = oneHeight; }
	float GetHeight() { return height; }

	void SetLength(float oneLength) { length = oneLength; }
	float GetLength() { return length; }

	void SetWidth(float oneWidth) { width = oneWidth; }
	float GetWidth() { return width; }

	void SetOneVol(volCube oneVolCube, int x, int y, int z) { vol[x][y][z] = oneVolCube; }
	volCube* GetVolCube(int x, int y, int z) { return &vol[x][y][z]; }

	void SetPathAStar(path onePath) { pathAStar = onePath; }
	path* GetPathAStar() { return &pathAStar; }

	void SetPathAStarVect(vector<vector<double> > inXYZ) { pathAStar.xyz = inXYZ; pathAStar.xyz.push_back(pathAStar.pathEnd); pathAStar.xyz.insert(pathAStar.xyz.begin(), pathAStar.pathStart); }
	vector<vector<double> > GetPathpathAStarVect() { return pathAStar.xyz; }

	void ClearPathAStarVect() { pathAStar.centerXYZ.clear(); pathAStar.xyz.clear(); }


	void SetPathRRT(path onePath) { pathRRT = onePath; }
	path* GetPathRRT() { return &pathRRT; }

	void SetPathRRTVect(vector<vector<double> > inXYZ) { pathRRT.xyz = inXYZ; pathRRT.xyz.push_back(pathRRT.pathEnd); pathRRT.xyz.insert(pathRRT.xyz.begin(), pathRRT.pathStart); }
	vector<vector<double> > GetPathpathRRTVect() { return pathRRT.xyz; }

	void ClearPathRRTVect() { pathRRT.centerXYZ.clear(); pathRRT.xyz.clear(); }


	void SetPathVectStartEnd(vector<double>  inStart, vector<double>  inEnd) { pathAStar.pathStart = inStart; pathAStar.pathEnd = inEnd; pathRRT.pathStart = inStart; pathRRT.pathEnd = inEnd; }
	void SetPathVectStart(vector<double>  inStart) { pathAStar.pathStart = inStart; pathRRT.pathStart = inStart; }
	void SetPathVectEnd(vector<double>  inEnd) { pathAStar.pathEnd = inEnd; pathRRT.pathEnd = inEnd; }





	vector<vector<vector<volCube> > > GetVolume() { return vol; }

	vector<vector<vector<int> > > GetVolumeStates();

	Volume();

	Volume(float oneLength, float oneWidth, float oneHeight);

	void OffsetPathAStar();
	void OffsetPathRRT();

	void DrawPathAStar();
	void DrawPathRRT();

	double SumPathRRT();
	double SumPathAStar();

};

