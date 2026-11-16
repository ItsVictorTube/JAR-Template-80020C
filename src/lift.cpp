#include "vex.h"

Lift::Lift(motor LiftL, motor LiftR, int LiftBumper_Port) : 
    LiftL(LiftL), 
    LiftR(LiftR), 
    LiftBumper(LiftPort.Port[to_port(LiftBumper_Port)]) 
{}

void Lift::set_lift_constants(float lift_kp, float lift_ki, float lift_kd, float lift_starti){
    this->lift_kp = lift_kp;
    this->lift_ki = lift_ki;
    this->lift_kd = lift_kd;
    this->lift_starti = lift_starti;
}

void Lift::set_lift_exit_conditions(float lift_settle_error, float lift_settle_time, float lift_timeout){
    this->lift_settle_error = lift_settle_error;
    this->lift_settle_time = lift_settle_time;
    this->lift_timeout = lift_timeout;
}
