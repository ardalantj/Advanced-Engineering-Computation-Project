#include "RRT_connect.h"

#include <iostream>

// Planner testing

int main()
{
	// Example array

    int X=100;
    int Y=100;
    int Z=100;

    int ***arr3D = new int**[X];
    for(int i =0; i<X; i++){
       arr3D[i] = new int*[Y];
       for(int j =0; j<Y; j++){
           arr3D[i][j] = new int[Z];
           for(int k = 0; k<Z;k++){
              if(i>=25 && i<75 && j>=25 && j<75 && k>=25 && k<75) arr3D[i][j][k] = 1;
           }
       }
    }

	double *start = new double[3];
	*start = 50;
    *(start+1) = 50;
    *(start+2) = 24;
	double *end = new double[3];
	*end = 50;
    *(end+1) = 50;
    *(end+2) = 76;

	RRT_connect dronePlanner(start, end, arr3D, X, Y, Z);
    int length = 0;
	std::vector<std::vector<double>> plan = dronePlanner.search(100000, 0.1, 1, &length);

	for(int i = 0; i<length; i++)
	{
		double x = plan[i][0];
		double y = plan[i][1];
		double z = plan[i][2];
		std::cout<<"x: "<<x<<", y: "<<y<<", z: "<<z<<std::endl;
	}

    for(int i = 0; i <X; ++i)    {
        for(int j = 0; j < Y; ++j)
        {
            delete[] arr3D[i][j];
        }
        delete[] arr3D[i];
    }

    delete[] arr3D;
    delete[] start;
    delete[] end;
    return 0;
}
