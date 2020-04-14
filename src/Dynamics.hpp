//
//  Dynamics.hpp
//  AirViz
//
//  Created by Ardalan TJ on 4/7/20.
//  Copyright © 2020 Ardalan TJ. All rights reserved.
//

#ifndef Dynamics_hpp
#define Dynamics_hpp

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Utils.hpp"

class Dynamics {

public:

    /**
     * Position map for state vector
     */
    enum {
        STATE_X,
        STATE_X_DOT,
        STATE_Y,
        STATE_Y_DOT,
        STATE_Z,
        STATE_Z_DOT,
        STATE_PHI,
        STATE_PHI_DOT,
        STATE_THETA,
        STATE_THETA_DOT,
        STATE_PSI,
        STATE_PSI_DOT
    };

    /**
     * Class for parameters from the table below Equation 3
     */
    class Parameters {

        friend class MultirotorDynamics;

    public:

        double b;
        double d;
        double m;
        double l;
        double Ix;
        double Iy;
        double Iz;
        double Jr;

        uint16_t maxrpm;

        Parameters(double b, double d, double m, double l, double Ix, double Iy, double Iz, double Jr, uint16_t maxrpm)
        {
            this->b = b;
            this->d = d;
            this->m = m;
            this->l = l;
            this->Ix = Ix;
            this->Iy = Iy;
            this->Iz = Iz;
            this->Jr = Jr;

            this->maxrpm = maxrpm;
        }
    };

    /**
     * Exported state representations
     */

     // Kinematics
    typedef struct {

        double location[3];
        double rotation[3];

    } pose_t;

    // Dynamics
    typedef struct {

        double angularVel[3];
        double bodyAccel[3];
        double inertialVel[3];
        double quaternion[4];

        pose_t pose;

    } state_t;

private:

    // Data structure for returning state
    state_t _state = {};

    // Flag for whether we're airborne and can update dynamics
    bool _airborne = false;

    // Inertial-frame acceleration
    double _inertialAccel[3] = {};

    // y = Ax + b helper for frame-of-reference conversion methods
    static void dot(double A[3][3], double x[3], double y[3])
    {
        for (uint8_t j = 0; j < 3; ++j) {
            y[j] = 0;
            for (uint8_t k = 0; k < 3; ++k) {
                y[j] += A[j][k] * x[k];
            }
        }
    }

    // bodyToInertial method optimized for body X=Y=0
    static void bodyZToInertial(double bodyZ, const double rotation[3], double inertial[3])
    {
        double phi = rotation[0];
        double theta = rotation[1];
        double psi = rotation[2];

        double cph = cos(phi);
        double sph = sin(phi);
        double cth = cos(theta);
        double sth = sin(theta);
        double cps = cos(psi);
        double sps = sin(psi);

        // This is the rightmost column of the body-to-inertial rotation matrix
        double R[3] = { sph * sps + cph * cps * sth,
            cph * sps * sth - cps * sph,
            cph * cth };

        for (uint8_t i = 0; i < 3; ++i) {
            inertial[i] = bodyZ * R[i];
        }
    }

    // Height above ground, set by kinematics
    double _agl = 0;

protected:

    // universal constants
    static constexpr double g = 9.80665; // might want to allow this to vary!

    // state vector (see Eqn. 11) and its first temporal derivative
    double _x[12] = {};
    double _dxdt[12] = {};

    // Values computed in Equation 6
    double _U1 = 0;     // total thrust
    double _U2 = 0;     // roll thrust right
    double _U3 = 0;     // pitch thrust forward
    double _U4 = 0;     // yaw thrust clockwise
    double _Omega = 0;  // torque clockwise

    // parameter block
    Parameters* _p = NULL;

    // roll right
    virtual double u2(double* o) = 0;

    // pitch forward
    virtual double u3(double* o) = 0;

    // yaw cw
    virtual double u4(double* o) = 0;

    // radians per second for each motor, and their squared values
    double* _omegas = NULL;
    double* _omegas2 = NULL;

    // quad, hexa, octo, etc.
    uint8_t _motorCount = 0;

    /**
     *  Constructor
     */
    MultirotorDynamics(Parameters* params, const uint8_t motorCount)
    {
        _p = params;
        _motorCount = motorCount;

        _omegas = new double[motorCount]();
        _omegas2 = new double[motorCount]();

        for (uint8_t i = 0; i < 12; ++i) {
            _x[i] = 0;
        }
    }

    virtual void updateGimbalDynamics(double dt) {}

    /**
     * Implements Equation 12 computing temporal first derivative of state.
     * Should fill _dxdx[0..11] with appropriate values.
     * @param accelNED acceleration in NED inertial frame
     * @param netz accelNED[2] with gravitational constant added in
     * @param phidot rotational acceleration in roll axis
     * @param thedot rotational acceleration in pitch axis
     * @param psidot rotational acceleration in yaw axis
     */
    virtual void computeStateDerivative(double accelNED[3], double netz)
    {
        double phidot = _x[STATE_PHI_DOT];
        double thedot = _x[STATE_THETA_DOT];
        double psidot = _x[STATE_PSI_DOT];

        _dxdt[0] = _x[STATE_X_DOT];                                                              // x'
        _dxdt[1] = accelNED[0];                                                                  // x''
        _dxdt[2] = _x[STATE_Y_DOT];                                                              // y'
        _dxdt[3] = accelNED[1];                                                                  // y''
        _dxdt[4] = _x[STATE_Z_DOT];                                                              // z'
        _dxdt[5] = netz;                                                                         // z''
        _dxdt[6] = phidot;                                                                       // phi'
        _dxdt[7] = psidot * thedot * (_p->Iy - _p->Iz) / _p->Ix - _p->Jr / _p->Ix * thedot * _Omega + _U2 / _p->Ix;    // phi''
        _dxdt[8] = thedot;                                                                       // theta'
        _dxdt[9] = -(psidot * phidot * (_p->Iz - _p->Ix) / _p->Iy + _p->Jr / _p->Iy * phidot * _Omega + _U3 / _p->Iy); // theta''
        _dxdt[10] = psidot;                                                                        // psi'
        _dxdt[11] = thedot * phidot * (_p->Ix - _p->Iy) / _p->Iz + _U4 / _p->Iz;                               // psi''
    }

    /**
     * Computes motor speed base on motor value
     * @param motorval motor value in [0,1]
     * @return motor speed in rad/s
     */
    virtual double computeMotorSpeed(double motorval)
    {
        return motorval * _p->maxrpm * 3.14159 / 30;
    }

public:

    /**
     *  Destructor
     */
    virtual ~MultirotorDynamics(void)
    {
        delete _omegas;
        delete _omegas2;
    }

    /**
     * Initializes kinematic pose, with flag for whether we're airbone (helps with testing gravity).
     *
     * @param rotation initial rotation
     * @param airborne allows us to start on the ground (default) or in the air (e.g., gravity test)
     */
    void init(double rotation[3], bool airborne = false)
    {
        // Always start at location (0,0,0)
        _x[STATE_X] = 0;
        _x[STATE_Y] = 0;
        _x[STATE_Z] = 0;

        _x[STATE_PHI] = rotation[0];
        _x[STATE_THETA] = rotation[1];
        _x[STATE_PSI] = rotation[2];

        // Initialize velocities and airborne flag
        _airborne = airborne;
        _x[STATE_X_DOT] = 0;
        _x[STATE_Y_DOT] = 0;
        _x[STATE_Z_DOT] = 0;
        _x[STATE_PHI_DOT] = 0;
        _x[STATE_THETA_DOT] = 0;
        _x[STATE_PSI_DOT] = 0;

        // Initialize inertial frame acceleration in NED coordinates
        bodyZToInertial(-g, rotation, _inertialAccel);

        // We usuall start on ground, but can start in air for testing
        _airborne = airborne;
    }

    /**
     * Updates state.
     *
     * @param dt time in seconds since previous update
     */
    void update(double dt)
    {
        // Use the current Euler angles to rotate the orthogonal thrust vector into the inertial frame.
        // Negate to use NED.
        double euler[3] = { _x[6], _x[8], _x[10] };
        double accelNED[3] = {};
        bodyZToInertial(-_U1 / _p->m, euler, accelNED);

        // We're airborne once net downward acceleration goes below zero
        double netz = accelNED[2] + g;

        double velz = _x[STATE_Z_DOT];

        //debugline("Airborne: %d   AGL: %3.2f   velz: %+3.2f   netz: %+3.2f", _airborne, _agl, velz, netz);

        // If we're airborne, check for low AGL on descent
        if (_airborne) {

            //if (_agl <= 0 && velz > 0) {
            if (_agl <= 0 && netz >= 0) {
                _airborne = false;
                _x[STATE_PHI_DOT] = 0;
                _x[STATE_THETA_DOT] = 0;
                _x[STATE_PSI_DOT] = 0;
                _x[STATE_X_DOT] = 0;
                _x[STATE_Y_DOT] = 0;
                _x[STATE_Z_DOT] = 0;

                _x[STATE_PHI] = 0;
                _x[STATE_THETA] = 0;
                _x[STATE_Z] += _agl;
            }
        }

        // If we're not airborne, we become airborne when downward acceleration has become negative
        else {
            _airborne = netz < 0;
        }

        // Once airborne, we can update dynamics
        if (_airborne) {

            // Compute the state derivatives using Equation 12
            computeStateDerivative(accelNED, netz);

            // Compute state as first temporal integral of first temporal derivative
            for (uint8_t i = 0; i < 12; ++i) {
                _x[i] += dt * _dxdt[i];
            }

            // Once airborne, inertial-frame acceleration is same as NED acceleration
            _inertialAccel[0] = accelNED[0];
            _inertialAccel[1] = accelNED[1];
            _inertialAccel[2] = accelNED[2];
        }
        else {
            //"fly" to agl=0
            double vz = 5 * _agl;
            _x[STATE_Z] += vz * dt;
        }

        updateGimbalDynamics(dt);

        // Get most values directly from state vector
        for (uint8_t i = 0; i < 3; ++i) {
            uint8_t ii = 2 * i;
            _state.angularVel[i] = _x[STATE_PHI_DOT + ii];
            _state.inertialVel[i] = _x[STATE_X_DOT + ii];
            _state.pose.rotation[i] = _x[STATE_PHI + ii];
            _state.pose.location[i] = _x[STATE_X + ii];
        }

        // Convert inertial acceleration and velocity to body frame
        inertialToBody(_inertialAccel, _state.pose.rotation, _state.bodyAccel);

        // Convert Euler angles to quaternion
        eulerToQuaternion(_state.pose.rotation, _state.quaternion);

    } // update

    /**
     * Returns state structure.
     * @return state structure
     */
    state_t getState(void)
    {
        return _state;
    }

    /**
     * Returns "raw" state vector.
     * @return state vector
     */
    double* getStateVector(void)
    {
        return _x;
    }

    /**
     * Uses motor values to implement Equation 6.
     *
     * @param motorvals in interval [0,1]
     * @param dt time constant in seconds
     */
    virtual void setMotors(double* motorvals, double dt)
    {
        // Convert the  motor values to radians per second
        for (unsigned int i = 0; i < _motorCount; ++i) {
            _omegas[i] = computeMotorSpeed(motorvals[i]); //rad/s
        }

        // Compute overall torque from omegas before squaring
        _Omega = u4(_omegas);

        // Overall thrust is sum of squared omegas
        _U1 = 0;
        for (unsigned int i = 0; i < _motorCount; ++i) {
            _omegas2[i] = _omegas[i] * _omegas[i];
            _U1 += _p->b * _omegas2[i];
        }

        // Use the squared Omegas to implement the rest of Eqn. 6
        _U2 = _p->l * _p->b * u2(_omegas2);
        _U3 = _p->l * _p->b * u3(_omegas2);
        _U4 = _p->d * u4(_omegas2);
    }

    /**
     *  Gets current pose
     *
     *  @return data structure containing pose
     */
    pose_t getPose(void)
    {
        pose_t pose = {};

        for (uint8_t i = 0; i < 3; ++i) {
            uint8_t ii = 2 * i;
            pose.rotation[i] = _x[STATE_PHI + ii];
            pose.location[i] = _x[STATE_X + ii];
        }

        return pose;
    }

    /**
     * Sets height above ground level (AGL).
     * This method can be called by the kinematic visualization.
     */
    void setAgl(double agl)
    {
        _agl = agl;
    }

    // Motor direction for animation
    virtual int8_t motorDirection(uint8_t i) { (void)i; return 0; }

    /**
     *  Frame-of-reference conversion routines.
     *
     *  See Section 5 of http://www.chrobotics.com/library/understanding-euler-angles
     */

    static void bodyToInertial(double body[3], const double rotation[3], double inertial[3])
    {
        double phi = rotation[0];
        double theta = rotation[1];
        double psi = rotation[2];

        double cph = cos(phi);
        double sph = sin(phi);
        double cth = cos(theta);
        double sth = sin(theta);
        double cps = cos(psi);
        double sps = sin(psi);

        double R[3][3] = { {cps * cth,  cps * sph * sth - cph * sps,  sph * sps + cph * cps * sth},
            {cth * sps,  cph * cps + sph * sps * sth,  cph * sps * sth - cps * sph},
            {-sth,     cth * sph,                cph * cth} };

        dot(R, body, inertial);
    }

    static void inertialToBody(double inertial[3], const double rotation[3], double body[3])
    {
        double phi = rotation[0];
        double theta = rotation[1];
        double psi = rotation[2];

        double cph = cos(phi);
        double sph = sin(phi);
        double cth = cos(theta);
        double sth = sin(theta);
        double cps = cos(psi);
        double sps = sin(psi);

        double R[3][3] = { {cps * cth,                cth * sps,                   -sth},
            {cps * sph * sth - cph * sps,  cph * cps + sph * sps * sth,  cth * sph},
            {sph * sps + cph * cps * sth,  cph * sps * sth - cps * sph,  cph * cth} };

        dot(R, inertial, body);
    }

    /**
     * Converts Euler angles to quaterion.
     *
     * @param eulerAngles input
     * @param quaternion output
     */

    static void eulerToQuaternion(const double eulerAngles[3], double quaternion[4])
    {
        // Convenient renaming
        double phi = eulerAngles[0] / 2;
        double the = eulerAngles[1] / 2;
        double psi = eulerAngles[2] / 2;

        // Pre-computation
        double cph = cos(phi);
        double cth = cos(the);
        double cps = cos(psi);
        double sph = sin(phi);
        double sth = sin(the);
        double sps = sin(psi);

        // Conversion
        quaternion[0] = cph * cth * cps + sph * sth * sps;
        quaternion[1] = cph * sth * sps - sph * cth * cps;
        quaternion[2] = -cph * sth * cps - sph * cth * sps;
        quaternion[3] = cph * cth * sps - sph * sth * cps;
    }

    /**
     * Gets motor count set by constructor.
     * @return motor count
     */
    uint8_t motorCount(void)
    {
        return _motorCount;
    }

}; // class MultirotorDynamics

#endif /* Dynamics_hpp */
