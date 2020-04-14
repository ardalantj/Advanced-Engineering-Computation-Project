//RRT-Connect
// Narendran Narasimhan

#include<math.h>
#include<map>
#include<unordered_map>
#include<vector>
#include<utility>
#include<stdlib.h>
#include<time.h>
#include<limits>
#include"RRT_connect.h"
#include<iostream>

#define PI 3.141592654

void RRT_connect::reset(){

}

RRT_connect::RRT_connect(double* start, double* goal, int*** map, int X, int Y, int Z): m_start(start), m_goal(goal),
m_map(map), m_newChild_a(nullptr), m_newChild_b(nullptr), X(X), Y(Y), Z(Z)
{

  tree_a.insert(std::make_pair(m_start, nullptr));
  tree_length_a.insert(std::make_pair(m_start, 0));
  tree_b.insert(std::make_pair(m_goal, nullptr));
  tree_length_b.insert(std::make_pair(m_goal, 0));

  change = true;
  vertices = 0;
  cumCost = 0;
  m_interp = 0.1;
  m_epsilon = 1.5;

  double diag = sqrt(X*X + Y*Y);
  mapMax = sqrt(diag*diag + Z*Z);

}


void RRT_connect::randomConfig(double* randC){

  for(int i=0; i<3; i++){
    double randomNum = (double) -2*mapMax + (double) 5*mapMax*((double)rand()/(double)RAND_MAX);
    randC[i] = randomNum;
  }

}

double* RRT_connect::nearestNeighbor(double* point){

  std::unordered_map<double*, double*>::iterator it;
  double distance = std::numeric_limits<double>::max();

  double placeHolder = 0;
  double* nearestPoint;

  if(change){
    for(it = tree_a.begin(); it != tree_a.end(); it++){
      placeHolder = eucDistance(it->first, point);

      if(distance > placeHolder){
        distance = placeHolder;
        nearestPoint = it->first;
      }
      placeHolder = 0;
    }
  }
  else{
    for(it = tree_b.begin(); it != tree_b.end(); it++){
      placeHolder = eucDistance(it->first, point);
      if(distance > placeHolder){
        distance = placeHolder;
        nearestPoint = it->first;
      }
      placeHolder = 0;
    }
  }

  return nearestPoint; // address of closest point in tree
}

bool RRT_connect::isValidPosition(double* point){

  if(point[0]<0 || point[0]>=X || point[1]<0 || point[1]>=Y ||point[2]<0 || point[2]>=Z) return 1;

  int x = (int) round(point[0]);
  int y = (int) round(point[1]);
  int z = (int) round(point[2]);

  return m_map[x][y][z];
}


void RRT_connect::localPlanner_extend(double* randC, double* near){

  double distance = eucDistance(randC, near);

  int numofsamples = (int)(distance/m_interp); // number of points to interpolate/check
  double newPoint[3];
  double oldPoint[3]; // point to initial point
  int counter = 0;

  for(int i = 0; i < numofsamples; i++){

    for(int j = 0; j < 3; j++){
      oldPoint[j] = newPoint[j];
      newPoint[j] = near[j] + (randC[j] - near[j])*((double)(i+1)/(double)numofsamples);
    }
    if(isValidPosition(newPoint)){
      if(counter == 0) break;

      double* addPoint = new double[3];

      for(int j = 0; j<3; j++){
        addPoint[j] = oldPoint[j];
      }
      if(change){

        m_newChild_a = addPoint;

        tree_a.insert(std::make_pair(addPoint, near));
        tree_length_a.insert(std::make_pair(addPoint, tree_length_a[near] + 1));
        break;
      }
      else{
        m_newChild_b = addPoint;
        tree_b.insert(std::make_pair(addPoint, near));
        tree_length_b.insert(std::make_pair(addPoint, tree_length_b[near] + 1));
        break;
      }
    }

    else if(eucDistance(near, newPoint) >= m_epsilon){

      if(counter == 0) break;
      double* addPoint = new double[3];
      for(int j = 0; j<3; j++){
        addPoint[j] = oldPoint[j];

      }
      if(change){
        m_newChild_a = addPoint;
        tree_a.insert(std::make_pair(addPoint, near));
        tree_length_a.insert(std::make_pair(addPoint, tree_length_a[near] + 1));
        break;
      }
      else{
        m_newChild_b = addPoint;
        tree_b.insert(std::make_pair(addPoint, near));
        tree_length_b.insert(std::make_pair(addPoint, tree_length_b[near] + 1));
        break;
      }
    }
    counter++;
  }

}

void RRT_connect::localPlanner_connect(double* randC, double* near){

  double distance = eucDistance(randC, near);

  int numofsamples = (int)(distance/m_interp); // number of points to interpolate/check per distance

  double newPoint[3];
  double oldPoint[3];
  int counter = 0;

  for(int i = 0; i < numofsamples; i++){

    for(int j = 0; j < 3; j++){
      oldPoint[j] = newPoint[j];
      newPoint[j] = near[j] + (randC[j] - near[j])*((double)(i+1)/(double)numofsamples);
    }

    if(isValidPosition(newPoint)){
      if(counter == 0) break;
      double* addPoint = new double[3];
      for(int j = 0; j<3; j++){
        addPoint[j] = oldPoint[j];

      }

      if(change){
        m_newChild_a = addPoint;
        tree_a.insert(std::make_pair(addPoint, near));
        tree_length_a.insert(std::make_pair(addPoint, tree_length_a[near] + 1));
        break;
      }
      else{
        m_newChild_b = addPoint;
        tree_b.insert(std::make_pair(addPoint, near));
        tree_length_b.insert(std::make_pair(addPoint, tree_length_b[near] + 1));
        break;
      }
    }

    if(eucDistance(newPoint, randC) <= 1.5*m_interp && !change){

      double* addPoint = new double[3];
      for(int j = 0; j<3; j++){
        addPoint[j] = randC[j];

      }
      m_newChild_b = addPoint;
      tree_b.insert(std::make_pair(addPoint, near));
      tree_length_b.insert(std::make_pair(addPoint, tree_length_b[near] + 1));
      break;
    }

    if(eucDistance(newPoint, randC) <= 1.5*m_interp && change){

      double* addPoint = new double[3];
      for(int j = 0; j<3; j++){
        addPoint[j] = randC[j];

      }
      m_newChild_a = addPoint;

      tree_a.insert(std::make_pair(addPoint, near));
      tree_length_a.insert(std::make_pair(addPoint, tree_length_a[near] + 1));
      break;
    }

    counter++;
  }

}

bool RRT_connect::isGoal(std::vector<std::vector<double>> &plan, int* length){
  // check if new point is goal
  int check = 0;
  bool goalReached = false;

  for(int i = 0; i < 3; i++){
    if(m_newChild_a[i] != m_newChild_b[i]) continue;
    check++;
  }

  // return plan if goal reached
  if(check == 3){
    vertices = tree_a.size() + tree_b.size();
    goalReached = true;
    int length1 = tree_length_a[m_newChild_a]; // number of samples till goal reached
    int length2 = tree_length_b[m_newChild_b];
    *length = length1 + length2;

    //*plan = (double**) malloc((length1+length2)*sizeof(double*));

    double* backtrack = m_newChild_a; // backtracking placeholder

    for(int i = (length1)-1; i >= 0; i--){
          //(*plan)[i] = (double*) malloc(3*sizeof(double));
          //for(int j = 0; j < 3; j++){
              //(*plan)[i][j] =  backtrack[j];
          std::vector<double> coord;
          coord.push_back(backtrack[0]);
          coord.push_back(backtrack[1]);
          coord.push_back(backtrack[2]);
          plan.insert(plan.begin(), coord);
          //}
          if(tree_a[backtrack] != nullptr){
            cumCost += eucDistance(backtrack, tree_a[backtrack]);
          }
          backtrack = tree_a[backtrack];

    }
    // now forward track for b
    backtrack = tree_b[m_newChild_b];

    for(int i = (length1); i<*length; i++){
          //(*plan)[i] = (double*) malloc(3*sizeof(double));
          //for(int j = 0; j < 3; j++){
              //(*plan)[i][j] =  backtrack[j];
          std::vector<double> coord;
          coord.push_back(backtrack[0]);
          coord.push_back(backtrack[1]);
          coord.push_back(backtrack[2]);
          plan.push_back(coord);
          //}
          if(tree_b[backtrack] != nullptr) cumCost += eucDistance(backtrack, tree_b[backtrack]);
          backtrack = tree_b[backtrack];

    }
  }

  return goalReached;
}


double RRT_connect::eucDistance(double* A, double* B){
  double placeHolder = 0;
  for(int i = 0; i < 3; i++){
    placeHolder += pow(fabs(A[i] - B[i]),2);
  }
  placeHolder = sqrt(placeHolder);
  return placeHolder;
}

std::vector<std::vector<double>> RRT_connect::search(int sampleSize, double interp, double epsilon, int* length){
  // generate i random samples
  srand(time(0)); // seed for random
  m_epsilon = epsilon;
  m_interp = interp;

  std::vector<std::vector<double>> plan;
  // nearest neighbor flips the switch
  for(int i=0; i<sampleSize; i++){

    if(change){
      double randC[3];

      randomConfig(randC); //place random values into randC

      double* nearestQ = nearestNeighbor(randC); // this is an address of vertex point in heap/tree closest to random point

      localPlanner_extend(randC, nearestQ); // transition validity check

      if(m_newChild_a == nullptr) continue; // if no extension found

      change = false; // flip switch

      double* nearestQ_b = nearestNeighbor(m_newChild_a);
      if(m_newChild_a == nullptr) continue;
      localPlanner_connect(m_newChild_a, nearestQ_b);

      if(isGoal(plan, length)) break;

    }
    else{
      double randC[3];

      randomConfig(randC); //place random values into randC

      double* nearestQ = nearestNeighbor(randC); // this is an address of vertex point in heap/tree closest to random point

      localPlanner_extend(randC, nearestQ); // transition validity check

      if(m_newChild_b == nullptr) continue; // if no extension found

      change = true;

      double* nearestQ_a = nearestNeighbor(m_newChild_b);
  	  if(m_newChild_b == nullptr) continue;
      localPlanner_connect(m_newChild_b, nearestQ_a);

      if(isGoal(plan, length)) break;

    }

  }
  return plan;
}

int RRT_connect::getVertices(){
  return vertices;
}
double RRT_connect::getCost(){
  return cumCost;
}

RRT_connect::~RRT_connect(){
  // delete tree keys except start state
  std::unordered_map<double*, double*>::iterator it_a;
  std::unordered_map<double*, double*>::iterator it_b;

  for(it_a = tree_a.begin(); it_a != tree_a.end(); it_a++){
    if(it_a->first == m_start) continue;
    else{ delete it_a->first;}
  }
  for(it_b = tree_b.begin(); it_b != tree_b.end(); it_b++){
    if(it_b->first == m_goal) continue;
    else{ delete it_b->first;}
  }
}
