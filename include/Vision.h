/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature BLUESIG = vex::vision::signature (1, -1949, -1337, -1643, 4481, 6111, 5296, 2.5, 0);
vex::vision::signature REDSIG = vex::vision::signature (2, 6677, 7211, 6944, -871, -591, -731, 2.5, 0);
vex::vision::signature YELLOWSIG = vex::vision::signature (3, 1171, 1579, 1375, -2949, -2763, -2856, 5.2, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT12, 50, BLUESIG, REDSIG, YELLOWSIG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/