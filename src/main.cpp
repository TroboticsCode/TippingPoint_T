// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Inertial12           inertial      12
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       JBormann                                                  */
/*    Created:      Nov. 2019                                                 */
/*    Description:  Trobotics Template File                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

LifterMotorL.setVelocity(100, percent);
LifterMotorR.setVelocity(100, percent);
LifterMotorL.setPosition(0, degrees);
LifterMotorR.setPosition(0, degrees);

  Controller1.ButtonR1.pressed(cycle_autons);
  Brain.Screen.pressed(cycle_autons);
  return;
}

void autonomous(void) {
  switch (state) {
  case NONE:
    break;

  case AutonR:
    Auton1();
    break;

  case AutonB:
    Auton2();
    break;

  // Default = NO autonomous
  default:
    break;
  }
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // add local user control variables here:

  // User control code here, inside the loop:
  // remove existing demo code and replace with you own! Then remove this
  // comment
  while (1) {
    Controller1.ButtonY.pressed(autonomous);

    // leave the drive code here, it should work if you set up
    // DriveFunctionsConfig.h properly
    userDrive();

    LifterMotorL.setStopping(hold);
    LifterMotorR.setStopping(hold);
    PincherMotor.setStopping(hold);
    ForkLiftMotor.setStopping(hold);
    LifterMotorL.setVelocity(100, percent);
    LifterMotorR.setVelocity(100, percent);
    PincherMotor.setVelocity(50, percent);
    ForkLiftMotor.setVelocity(100, percent);

    if (Controller1.ButtonL2.pressing()) 
    {
      PincherMotor.spin(reverse);
    } 
    else if (Controller1.ButtonL1.pressing()) 
    {
      PincherMotor.spin(forward);
    } 
    else 
    {
      PincherMotor.stop();
    }

    if (Controller1.ButtonX.pressing()) 
    {
      ForkLiftMotor.spin(forward);
    } 
    else if (Controller1.ButtonB.pressing()) 
    {
      ForkLiftMotor.spin(reverse);
    } 
    else 
    {
      ForkLiftMotor.stop();
    }

    //lift control
    if (Controller1.ButtonR2.pressing() && armPot.value(range10bit) > 355) //down
    {
      LifterMotorL.spin(forward);
      LifterMotorR.spin(forward);
    } 
    else if (Controller1.ButtonR1.pressing() && armPot.value(range10bit) < 775) //up
    {
      LifterMotorL.spin(reverse);
      LifterMotorR.spin(reverse);
    } 
    else 
    {
      LifterMotorL.stop();
      LifterMotorR.stop();
    }

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Arm Pot Value: ");
    Brain.Screen.print(armPot.value(range10bit));

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }

  wait(20, msec); // Sleep the task for a short amount of time to
}

// Main will set up the competition functions and callbacks.

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
