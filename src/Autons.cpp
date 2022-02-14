#include "vex.h"
#include "Autons.h"
#include "Functions.h"
#include "DriveFunctionsConfig.h"

//Put your auton routines in here

void Auton1() //skills
{
// setRotGains(0, 0, 0, 20, 10); //update PID gains to tune robot
//  setLinGains(0, 0, 0, 20, 10);
  LifterMotorL.setBrake(hold);
  LifterMotorR.setBrake(hold);

  moveLinear(91, 50, 5000); //pushes goal one across the field
  moveStop(hold);
  //wait(1, seconds);

  moveRotate(40, 50, 5000); //rotate towards the second goal
    moveStop(hold);

  wait(1, seconds);
  moveLinear(-72, 50, 5000); // move towards and pushes the second goal to the other side
    moveStop(hold);

  //wait(1, seconds);
  moveRotate(-70, 100, 5000); // rotates towards the third goal
    moveStop(hold);
    

  wait(0.5, seconds);
  moveLinear(50, 50, 5000); // moves towards and pushes the third goal to the other side***
    moveStop(hold);

  //wait(1, seconds);
  moveRotate(75, 100, 5000); // rotates towards the third goal probably***
    moveStop(hold);

  //wait(1, seconds);
  moveLinear(-7, 50, 5000); // moves towards the third goal probably
    moveStop(hold);

  //wait(1, seconds);
  //moveRotate(-51, 25, 3000); // rotates towards another goal
  goalCenter(SIGBLUE);
    moveStop(hold);

  wait(1, seconds);
 // moveLinear(43, 45, 3000); // moves towards the goal ...
 // wait(0, seconds);
  //claw(); // for some reason should grab a goal
  //moveLinear(-78, 60, 3000); // moves the grabbed goal away to score more points probably
  moveRotate(-50, 50, 5000);
  goalApproach(SIGBLUE, 40);
  moveLinear(-190, 100, 5000);

}

void Auton2() //right
{
  moveLinear(50, 100, 3000);
  pClaw(true);
  moveLinear(-20, 100, 3000);
}

void Auton3() //
{

  // setRotGains(0, 0, 0, 20, 10); //update PID gains to tune robot
//  setLinGains(0, 0, 0, 20, 10);
  LifterMotorL.setBrake(hold);
  LifterMotorR.setBrake(hold);

  //starting blue
  moveLinear(91, 50, 10000); //pushes goal one across the field
  moveStop(hold);
  //wait(1, seconds);

  //first yellow
  moveRotate(-170, 50, 5000); //rotate towards the second goal (yellow)
    moveStop(hold);
  goalCenter(SIGYELLOW);
  goalCenter(SIGYELLOW);

  moveLinear(60, 50, 5000); // move towards and pushes the second goal to the other side
    moveStop(hold);

  //second yellow
  moveLinear(-2, 50, 1000);
  moveRotate(120, 75, 5000); // rotates towards the third goal
    moveStop(hold);
  goalCenter(SIGYELLOW);
  goalCenter(SIGYELLOW);

  moveLinear(45, 50, 5000); // moves towards and pushes the third goal to the other side
    moveStop(hold);

  //third yellow
  moveRotate(-120, 75, 5000); // rotates towards the third goal probably
    moveStop(hold);
    goalCenter(SIGYELLOW);

  moveLinear(65, 50, 5000); // moves towards the third goal probably
    moveStop(hold);

  //last blue
  moveRotate(100, 75, 5000);

  goalCenter(SIGBLUE);
    moveStop(hold);

 // moveLinear(43, 45, 3000); // moves towards the goal ...
 // wait(0, seconds);

  goalApproach(SIGBLUE, 40);
  moveLinear(-190, 100, 4000);
}