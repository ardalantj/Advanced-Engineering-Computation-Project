#ifndef RRT_CON
#define RRT_CON

#ifndef RRT_CONNECT_H
#define RRT_CONNECT_H


#include<math.h>
#include<map>
#include<unordered_map>
#include<vector>
#include<utility>
#include<stdlib.h>
#include<time.h>
#include<limits>

/*
	RRT-Connect
	- generate random point
	- nearest to tree A
	- extend from tree A by epsilon or until obstacle
	- extend from B till new node or obstacle
	- check if nodes equal --> if goal --> concatenate plan
	- else switch and repeat
*/


class RRT_connect{
	public:
		RRT_connect(double* start, double* goal, int*** map, int x, int y, int z);
		~RRT_connect();

		double eucDistance(double* A, double* B);
		void randomConfig(double* randC);

        int getVertices();
        double getCost();

        std::vector<std::vector<double>> search(int sampleSize, double interp, double epsilon, int* length);

        void reset();

    protected:
        void localPlanner_connect(double* randC, double* near);
        void localPlanner_extend(double* randC, double* near);
		bool isGoal(std::vector<std::vector<double>> &plan, int* length);
        double* nearestNeighbor(double* point);
        bool isValidPosition(double* point);

	private:
	    double* m_start; // size of dof
	    double* m_goal;
	    double* m_newChild_a;
	    double* m_newChild_b;
	    int*** m_map;
	    double mapMax;
	    int X, Y, Z;

	    double m_interp;
	    double m_epsilon;

	    int vertices;
	    double cumCost;
	    bool change; // Switch to change tree expansion

	    std::unordered_map<double*, double*> tree_a; // child --> parent
	    std::unordered_map<double*, double*> tree_b; // child --> parent
	    std::unordered_map<double*, int> tree_length_a; // # of vertices away from root
	    std::unordered_map<double*, int> tree_length_b; // # of vertices away from root
};

#endif // RRT_CONNECT_H



#endif 