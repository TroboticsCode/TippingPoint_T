#include "vex.h"
#include "DriveFunctionsConfig.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LifterMotorL = motor(PORT2, GREEN, false);
motor LifterMotorR = motor(PORT4, GREEN, true);
motor ForkLiftMotor = motor(PORT6, GREEN, true);
motor PincherMotor = motor(PORT13, GREEN, false);
pneumatics Pincher = pneumatics(Brain.ThreeWirePort.E);

pot armPot = pot(Brain.ThreeWirePort.D);
pot forkLiftPot = pot(Brain.ThreeWirePort.A);
bumper clawBumper = bumper(Brain.ThreeWirePort.B);
gps GPS = gps(PORT15);

// VEXcode generated functions


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}