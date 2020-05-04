#pragma once

// Here is where we set the draw distance
// NOTE: This is across all classes
const int drawDist = 10000;

class Camera
{

private:
	
	// Camera locations and angles
	float x;
	float y;
	float z;
	float ax;
	float ay;
	float az;
	
public:

	// Initialize them all to 0 on construction
	Camera()
	{
		x = 0.;
		y = 0.;
		z = 0.;
		ax = 0.;
		ay = 0.;
		az = 0.;
	}

	// Set all x,y,z at once
	void setCameraXYZ(float camX, float camY, float camZ)
	{
		x = camX;
		y = camY;
		z = camZ;
	};

	// Set all angles at once
	void setCameraaXaYaZ(float camX, float camY, float camZ)
	{
		ax = camX;
		ay = camY;
		az = camZ;
	};

	// Setting individual values
	void setCameraX(float camX) { x = camX; }
	void setCameraY(float camY) { y = camY; }
	void setCameraZ(float camZ) { z = camZ; }
	void setCameraaX(float camX) { ax = camX; }
	void setCameraaY(float camY) { ay = camY; }
	void setCameraaZ(float camZ) { az = camZ; }

	// Getting individual values
	float getCameraX() { return x; }
	float getCameraY() { return y; }
	float getCameraZ() { return z; }
	float getCameraaX() { return ax; }
	float getCameraaY() { return ay; }
	float getCameraaZ() { return az; }

};

