#include "functions.h"
#include "DriveFunctionsConfig.h"
#include "PID.h"
#include "Vision.h"
#include "vex.h"

#define CENTER_X 316 / 2.0f
#define CENTER_Y 212 / 2.0f

uint16_t armAngles[] = {492, 670, 800};
uint8_t armAngleIndex = 0;
pidStruct_t armPID;

void testPID() {
  setLinGains(65, 0.0000000000001, 35, 15, 10); // done
  setRotGains(0.03, 0.00000000000000001, 0.002, 15, 10);
  for (int i = 0; i < 1; i++) {
    // moveLinear(36, 100, 10000);
    moveRotate(90, 100, 100000);
    moveStop(brake);
    wait(5, sec);
    // moveRotate(-90, 90, 10000);
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
  Brain.Screen.setCursor(6, 1);
  Brain.Screen.clearLine();
  Brain.Screen.print("Cam status: %d", Vision.installed());

  if (color == SIGRED)
    Vision.takeSnapshot(REDSIG);
  else if (color == SIGBLUE)
    Vision.takeSnapshot(BLUESIG);
  else if (color == SIGYELLOW)
    Vision.takeSnapshot(YELLOWSIG);

  int objectCenter = Vision.largestObject.centerX;

  while ((objectCenter > CENTER_X + 5) || (objectCenter < CENTER_X - 5)) {
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

    if (Vision.objectCount > 0) {
      if (objectCenter < CENTER_X - 10) {
        Brain.Screen.print("turn right");
        BackRight.spin(directionType::fwd, 15, velocityUnits::pct);
        BackLeft.spin(directionType::rev, 15, velocityUnits::pct);
        FrontRight.spin(directionType::fwd, 15, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, 15, velocityUnits::pct);
      } else if (objectCenter > CENTER_X + 10) {
        Brain.Screen.print("turn left ");
        BackRight.spin(directionType::rev, 15, velocityUnits::pct);
        BackLeft.spin(directionType::fwd, 15, velocityUnits::pct);
        FrontRight.spin(directionType::rev, 15, velocityUnits::pct);
        FrontLeft.spin(directionType::fwd, 15, velocityUnits::pct);
      } else {
        Brain.Screen.print("Dont move");
        BackRight.stop();
        BackLeft.stop();
        FrontRight.stop();
        FrontLeft.stop();
      }
    } else {
      moveStop(brake);
      Brain.Screen.clearLine();
      Brain.Screen.print("No object detected");
    }
  }
  Brain.Screen.newLine();
  Brain.Screen.print("DONE");
  BackRight.stop(brakeType::brake);
  BackLeft.stop(brakeType::brake);
  FrontRight.stop(brakeType::brake);
  FrontLeft.stop(brakeType::brake);
}

void goalApproach(int color, uint8_t vel, uint64_t timeOut) {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Starting goal approach routine");

  BackRight.resetPosition();
  BackLeft.resetPosition();
  FrontRight.resetPosition();
  FrontLeft.resetPosition();

  const uint8_t defPower = vel;

  int driveL = defPower;
  int driveR = defPower;

  int error = 0;
  int objectCenter;
  float gain = 0.25;
  int correction = 0;

  uint64_t startTime = Brain.timer(timeUnits::msec);

  while (!clawBumper.pressing() &&
         (Brain.timer(timeUnits::msec) - startTime < timeOut)) {
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
    error = fabs(CENTER_X - objectCenter);
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
    } else { // no object found, go straight
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

int pidArmTask() {
  while (1) {
    pidCalculate(&armPID, armAngles[armAngleIndex], armPot.value(range10bit));
    LifterMotorL.spin(forward, 0.12f * armPID.output, voltageUnits::volt);
    LifterMotorR.spin(forward, 0.12f * armPID.output, voltageUnits::volt);

    // printPIDValues(&armPID);

    Brain.Screen.setCursor(8, 1);
    Brain.Screen.print("arm function ran ");

    vex::task::sleep(armPID.minDt);
  }

  return 0;
}