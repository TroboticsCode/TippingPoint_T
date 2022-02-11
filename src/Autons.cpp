#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"
#include "gps.h"

// Put your auton routines in here

void Auton1() // skills
{
  // setRotGains(0, 0, 0, 20, 10); //update PID gains to tune robot
  //  setLinGains(0, 0, 0, 20, 10);
  LifterMotorL.setBrake(hold);
  LifterMotorR.setBrake(hold);

  moveLinear(91, 50, 10000); // pushes goal one across the field
  moveStop(hold);
  // wait(1, seconds);

  moveRotate(40, 50, 3000); // rotate towards the second goal
  moveStop(hold);

  wait(1, seconds);
  moveLinear(-77, 50,
             3000); // move towards and pushes the second goal to the other side
  moveStop(hold);

  // wait(1, seconds);
  moveRotate(-60, 50, 3000); // rotates towards the third goal
  moveStop(hold);

  // wait(1, seconds);
  moveLinear(75, 50,
             3000); // moves towards and pushes the third goal to the other side
  moveStop(hold);

  // wait(1, seconds);
  moveRotate(55, 50, 3000); // rotates towards the third goal probably
  moveStop(hold);

  // wait(1, seconds);
  moveLinear(-65, 50, 3000); // moves towards the third goal probably
  moveStop(hold);

  // wait(1, seconds);
  // moveRotate(-51, 25, 3000); // rotates towards another goal
  goalCenter(SIGBLUE);
  moveStop(hold);

  wait(1, seconds);
  // moveLinear(43, 45, 3000); // moves towards the goal ...
  // wait(0, seconds);
  // claw(); // for some reason should grab a goal
  // moveLinear(-78, 60, 3000); // moves the grabbed goal away to score more
  // points probably
  moveRotate(-50, 50, 3000);
  goalApproach(SIGBLUE);
  moveLinear(-190, 100, 4000);
}

void Auton2() // right
{
  moveLinear(12, 20, 3000);
  moveStop(hold);
  wait(1, seconds);
  pClaw(true);
  moveRotate(-35, 90, 3000);
  wait(0.5, seconds);
  moveLinear(-12, 90, 3000);
  wait(1, seconds);
  moveRotate(35, 90, 3000);
  wait(0.5, seconds);
  moveLinear(-12, 20, 3000);
  moveStop(hold);
}

void Auton3() //programming skills
{
  // start lift control task
  vex::task armTask(pidArmTask); //this will run in the background to keep the arm in position
  armAngleIndex = 0; //update index to move arm to new position

  // update drive PID gains to tune robot
  setRotGains(0, 0, 0, 20, 10); 
  setLinGains(0, 0, 0, 20, 10);

  //wait for GPS to calibrate
  GPS.calibrate();
  while(GPS.isCalibrating());

  movePoint(coordinates[yellowCenter][xCOR], coordinates[yellowCenter][yCOR]);

  // starting blue
  moveLinear(91, 50, 10000); // pushes goal one across the field
  moveStop(hold);

  // first yellow
  moveRotate(-170, 50, 3000); // rotate towards the second goal (yellow)
  moveStop(hold);
  goalCenter(SIGYELLOW);
  goalCenter(SIGYELLOW);

  moveLinear(60, 50, 3000); // move towards and pushes the second goal to the other side
  moveStop(hold);

  // second yellow
  moveLinear(-2, 50, 1000);
  moveRotate(120, 75, 3000); // rotates towards the third goal
  moveStop(hold);

  goalCenter(SIGYELLOW);
  goalCenter(SIGYELLOW);

  moveLinear(45, 50, 3000); // moves towards and pushes the third goal to the other side
  moveStop(hold);

  // third yellow
  moveRotate(-120, 75, 3000); // rotates towards the third goal probably
  moveStop(hold);
  goalCenter(SIGYELLOW);

  moveLinear(65, 50, 3000); // moves towards the third goal probably
  moveStop(hold);

  // last blue
  moveRotate(100, 75, 3000);

  goalCenter(SIGBLUE);
  moveStop(hold);

  // moveLinear(43, 45, 3000); // moves towards the goal ...
  // wait(0, seconds);

  goalApproach(SIGBLUE);
  moveLinear(-190, 100, 4000);
}
