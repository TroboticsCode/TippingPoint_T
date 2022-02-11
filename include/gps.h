#ifndef GPS_H
#define GPS_H

#define xCOR 0
#define yCOR 1

typedef enum
{
  yellowLeft,
  yellowCenter,
  yellowRight,
  blueBalance,
  redBalance
} eCoors;

//stored as x,y pairs
extern int coordinates[5][5];

int calculateHeading(int xDest, int yDest);
uint32_t calculateDistance(int xDest, int yDest);
void movePoint(int xDest, int yDest);

#endif