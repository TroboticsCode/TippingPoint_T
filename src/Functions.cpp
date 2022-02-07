#include "functions.h"
#include "DriveFunctionsConfig.h"
#include "Vision.h"
#include "vex.h"

#define CENTER_X 316 / 2.0f
#define CENTER_Y 212 / 2.0f

void testPID() {
  for (int i = 0; i < 8; i++) {
    moveLinear(12, 100, 10000);
    moveRotate(-90, 90, 10000);
  }
  // moveStop();
  wait(20, msec); // Sleep the task for a short amount of time t
}

void arm(int angle) {
  float motorRotation = angle * -7;
  LifterMotorL.rotateTo(motorRotation, degrees, false);
  LifterMotorR.rotateTo(motorRotation, degrees, true);

  LifterMotorL.stop();
  LifterMotorR.stop();
}

void pClaw(bool open) { Pincher.set(open); }

void goalCenter(int color) {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Starting ball center routine");

  if (color == SIGRED)
    Vision.takeSnapshot(REDSIG);
  else if (color == SIGBLUE)
    Vision.takeSnapshot(BLUESIG);
  else if (color == SIGYELLOW)
    Vision.takeSnapshot(YELLOWSIG);

  int objectCenter = Vision.largestObject.centerX;

  while ((objectCenter > CENTER_X + 10) || (objectCenter < CENTER_X - 10)) {
    if (color == SIGRED)
      Vision.takeSnapshot(REDSIG);
    else if (color == SIGBLUE)
      Vision.takeSnapshot(BLUESIG);
    else if (color == SIGYELLOW)
      Vision.takeSnapshot(YELLOWSIG);

    objectCenter = Vision.largestObject.centerX;
    Brain.Screen.setCursor(2, 2);
    Brain.Screen.clearLine();
    Brain.Screen.print(objectCenter);

    if (objectCenter < CENTER_X - 5) {
      Brain.Screen.print("turn right");
      BackRight.spin(directionType::fwd, 15, velocityUnits::pct);
      BackLeft.spin(directionType::rev, 15, velocityUnits::pct);
      FrontRight.spin(directionType::fwd, 15, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, 15, velocityUnits::pct);
    } 
    else if (objectCenter > CENTER_X + 5) {
      Brain.Screen.print("turn left ");
      BackRight.spin(directionType::rev, 15, velocityUnits::pct);
      BackLeft.spin(directionType::fwd, 15, velocityUnits::pct);
      FrontRight.spin(directionType::rev, 15, velocityUnits::pct);
      FrontLeft.spin(directionType::fwd, 15, velocityUnits::pct);
    } 
    else {
      Brain.Screen.print("Dont move");
      BackRight.stop();
      BackLeft.stop();
      FrontRight.stop();
      FrontLeft.stop();
    }
  }
  Brain.Screen.newLine();
  Brain.Screen.print("DONE");
  BackRight.stop(brakeType::brake);
  BackLeft.stop(brakeType::brake);
  FrontRight.stop(brakeType::brake);
  FrontLeft.stop(brakeType::brake);
}

void goalApproach(int color) {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Starting goal approach routine");

  const int defPower = 40;

  int driveL = defPower;
  int driveR = defPower;

  int error = 0;
  int objectCenter;
  float gain = 0.25;
  int correction = 0;

  while (!clawBumper.pressing()) {
    if (color == SIGRED)
      Vision.takeSnapshot(REDSIG);
    else if (color == SIGBLUE)
      Vision.takeSnapshot(BLUESIG);
    else if (color == SIGYELLOW)
      Vision.takeSnapshot(YELLOWSIG);

    // take snapshot of color
    objectCenter = Vision.largestObject.centerX;

    driveL = defPower;
    driveR = defPower;

    // determine error from center
    error = abs(CENTER_X - objectCenter);
    correction = error * gain;

    if (correction > defPower)
      correction = defPower;

    // apply correction to drive output
    if (Vision.objectCount > 0) {
      if (objectCenter < CENTER_X - 5) {
        driveL -= correction;
      } else if (objectCenter > CENTER_X + 5) {
        driveR -= correction;
      } else {
        driveL = defPower;
        driveR = defPower;
      }
    } else { //no object found, go straight
      driveL = defPower;
      driveR = defPower;
    }

    // output drive
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Left Power %d", driveL);
    Brain.Screen.newLine();
    Brain.Screen.print("Right Power %d", driveR);
    BackRight.spin(directionType::fwd, driveR, velocityUnits::pct);
    BackLeft.spin(directionType::fwd, driveL, velocityUnits::pct);
    FrontRight.spin(directionType::fwd, driveR, velocityUnits::pct);
    FrontLeft.spin(directionType::fwd, driveL, velocityUnits::pct);

    wait(10, msec);
  }
  // goal reached, stop and close claw
  Brain.Screen.newLine();
  Brain.Screen.print("DONE");
  BackRight.stop(brakeType::brake);
  BackLeft.stop(brakeType::brake);
  FrontRight.stop(brakeType::brake);
  FrontLeft.stop(brakeType::brake);
  pClaw(CLOSE);
}