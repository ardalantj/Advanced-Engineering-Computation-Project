//
//  quadrotor.hpp
//  AirViz
//
//  Created by Ardalan TJ on 4/20/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#ifndef quadrotor_hpp
#define quadrotor_hpp

#include <stdio.h>
#include <vector>
#include "Eigen/Dense"
#include <iostream>

typedef Eigen::Matrix<float, 5, 1> Vector5f;
typedef Eigen::Matrix<float, 3, 1> Vector3f;
typedef Eigen::Matrix<float, 6, 1> Vector6f;


class quadrotor
{
public:
    // Simulation parameters
    const double g = 9.81;
    const double Ixx = 1.0;
    const double Iyy = 1.0;
    const double Izz = 1.0;
    double m = 0.2;
    int T = 5;
    
    // Proportional coefficients
    int Kp_x = 1;
    int Kp_y = 1;
    int Kp_z = 1;
    int Kp_roll = 25;
    int Kp_pitch = 25;
    int Kp_yaw = 25;
    
    // Derivative coefficients
    int Kd_x = 10;
    int Kd_y = 10;
    int Kd_z = 1;
    
    double thrust = 0.0;
    double roll_torque = 0.0;
    double pitch_torque = 0.0;
    double yaw_torque = 0.0;
    double roll_vel = 0.0;
    double pitch_vel = 0.0;
    double yaw_vel = 0.0;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double roll = 0.0;
    double pitch = 0.0;
    double yaw = 0.0;

    // Default construcotr Quadrotor class constructor
    quadrotor()
    {
        std::cout << "Quadrotor object constructed!" << std::endl;
    }
    
    // Specialized constructor
    quadrotor(double m_, int T_, double x_, double y_, double z_, double roll_, double pitch_, double yaw_)
    {
        std::cout << "Quadrotor specialized object constructed!" << std::endl;
        m = m_;
        T = T_;
        x = x_;
        y = y_;
        z = z_;
        roll = roll_;
        pitch = pitch_;
        yaw = yaw_;
    }
    
    // updates the current quadcopter pose given the position and orientation
    void update_pose(quadrotor &q, double x, double y, double z, double roll, double pitch, double yaw);

    // Returns the 3d transformation matrix given quadrotor position and orientation
    Eigen::Matrix3d transformation_matrix(quadrotor q);
    
    // Calculates the ZYX rotation given roll, pitch, and yaw in radians
    Eigen::Matrix3d rotation_matrix(double roll, double pitch, double yaw);
    
    // Given set of coefficients, this function calculates the required thrust and torque to track the desired trajectory
    void quadsim(Eigen::Vector3d x_c, Eigen::Vector3d y_c, Eigen::Vector3d z_c);

    // Given a set of quintic polynomials this function calculates the position
    double calc_pos(Vector5f c, double t);

    // Given a set of quintic polynomials this function calculates the velocity
    double calc_vel(Vector5f, double t);

    // Given a set of quintic polynomials this function calculates the acceleration
    double calc_accel(Vector5f, double t);
};

class trajectory
{
public:
    // Each vector contains x,y,z components
    Vector3f start_pose = Vector3f::Zero();
    Vector3f des_pose = Vector3f::Zero();
    Vector3f start_vel = Vector3f::Zero();
    Vector3f des_vel = Vector3f::Zero();
    Vector3f start_accel = Vector3f::Zero();
    Vector3f des_accel = Vector3f::Zero();
    
    // Given matrix of coefficients A solve for x, y, and z coefficients given b_x, b_y, b_z
    Vector6f traj_solve(quadrotor &q);
};

#endif /* quadrotor_hpp */

