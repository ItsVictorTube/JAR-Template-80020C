using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

extern controller Controller;

extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;

extern motor LiftRight;
extern motor LiftLeft;
extern motor_group LeftDrive;
extern motor_group RightDrive;

extern digital_out ClawSolenoid;
extern digital_out FlipperSolenoid;

extern Drive chassis;
extern Lift lift;