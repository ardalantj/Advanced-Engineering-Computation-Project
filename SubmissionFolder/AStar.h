#pragma once
#ifdef _WIN32
#include <queue>
#else
#include<bits/stdc++.h> 
#endif
//#include<bits/stdc++.h> 
//#include<iostream>
//#include<vector>
//
//
//using namespace std;
//
//#define ROW 200
//#define COL 100
//#define HEI 200 
//
//class Node {
//
//public:
//
//	int gridX;
//	int gridY;
//	int gridZ;
//
//	double gCost;
//	double hCost;
//
//	Node* parent;
//
//	Node(int _gridX, int _gridY, int _gridZ);
//
//	int fCost() const;
//
//	bool operator==(const Node& t) const;
//
//	bool operator!=(const Node& t) const;
//};
//
//struct compareFValue {
//	bool operator()(Node* p1, Node* p2)
//	{
//		if (p1->fCost() == p2->fCost()) {
//			return p1->hCost > p2->hCost;
//		}
//		return p1->fCost() > p2->fCost(); //> for the lowest element at the top. 
//	}
//};
//

//
//
//// int main(){
//
//// 	vector<vector<vector<int>>> grid = {{{1,1,1},{1,1,1}, {1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}}, 
//// 									{{1,1,1},{1,1,1}, {1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}}, 
//// 									{{1,1,1},{1,1,1}, {1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}}
//// 									};
//
//// 	vector<int> src({0,0,0});
//// 	vector<int> dest({2,2,2});
//
//// 	aStarSearch(grid, src, dest); 
//
//// 	return(0); 
//
//// }


using namespace std;

#define ROW 100 
#define COL 100
#define HEI 100

class Node {

public:

	int gridX;
	int gridY;
	int gridZ;

	double gCost;
	double hCost;

	Node* parent;

	Node(int _gridX, int _gridY, int _gridZ) {
		gridX = _gridX;
		gridY = _gridY;
		gridZ = _gridZ;
	}

	int fCost() const {

		return gCost + hCost;

	}

	~Node()
	{
		// cout<<"\n Destructor called";
	   // delete parent;
	}

	bool operator==(const Node& t) const
	{
		if (this->gridX == t.gridX && this->gridY == t.gridY && this->gridZ == t.gridZ) {
			printf("Comes Here\n");
			return true;
		}
	}

	bool operator!=(const Node& t) const
	{
		if (!(this->gridX == t.gridX && this->gridY == t.gridY && this->gridZ == t.gridZ)) {
			return true;
		}
	}

};

vector<vector<int>> RetracePath(Node* startNode, Node* endNode);
static bool isValid(int row, int col, int hei);
bool isUnBlocked(vector<vector<vector<int>>> grid, int i, int j, int k);
double GetDistance(Node* nodeA, Node* nodeB);
vector<vector<int>> aStarSearch(vector<vector<vector<int>>> grid, vector<int> startVec, vector<int> endVec);

struct compareFValue {
	bool operator()(Node* p1, Node* p2)
	{
		if (p1->fCost() == p2->fCost()) {
			return p1->hCost > p2->hCost;
		}
		return p1->fCost() > p2->fCost(); //> for the lowest element at the top. 
	}
};

// int main(){

// 	vector<vector<vector<int>>> grid = {{{1,1,1},{1,1,1}, {1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}}, 
// 									{{1,1,1},{1,1,1}, {1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}}, 
// 									{{1,1,1},{1,1,1}, {1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}}
// 									};

// 	vector<int> src({0,0,0});
// 	vector<int> dest({2,2,2});

// 	aStarSearch(grid, src, dest); 

// 	return(0); 

// }