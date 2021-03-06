#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//always include vex.h because it has all the robot setup declarations
//as well as the API for the code.
#include "vex.h"

#define OPEN false
#define CLOSE true

#define SIGRED     1
#define SIGBLUE    2
#define SIGYELLOW  3

//enter the prototypes for other functions here
//lift, claw, etc
//drive function prototypes can go here but they should be in the DriveFunctions.h file
void testPID(void);
void arm(int angle);
void claw(bool open);
void pClaw(bool open);
void moveArm(int32_t target);
void goalCenter(int color);
void goalApproach(int color, uint8_t vel);

#endif