#include "RRT_connect.h"

#include <iostream>

// Planner testing

int main()
{

    int X=100;
    int Y=100;
    int Z=100;

    // test map
    std::vector<std::vector<std::vector<int>>>
     arr3D(X, std::vector<std::vector<int>>(Y, std::vector<int>(Z,0)));

    for(int i =0; i<X; i++){
       for(int j =0; j<Y; j++){
           for(int k = 0; k<Z;k++){
              if(i>=25 && i<75 && j>=25 && j<75 && k>=25 && k<75) arr3D[i][j][k] = 1;
           }
       }
    }

  // test start and end
  std::vector<double> start = {50, 50, 20};
  std::vector<double> end = {50, 50, 80};

 // class initialization
	RRT_connect dronePlanner(start, end, arr3D, X, Y, Z);
  int length = 0;
	std::vector<std::vector<double>> plan = dronePlanner.search(100000, 0.1, 1, &length);

  // print plan
	for(int i = 0; i<length; i++)
	{
		double x = plan[i][0];
		double y = plan[i][1];
		double z = plan[i][2];
		std::cout<<"x: "<<x<<", y: "<<y<<", z: "<<z<<std::endl;
	}

    return 0;
}
