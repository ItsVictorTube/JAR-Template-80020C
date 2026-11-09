#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen.
brain Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:
#pragma region configured devices
controller Controller(primary);

motor LeftFront(PORT1, ratio18_1, false);
motor LeftBack(PORT2, ratio18_1, false);
motor RightFront(PORT3, ratio18_1, true);
motor RightBack(PORT4, ratio18_1, true);

motor_group LeftDrive(LeftFront, LeftBack);
motor_group RightDrive(RightFront, RightBack);
#pragma endregion