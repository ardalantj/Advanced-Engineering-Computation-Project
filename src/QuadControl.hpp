//
//  QuadControl.hpp
//  AirViz
//
//  Created by Ardalan TJ on 3/24/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#ifndef QuadControl_hpp
#define QuadControl_hpp

#include <stdio.h>

class QuadControl{
    
public:
    
    //Executes control action for dt time step
    VehicleCommand RunControl(float dt, float sim_time);
    
    float AltitudeControl(float posZCmd, float velZCmd, float posZ, float velZ, Quaternion<float> attitude, float accelZCmd, float dt);
    
    //Initializing vehicle parameters and mission specs (Ideally, we would want a config file that this function and pull user entered data from)
    void init();
    
    // controller gains
    float kpPosXY, kpPosZ;
    float kpVelXY, kpVelZ;
    float kpBank, kpYaw;
    float KiPosZ;
    
    // limits & saturations
    float maxAscentRate, maxDescentRate;
    float maxSpeedXY;
    float maxAccelXY;
    float maxTiltAngle;
    float minMotorThrust, maxMotorThrust;
}
#endif /* QuadControl_hpp */
