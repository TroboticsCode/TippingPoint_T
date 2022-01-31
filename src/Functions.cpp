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

void arm(int angle) 
{
  float motorRotation = angle * -7;
  LifterMotorL.rotateTo(motorRotation, degrees, false);
  LifterMotorR.rotateTo(motorRotation, degrees, true);

  LifterMotorL.stop();
  LifterMotorR.stop();
}

void claw(bool open)
{
  if(open)
  {
    PincherMotor.rotateTo(0, degrees, false);
    
  }
  else
  {
    PincherMotor.rotateTo(90, degrees, false);
  }
}

void pClaw(bool open)
{
  Pincher.set(open);
}
