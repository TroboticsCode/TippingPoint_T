#include "vex.h"
#include "DriveFunctionsConfig.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LifterMotorL = motor(PORT4, GREEN, false);
motor LifterMotorR = motor(PORT2, GREEN, true);
motor ForkLiftMotor = motor(PORT6, GREEN, true);
motor PincherMotor = motor(PORT13, GREEN, false);

pot armPot = pot(Brain.ThreeWirePort.D);
//bumper clawBumper = bumper();


// VEXcode generated functions


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}