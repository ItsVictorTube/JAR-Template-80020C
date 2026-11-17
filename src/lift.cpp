#include "vex.h"

Lift::Lift(motor LiftL, motor LiftR, int LiftBumper_Port) : 
    LiftL(LiftL), 
    LiftR(LiftR), 
    LiftBumper(LiftPort.Port[to_port(LiftBumper_Port)]) 
{}

void Lift::lift_with_voltage(float voltage){
    LiftL.spin(directionType::fwd, voltage, voltageUnits::volt);
    LiftR.spin(directionType::fwd, voltage, voltageUnits::volt);
}

void Lift::lift_stop(vex::brakeType mode){
    LiftL.stop(mode);
    LiftR.stop(mode);
}

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

void Lift::set_heights(float low_height, float mid_height, float high_height){
    this->low_height = low_height;
    this->mid_height = mid_height;
    this->high_height = high_height;
}

void Lift::rise_to_height(float height, float lift_max_voltage, float lift_settle_error, float lift_settle_time, float lift_timeout, float lift_kp, float lift_ki, float lift_kd, float lift_starti){
    PID liftPID(height, lift_kp, lift_ki, lift_kd, lift_starti, lift_settle_error, lift_settle_time, lift_timeout);
}
