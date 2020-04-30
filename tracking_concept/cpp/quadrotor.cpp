//
//  quadrotor.cpp
//  AirViz
//
//  Created by Ardalan TJ on 4/20/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#include "quadrotor.hpp"
#include <stdio.h>
#include <iostream>
#include <cmath>

typedef Eigen::Matrix<float, 5, 1> Vector5f;
typedef Eigen::Matrix<float, 6, 6> Matrix6f;


// updates the current quadcopter pose given the position and orientation
void quadrotor::update_pose(quadrotor &q, double x, double y,double z, double roll,double pitch,double yaw)
{
    q.x = x;
    q.y = y;
    q.z = z;
    q.roll = roll;
    q.pitch = pitch;
    q.yaw = yaw;
}

// Calculates the ZYX rotation given roll, pitch, and yaw in radians
Eigen::Matrix3d rotation_matrix(double roll, double pitch, double yaw)
{
    Eigen::Matrix3d rotation_mat;

    rotation_mat << cos(yaw) * cos(pitch), -sin(yaw) * cos(roll) + cos(yaw) * sin(pitch) * sin(roll), sin(yaw) * sin(roll) + cos(yaw) * sin(pitch) * cos(roll),
    sin(yaw) * cos(pitch), cos(yaw) * cos(roll) + sin(yaw) * sin(pitch) *
     sin(roll), -cos(yaw) * sin(roll) + sin(yaw) * sin(pitch) * cos(roll),
     -sin(pitch), cos(pitch) * sin(roll), cos(pitch) * cos(yaw);

    return rotation_mat;
}

// Returns transofrmation matrix given position and orientation
Eigen::Matrix3d quadrotor::transformation_matrix(quadrotor quad)
{
    x = quad.x;
    y = quad.y;
    z = quad.z;
    roll = quad.roll;
    pitch = quad.pitch;
    yaw = quad.yaw;

    Eigen::Matrix3d transformation_mat;

    transformation_mat << cos(yaw) * cos(pitch), -sin(yaw) * cos(roll) + cos(yaw) * sin(pitch) * sin(roll),sin(yaw) * sin(roll) + cos(yaw) * sin(pitch) * cos(roll), x,
    sin(yaw) * cos(pitch), cos(yaw) * cos(roll) + sin(yaw) * sin(pitch) * sin(roll), -cos(yaw) * sin(roll) + sin(yaw) * sin(pitch) * cos(roll), y,
    -sin(pitch), cos(pitch) * sin(roll), cos(pitch) * cos(yaw), z;

    return transformation_mat;
}

// Given set of coefficients, this function calculates the required thrust and torque to track the desired trajectory
void quadrotor::quadsim(Eigen::Vector3d x_c, Eigen::Vector3d y_c, Eigen::Vector3d)
{
    auto x_pos = -5;
    auto y_pos = -5;
    auto z_pos = 5;
    auto x_vel = 0;
    auto y_vel = 0;
    auto z_vel = 0;
    auto x_acc = 0;
    auto y_acc = 0;
    auto z_acc = 0;
    auto roll = 0;
    auto pitch = 0;
    auto yaw = 0;
    auto roll_vel = 0;
    auto pitch_vel = 0;
    auto yaw_vel = 0;

    auto des_yaw = 0;

    auto dt = 0.1;
    auto t = 0;

    auto qobj = quadrotor(5, 5, x = x_pos, y = y_pos, z = z_pos, roll = roll,
                  pitch = pitch, yaw = yaw);

    auto i = 0;
    auto n_run = 8;
    auto irun = 0;

    while (true) {
        while(t < T)
        {
//            auto des_z_pos = calc_pos(z_c[i], t);
//            auto des_x_vel = calc_vel(x_c[i], t);
//            auto des_y_vel = calc_vel(y_c[i], t);
//            auto des_z_vel = calc_vel(z_c[i], t);
//            auto des_x_acc = calc_accel(x_c[i], t);
//            auto des_y_acc = calc_accel(y_c[i], t);
//            auto des_z_acc = calc_accel(z_c[i], t);

//            auto thrust = m * (g + des_z_acc + Kp_z * (des_z_pos -z_pos) + Kd_z * (des_z_vel - z_vel));
//
//            roll_torque = Kp_roll * \
//                (((des_x_acc * sin(des_yaw) - des_y_acc * cos(des_yaw)) / g) - roll)
//            pitch_torque = Kp_pitch * \
//                (((des_x_acc * cos(des_yaw) - des_y_acc * sin(des_yaw)) / g) - pitch)
//            yaw_torque = Kp_yaw * (des_yaw - yaw)
//
            roll_vel += roll_torque * dt / Ixx;
            pitch_vel += pitch_torque * dt / Iyy;
            yaw_vel += yaw_torque * dt / Izz;
//
            roll += roll_vel * dt;
            pitch += pitch_vel * dt;
            yaw += yaw_vel * dt;
//
            auto R = rotation_matrix(roll, pitch, yaw);
        }
    }
}

// Given a set of quintic polynomials this function calculates the position
double quadrotor::calc_pos(Vector5f c, double t)
{
    return c[0] * pow(t,5) + c[1] * pow(t,4) + c[2] * pow(t,3) + c[3] * pow(t,2) + c[4] * t + c[5];
}

// Given a set of quintic polynomials this function calculates the velocity
double quadrotor::calc_vel(Vector5f c, double t)
{
    return 5 * c[0] * pow(t,4) + 4 * c[1] * pow(t,3) + 3 * c[2] * pow(t,2) + 2 * c[3] * t + c[4];
}

// Given a set of quintic polynomials this function calculates the acceleration
double quadrotor::calc_accel(Vector5f c, double t)
{
    return 20 * c[0] * pow(t,3) + 12 * c[1] * pow(t,2) + 6 * c[2] * t + 2 * c[3];
}

Vector3f trajectory::traj_solve()
{
    Vector3f x_c;
    Vector3f y_c;
    Vector3f z_c;

    Matrix6f A;

    A << 0, 0, 0, 0, 0, 1,
    pow(T,5), pow(T,4), pow(T,3), pow(T,2), pow(T,1), 1,
    0, 0, 0, 0, 1, 0,
    5 * pow(T,4), 4 * pow(T,3), 3 * pow(T,2), 2*T, 1, 0,
    0, 0, 0, 2, 0, 0,
    20 * pow(T,3), 12 * pow(T,2), 6*T, 2, 0, 0;

    return x_c, y_c, z_c;
}
