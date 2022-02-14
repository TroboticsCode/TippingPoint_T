#include "vex.h"
#include "gps.h"
#include "DriveFunctionsConfig.h"

int coordinates[5][5] = { //update the [][] when a new pair is added
  {0,0},      //yellowLeft
  {10,10},    //yellowCenter
  {20,20},    //yellowRight
  {30,30},    //redBalance
  {40,40},    //blueBalance
};

//calculates the heading in degrees to reach a desired point
//current position and heading are taken from the GPS sensor
int calculateHeading(int xDest, int yDest)
{
  int xCur = (int)GPS.xPosition(inches);
  int yCur = (int)GPS.yPosition(inches);
  int headingCur = (int)GPS.heading(degrees);

  int headingDest = atan2((xCur-xDest), (yCur-yDest));

  int rotDeg = headingCur - headingDest;

  return rotDeg;
}

//find the absolute distance between two points in inches
//current position is taken from the GPS sensor
uint32_t calculateDistance(int xDest, int yDest)
{
  int xCur = (int)GPS.xPosition(inches);
  int yCur = (int)GPS.yPosition(inches);

  return (uint32_t)sqrt(pow((xDest-xCur),2)+pow((yDest-yCur),2));
}

void movePoint(int xDest, int yDest)
{
  moveRotate(calculateHeading(xDest, yDest), 100, 3000);
  moveStop(hold);

  wait(100, msec); //wait a moment to steady

  moveLinear(calculateDistance(xDest, yDest), 100, 20000);
  moveStop(hold);
}