#include "vex.h"
#include "Autons.h"
#include "Functions.h"
#include "DriveFunctionsConfig.h"


//Put your auton routines in here

void Auton1()
{
 // setRotGains(0, 0, 0, 20, 10); //update PID gains to tune robot
//  setLinGains(0, 0, 0, 20, 10);

  moveLinear(1, 50, 10000);

  //Arm(10);
}

void Auton2()
{
  moveLinear(84, 50, 10000);
  moveRotate(20, 50, 10000);
  moveLinear(60, 50, 10000);
}

