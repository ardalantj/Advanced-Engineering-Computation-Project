//
//  Vehicle.hpp
//  AirViz
//
//  Created by Ardalan TJ on 4/7/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

class Vehicle
{

public:
    // Default constructor
    Vehicle();
    ~Vehicle();
    
    // Function to extract information about the vehicle: index mapping is 0 -> x, 1 -> y, 2 -> z
    double get_position(int index);
    double get_speed(int index);
    double get_attitude(int index);
    double get_motor_rpm(int index);
    double get_up_vector(int index);
    double get_direction_vector(int index);

    // functions to change and test simulation parameters
    bool startSimulation();
    bool stopSimulation();
    bool simulationRunning();
    
private:
    // These vectors describe the exact state of the quadrotor. In reality this should not be used by the controller as it would mean the perfect knowledge of the state, but we assume we have access to that for simplicity
    
    Vector3d x;
    Vector3d xdot;
    Vector3d xddot;
    Vector3d theta;
    Vector3d thetadot;
    
   // For the renderer it is more convinient to use up- and direction-vector.
    // The direction vector is the vector (1 0 0) in the body frame transformed into the earth frame.
    
    // The up vector is the vector (0 0 1) in the body frame transformed into the earth frame.
    Vector3d up_vector;
    Vector3d direction_vector;
}
#endif /* Vehicle_hpp */
