#include "vex.h"
#include "Autons.h"
#include "Functions.h"
#include "DriveFunctionsConfig.h"


//Put your auton routines in here

void Auton1()
{
 // setRotGains(0, 0, 0, 20, 10); //update PID gains to tune robot
//  setLinGains(0, 0, 0, 20, 10);

  moveLinear(91, 50, 3000); //pushes goal one across the field
  wait(1, seconds);
  moveRotate(40, 25, 3000); //rotate towards the second goal
  wait(1, seconds);
  moveLinear(-77, 50, 3000); // move towards and pushes the second goal to the other side
  wait(1, seconds);
  moveRotate(-60, 25, 3000); // rotates towards the third goal
  wait(1, seconds);
  moveLinear(75, 50, 3000); // moves towards and pushes the third goal to the other side
  wait(1, seconds);
  moveRotate(55, 25, 3000); // rotates towards the third goal probably
  wait(1, seconds);
  moveLinear(-65, 50, 3000); // moves towards the third goal probably
  wait(1, seconds);
  moveRotate(-51, 25, 3000); // rotates towards another goal
  wait(1, seconds);
  moveLinear(43, 45, 3000); // moves towards the goal ...
  wait(0, seconds);
  //claw(); // for some reason should grab a goal
  moveLinear(-78, 60, 3000); // moves the grabbed goal away to score more points probably

}

void Auton2()
{

}

