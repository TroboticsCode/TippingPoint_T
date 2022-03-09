#include "Autons.h"
#include "DriveFunctionsConfig.h"
#include "Functions.h"
#include "vex.h"
#include "gps.h"
//#include "Vision.h"
//#include "Vision2.h"
#include "visionSigs.h"

// Put your auton routines in here

void Auton1() // skills
{
  // setRotGains(0, 0, 0, 20, 10); //update PID gains to tune robot
  // setLinGains(0, 0, 0, 20, 10);

  //setLinGains(65, 0.0000000000001, 35, 15, 10); //done
  //setRotGains(0.03, 0.00000000000000001, 0.002, 15, 10);

  setLinGains(75, 0.0000000000000001, 35, 20, 10);
  setRotGains(0.03, 0, 0, 20, 10);
  
  LifterMotorL.setBrake(hold);
  LifterMotorR.setBrake(hold);

  moveLinear(91, 100, 6000); // pushes goal one across the field
  moveStop(hold);
  // wait(1, seconds);

  moveRotate(40, 100, 3000); // rotate towards the second goal
  moveStop(hold);

  wait(1, seconds);
  moveLinear(-77, 100, 3000); // move towards and pushes the second goal to the other side
  moveStop(hold);

  // wait(1, seconds);
  moveRotate(-60, 100, 3000); // rotates towards the third goal
  moveStop(hold);

  // wait(1, seconds);
  moveLinear(75, 75, 3000); // moves towards and pushes the third goal to the other side
  moveStop(hold);

  // wait(1, seconds);
  moveRotate(55, 100, 3000); // rotates towards the third goal probably
  moveStop(hold);

  // wait(1, seconds);
  moveLinear(-65, 100, 3000); // moves towards the third goal probably
  moveStop(hold);

  // wait(1, seconds);
  // moveRotate(-51, 25, 3000); // rotates towards another goal
  goalCenter(&Vision, BLUESIG);
  moveStop(hold);

  wait(1, seconds);
  // moveLinear(43, 45, 3000); // moves towards the goal ...
  // wait(0, seconds);
  // claw(); // for some reason should grab a goal
  // moveLinear(-78, 60, 3000); // moves the grabbed goal away to score more
  // points probably
  moveRotate(-50, 100, 3000);
  //goalApproach(SIGBLUE, 50, 6000);
  for(int i = 0; i < 5; i++)
  {
    goalCenter(&Vision, BLUESIG);
  }
  moveLinear(72, 100, 4000);
  moveLinear(-190, 100, 4000);
}

void Auton2() // right
{
  setLinGains(75, 0.0000000000000001, 35, 20, 10);
  setRotGains(0.03, 0, 0, 20, 10);

  moveLinear(12, 20, 3000);
  moveStop(hold);
  wait(1, seconds);
  pClaw(true);
  //moveRotate(-35, 90, 3000);
  //wait(0.5, seconds);
  moveLinear(-36, 90, 3000);
  
  /*
  wait(1, seconds);
  moveRotate(35, 90, 3000);
  wait(0.5, seconds);
  moveLinear(-12, 20, 3000);
  moveStop(hold);
  */
}

void Auton3() //programming skills
{
  // start lift control task
  //vex::task armTask(pidArmTask); //this will run in the background to keep the arm in position
  //armAngleIndex = 0; //update index to move arm to new position
  
  // update drive PID gains to tune robot
  /*
  setLinGains(65, 0.0000000000001, 35, 15, 10); //done
  setRotGains(0.03, 0.00000000000000001, 0.002, 15, 10);

  //wait for GPS to calibrate
  GPS.calibrate();
  while(GPS.isCalibrating());

  //movePoint(coordinates[yellowCenter][xCOR], coordinates[yellowCenter][yCOR]);
  movePoint(24, 24);*/

  while(1)
    goalCenter(&Vision2, BLUESIG2);
}

void Auton4() 
{
  setLinGains(75, 0, 0, 20, 10);
  setRotGains(0.03, 0, 0, 20, 10);
  
  vex::task armTask(pidArmTask); //this will run in the background to keep the arm in position
  armAngleIndex = 0; //update index to move arm to new position

  goalApproach(90, 1200, &Vision, YELLOWSIG);
  //we have the yellow goal, now lift the arm
  //armAngleIndex = 1;

  moveLinear(-20, 100, 3000);
  moveStop(brake);
  moveRotate(-80, 60, 3000);

  goalCenter(&Vision2, BLUESIG2); //must use sig 2's with vision2, center on next goal

  moveLinear(-18, 100, 3000); //back into goal
  pClampBack(OPEN); //grab
  moveLinear(24, 100, 3000); //move away from line
  //arm(15);
  armAngleIndex = 2; //update arm angles in the functions.cpp file
  wait(500, msec);

  armTask.stop(); //make sure to kill the arm control
}

