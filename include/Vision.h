/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature REDSIG = vex::vision::signature (1, 5933, 8607, 7270, -969, -631, -800, 1, 0);
vex::vision::signature BLUESIG = vex::vision::signature (2, -2935, -1681, -2308, 5777, 10923, 8350, 1, 0);
vex::vision::signature YELLOWSIG = vex::vision::signature (3, -1, 955, 477, -3449, -2671, -3060, 1, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT12, 40, REDSIG, BLUESIG, YELLOWSIG, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/