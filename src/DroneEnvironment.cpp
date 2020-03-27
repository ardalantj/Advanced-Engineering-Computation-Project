#include "polygonalmesh.h"
#include <vector>
#include <iostream>

class DroneEnvironment {
public:
	std::vector <YsVec3> pointArray; // contains all of the points in the drone environment
	std::vector <bool> accessArray; // contains data for which points can be accessed by the drone
	float x, y, z; // the dimensions of the drone environment
	float dx, dy, dz; // the resolution between points
	int xPoints, yPoints, zPoints; // the total number of points in each dimension

	DroneEnvironment() {}; // empty constructor - DON'T USE
	~DroneEnvironment() {
		pointArray.clear();
		accessArray.clear();
		pointArray.~vector();
		accessArray.~vector();
	}
	DroneEnvironment(int x, int y, int z, float dx, float dy, float dz) // x,y,z define dimensions; dx,dy,dz define resolution
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->dx = dx;
		this->dy = dy;
		this->dz = dz;
		this->xPoints = x / dx;
		this->yPoints = y / dy;
		this->zPoints = z / dz;

		for (float i = 0; i <= x; i += dx) {
			for (float j = 0; j <= y; j += dy) {
				for (float k = 0; k <= z; k += dz) {
					this->pointArray.push_back(YsVec3(i, j, k));
					this->accessArray.push_back(true);
				}
			}
		}
	}
	void printArray(void) // prints all points in pointArray
	{
		for (auto point : pointArray)
		{
			std::cout << point.x() << "," << point.y() << "," << point.z() << std::endl;
		}
	}
	int getPointIndex(YsVec3 point) // returns index of a point in pointVertex
	{
		if (point.x() > this->x || point.y() > this->y || point.z() > this->z) { return -1; } // point not within environment bounds
		else
		{
			int xIndex = point.x() / dx * (this->yPoints+1) * (this->zPoints+1);
			int yIndex = point.y() / dy * (this->zPoints+1);
			int zIndex = point.z() / dz;
			std::cout << xIndex + yIndex + zIndex << std::endl;
			return xIndex + yIndex + zIndex;
		}
	}
	YsVec3* getNextX(YsVec3 point) // get pointer to next point along x axis
	{
		if (point.x() + dx > this->x)
		{
			return nullptr;
		}
		else
		{
			int currentPointIndex = this->getPointIndex(point);
			if (currentPointIndex == -1) { return nullptr; }
			YsVec3 a = pointArray[currentPointIndex + (this->yPoints+1) * (this->zPoints+1)];
			std::cout << a.x() << "," << a.y() << "," << a.z() << std::endl;
			return &pointArray[currentPointIndex + (this->yPoints + 1) * (this->zPoints + 1)];
		}
	}
	YsVec3* getPrevX(YsVec3 point) // get pointer to prev point along x axis
	{
		if (point.x() - dx < 0)
		{
			return nullptr;
		}
		else
		{
			int currentPointIndex = this->getPointIndex(point);
			if (currentPointIndex == -1) { return nullptr; }
			YsVec3 a = pointArray[currentPointIndex - (this->yPoints+1) * (this->zPoints+1)];
			std::cout << a.x() << "," << a.y() << "," << a.z() << std::endl;
			return &pointArray[currentPointIndex - (this->yPoints + 1) * (this->zPoints + 1)];
		}
	}
	YsVec3* getNextY(YsVec3 point) // get pointer to next point along y axis
	{
		if (point.y() + dy > this->y)
		{
			std::cout << "nullptr" << std::endl;
			return nullptr;
		}
		else
		{
			int currentPointIndex = this->getPointIndex(point);
			if (currentPointIndex == -1) { return nullptr; }
			YsVec3 a = pointArray[currentPointIndex + (this->zPoints+1)];
			std::cout << a.x() << "," << a.y() << "," << a.z() << std::endl;
			return &pointArray[currentPointIndex + (this->zPoints + 1)];
		}
	}
	YsVec3* getPrevY(YsVec3 point) // get pointer to prev point along y axis
	{
		if (point.y() - dy < 0)
		{
			std::cout << "nullptr" << std::endl;
			return nullptr;
		}
		else
		{
			int currentPointIndex = this->getPointIndex(point);
			if (currentPointIndex == -1) { return nullptr; }
			YsVec3 a = pointArray[currentPointIndex - (this->zPoints + 1)];
			std::cout << a.x() << "," << a.y() << "," << a.z() << std::endl;
			return &pointArray[currentPointIndex - (this->zPoints + 1)];
		}
	}
	YsVec3* getNextZ(YsVec3 point) // get pointer to next point along z axis
	{
		if (point.z() + dz > this->z)
		{
			std::cout << "nullptr" << std::endl;
			return nullptr;
		}
		else
		{
			int currentPointIndex = this->getPointIndex(point);
			if (currentPointIndex == -1) { return nullptr; }
			YsVec3 a = pointArray[currentPointIndex + 1];
			std::cout << a.x() << "," << a.y() << "," << a.z() << std::endl;
			return &pointArray[currentPointIndex + 1];
		}
	}
	YsVec3* getPrevZ(YsVec3 point) // get pointer to prev point along z axis
	{
		if (point.z() - dz < 0)
		{
			std::cout << "nullptr" << std::endl;
			return nullptr;
		}
		else
		{
			int currentPointIndex = this->getPointIndex(point);
			if (currentPointIndex == -1) { return nullptr; }
			YsVec3 a = pointArray[currentPointIndex - 1];
			std::cout << a.x() << "," << a.y() << "," << a.z() << std::endl;
			return &pointArray[currentPointIndex - 1];
		}
	}
	bool isAccessible(YsVec3 point) // check whether the point can be accessed by the drone
	{
		int currentPointIndex = this->getPointIndex(point);
		if (currentPointIndex == -1) { return false; }
		return this->accessArray[currentPointIndex];
	}
	void setAccess(YsVec3 point, bool access) // change the access of a point
	{
		int currentPointIndex = this->getPointIndex(point);
		if (currentPointIndex == -1) { return; }
		accessArray[currentPointIndex] = access;
		return;
	}
	void makeBoxObstacle(YsVec3 point1, YsVec3 point2) // creates a box-shape obstacle spanning point1 to point2
	{
		float temp;
		if (this->getPointIndex(point1) == -1 || this->getPointIndex(point2) == -1) // make sure both points are in environment
		{
			std::cout << "Make sure both points are within the drone environment" << std::endl;
			return;
		}
		// set up for the loops
		if (point1.x() > point2.x())
		{
			temp = point1.x();
			point1.SetX(point2.x());
			point2.SetX(temp);
		}
		if (point1.y() > point2.y())
		{
			temp = point1.y();
			point1.SetY(point2.y());
			point2.SetY(temp);
		}
		if (point1.z() > point2.z())
		{
			temp = point1.z();
			point1.SetZ(point2.z());
			point2.SetZ(temp);
		}

		for (float i = point1.x(); i <= point2.x(); i += dx)
		{
			for (float j = point1.y(); j <= point2.y(); j += dy)
			{
				for (float k = point1.z(); k <= point2.z(); k += dz)
				{
					this->setAccess(YsVec3(i, j, k), false);
				}
			}
		}
		std::cout << point1.x() << "," << point1.y() << "," << point1.z() << " -> " << point2.x() << "," << point2.y() << "," << point2.z() << std::endl;
		// OpenGL METHODS GO HERE TO VISUALIZE THE OBSTACLE
		return;
	}
	void clearObstacles()
	{
		for (auto i : this->accessArray)
		{
			i = true;
		}
	}
};