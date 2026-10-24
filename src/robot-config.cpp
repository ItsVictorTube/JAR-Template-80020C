#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:
inertial Inertial(PORT20);
controller Controller(primary);
motor LeftFront(PORT1, ratio18_1, true);
motor LeftBack(PORT2, ratio18_1, true);
motor RightFront(PORT3, ratio18_1, false);
motor RightBack(PORT4, ratio18_1, false);
motor_group LeftDrive(LeftBack, LeftFront);
motor_group RightDrive(RightBack, RightFront);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit();