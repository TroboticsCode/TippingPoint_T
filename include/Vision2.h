/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature BLUESIG2 = vex::vision::signature (1, -1949, -1337, -1643, 4481, 6111, 5296, 2.9, 0);
vex::vision::signature REDSIG2 = vex::vision::signature (2, 6677, 7211, 6944, -871, -591, -731, 2.5, 0);
vex::vision::signature YELLOWSIG2 = vex::vision::signature (3, -291, 1693, 701, -3459, -2783, -3121, 1.3, 0);
vex::vision::signature SIG_8 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_9 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_10 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_11 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision2 = vex::vision (vex::PORT14, 50, BLUESIG2, REDSIG2, YELLOWSIG2, SIG_8, SIG_9, SIG_10, SIG_11);
/*vex-vision-config:end*/