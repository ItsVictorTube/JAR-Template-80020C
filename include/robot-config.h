#pragma once

extern vex::brain Brain;

extern vex::inertial Inertial;
extern vex::controller Controller;

extern vex::motor LeftFront;
extern vex::motor LeftBack;
extern vex::motor RightFront;
extern vex::motor RightBack;
extern vex::motor_group LeftDrive;
extern vex::motor_group RightDrive;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit();
