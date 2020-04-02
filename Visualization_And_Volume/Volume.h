#pragma once

#include <vector>
#include <GL/glut.h>

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
		vector<vector<float>> xyz;
		vector<vector<float>> centerXYZ;
		vector<float> pathStart = { 0,0,0 };
		vector<float> pathEnd = { 0,0,0 };
	};



private:

	float height = 0.;
	float length = 0.;
	float width = 0.;
	double PI = 3.141562653;

	vector<vector<vector<volCube>>> vol;
	path bestPath;

	void DrawSphere(double offX, double offY, double offZ, double r, int lats, int longs, float red, float green, float blue);






public:

	

	void SetHeight(float oneHeight) { height = oneHeight; }
	float GetHeight() { return height; }

	void SetLength(float oneLength) { length = oneLength; }
	float GetLength() { return length; }

	void SetWidth(float oneWidth) { width = oneWidth; }
	float GetWidth() { return width; }

	void SetOneVol(volCube oneVolCube, int x, int y, int z) { vol[x][y][z] = oneVolCube; }
	volCube* GetVolCube(int x, int y, int z) { return &vol[x][y][z]; }

	void SetPath(path onePath) { bestPath = onePath; }
	path* GetPath() { return &bestPath; }

	Volume();

	Volume(float oneLength, float oneWidth, float oneHeight);

	void OffsetPath();

	void DrawPath();

};

