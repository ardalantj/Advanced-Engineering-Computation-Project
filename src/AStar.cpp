#include<bits/stdc++.h> 
#include<iostream>
using namespace std; 

#define ROW 3 
#define COL 3
#define HEI 3 

class Node{

	public:

		int gridX;
		int gridY;
		int gridZ;

		double gCost;
		double hCost;

		Node* parent;

		Node(int _gridX, int _gridY, int _gridZ){
			gridX = _gridX; 
			gridY = _gridY;
			gridZ = _gridZ;
		}

		int fCost() const{

			return gCost + hCost;

		}

		bool operator==(const Node& t) const
		    { 
		        if(this->gridX == t.gridX && this->gridY == t.gridY && this->gridZ == t.gridZ){
		        	printf("Comes Here\n");
		        	return true;
		        }
		    }

		bool operator!=(const Node& t) const
		    { 
		        if(!(this->gridX == t.gridX && this->gridY == t.gridY && this->gridZ == t.gridZ)){
		        	return true;
		        }
		    }
};

struct compareFValue{
	bool operator()(Node* p1, Node* p2)
	{
		if (p1->fCost() == p2->fCost()){
			return p1->hCost > p2->hCost;
		}
		return p1->fCost() > p2->fCost(); //> for the lowest element at the top. 
	}
};

vector<vector<int>> RetracePath(Node* startNode, Node* endNode) {
	
	vector<vector<int>> path;
	
	Node* currentnode = endNode;

	currentnode->parent = endNode->parent;

	int i = 0;

	while (!(currentnode->gridX == startNode->gridX && currentnode->gridY == startNode->gridY && currentnode->gridZ == startNode->gridZ)) {
		
		path.push_back({currentnode->gridX, currentnode->gridY, currentnode->gridZ});
		currentnode = currentnode->parent;
		
		i = i + 1;
	}
	
	reverse(path.begin(), path.end());
	
	// for (int i = 0; i < path.size(); i++) 
	// 	printf("\n -> (%d,%d,%d) ", path[i][0], path[i][1], path[i][2]); 
	
	return path;
}

static bool isValid(int row, int col, int hei) 
{ 
	
	return (row >= 0) && (row < ROW) && 
		(col >= 0) && (col < COL)&& 
		(hei >= 0) && (hei < HEI); 
} 

bool isUnBlocked(vector<vector<vector<int>>> grid, int i, int j, int k) 
{ 
	if (grid[i][j][k] == 1) 
		return (true); 
	else
		return (false); 
} 




double GetDistance(Node* nodeA, Node* nodeB) 
{
	int dstX = (nodeA->gridX - nodeB->gridX);
	int dstY = (nodeA->gridY - nodeB->gridY);
	int dstZ = (nodeA->gridZ - nodeB->gridZ);

	return (sqrt(dstX*dstX + dstY*dstY + dstZ*dstZ));
}



vector<vector<int>> aStarSearch(vector<vector<vector<int>>> grid, vector<int> startVec, vector<int> endVec) {

	if (isValid (startVec[0], startVec[1], startVec[2]) == false) 
	{ 
		printf ("Source is invalid\n"); 
		// return; 
	} 

	if (isValid (endVec[0], endVec[1], endVec[2]) == false) 
	{ 
		printf ("Destination is invalid\n"); 
		// return; 
	} 

	if (isUnBlocked(grid, startVec[0], startVec[1], startVec[2]) == false || 
			isUnBlocked(grid, endVec[0], endVec[1], endVec[2]) == false) 
	{ 
		printf ("Source or the destination is blocked\n"); 
		// return; 
	} 

	if ((startVec[0] == endVec[0] && startVec[1] == endVec[1] && startVec[2] == endVec[2])) 
	{ 
		printf ("We are already at the destination\n"); 
		// return; 
	} 

	priority_queue <Node*, vector<Node*>, compareFValue> openSet;

	int openSetMap[ROW][COL][HEI];
	memset(openSetMap, 0, sizeof (openSetMap)); 

	int closedSetMap[ROW][COL][HEI];
	memset(closedSetMap, 0, sizeof (closedSetMap)); 


	Node* startNode = new Node(startVec[0], startVec[1], startVec[2]);
	
	Node* endNode = new Node(endVec[0], endVec[1], endVec[2]);

	startNode->gCost = 0.0;
	startNode->hCost = 0.0;
	startNode->parent = NULL;

	openSet.push(startNode);
	openSetMap[startVec[0]][startVec[1]][startVec[2]] = 1;

	while (!openSet.empty()){

		Node* node = openSet.top();
				
		openSetMap[node->gridX][node->gridY][node->gridZ] = 0;
		openSet.pop();

		closedSetMap[node->gridX][node->gridY][node->gridZ] = 1;

		if (node->gridX == endNode->gridX && node->gridY == endNode->gridY && node->gridZ == endNode->gridZ){
			
			return RetracePath(startNode, node);;
		}

		int i = node->gridX;
		int j = node->gridY;
		int k = node->gridZ;

        int vi, vj, vk;

        vector<int> dx{-1, -1, -1,  0,  0,  1, 1, 1, 0,-1, -1, -1,  0,  0,  1, 1, 1, 0,-1, -1, -1,  0,  0,  1, 1, 1, 0};
        vector<int> dy{-1,  0,  1, -1,  1, -1, 0, 1, 0, -1,  0,  1, -1,  1, -1, 0, 1, 0, -1,  0,  1, -1,  1, -1, 0, 1, 0};
        vector<int> dz{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
		
		for(int index = 0; index < 27; index++){

			vi = i + dx[index];
			vj = j + dy[index];
			vk = k + dz[index];

			if (isValid(vi,vj,vk) == true){

				Node* neighbor = new Node(vi,vj,vk);

				if (grid[vi][vj][vk] == 0 or closedSetMap[neighbor->gridX][neighbor->gridY][neighbor->gridZ] == 1){

					continue;
				}

				double newCostToneighbor = node->gCost + GetDistance(node, neighbor);

				if (newCostToneighbor < neighbor->gCost || openSetMap[vi][vj][vk] == 0) {
					neighbor->gCost = newCostToneighbor;
					neighbor->hCost = GetDistance(neighbor, endNode);
					neighbor->parent = node;

					if (openSetMap[vi][vj][vk] == 0){
						
						openSetMap[vi][vj][vk] = 1;						
						openSet.push(neighbor);
					}

				}
			}

		}

	}

}


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