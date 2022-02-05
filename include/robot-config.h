#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

using namespace vex;

extern brain Brain;

// VEXcode devices - declare new devices here, set them up
// in robot-config.cpp
extern controller Controller1;
extern motor LifterMotorL;
extern motor LifterMotorR;
extern motor ForkLiftMotor;
extern motor PincherMotor;
extern pneumatics Pincher;

extern pot armPot;
extern pot forkLiftPot;
extern bumper clawBumper;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );

#endif