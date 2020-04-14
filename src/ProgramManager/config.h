//
//  config.h
//  AirViz
//
//  Created by Ardalan TJ on 4/7/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#ifndef config_h
#define config_h

#include <math.h>

// physical constants
#define GRAVITY 9.81 // m/sec^2

// position and attitude initialization
#define X_START 0.0  // m
#define Y_START 0.0
#define Z_START 0.0
#define ROLL_START 0.0 // degrees
#define PITCH_START 0.0
#define YAW_START 0.0

//arm length
#define LENGTH_ARM 0.225    // m

// quadcopter specific air resistance
#define DRAG_CONSTANT_X 0.2
#define DRAG_CONSTANT_Y 0.2
#define DRAG_CONSTANT_Z 0.2

#endif /* config_h */
