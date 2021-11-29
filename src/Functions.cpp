#include "functions.h"
#include "DriveFunctionsConfig.h"
#include "vex.h"

void testPID() {
  for (int i = 0; i < 8; i++) {
    moveLinear(12, 100, 10000);
    moveRotate(-90, 90, 10000);
  }
  // moveStop();
  wait(20, msec); // Sleep the task for a short amount of time t
}

void Arm(int angle) 
{
  float motorRotation = angle * -7;
  LifterMotorL.rotateTo(motorRotation, degrees, false);
  LifterMotorR.rotateTo(motorRotation, degrees, true);

  LifterMotorL.stop();
  LifterMotorR.stop();
}