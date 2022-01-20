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

void moveArm(int32_t target)
{
  pidStruct_t armPID;
  pidInit(&armPID, 0.0125, 0.000000001, 0, 10, 20);
  float arm_Power = 0;
  uint32_t timeOut = 100000;
  uint64_t startTime = Brain.timer(timeUnits::msec);

  do
  {
    printPIDValues(&armPID);
    arm_Power = pidCalculate(&armPID, target, armPot.value(range10bit));

    LifterMotorR.spin(forward, 12 * arm_Power, voltageUnits::volt);
    LifterMotorL.spin(forward, 12 * arm_Power, voltageUnits::volt);

  }while((fabs(armPID.avgError) > 0.03) && (Brain.timer(timeUnits::msec) - startTime < timeOut));
  
  LifterMotorL.setBrake(hold);
  LifterMotorR.setBrake(hold);
}