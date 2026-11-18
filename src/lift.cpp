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

void Lift::lift_zero(){
  int timer = 0;
  if(!LiftBumper.pressing() && timer < 1500){
    lift_with_voltage(-3.5);
    task::sleep(10);
    timer += 10;
  }
  Lift::lift_stop(vex::brakeType::hold);

  LiftL.resetPosition();
  LiftR.resetPosition();

  controller(primary).rumble("-");
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

void Lift::rise_to_height(float height){
  Lift::rise_to_height(height, lift_max_voltage, lift_settle_error, lift_settle_time, lift_timeout, lift_kp, lift_ki, lift_kd, lift_starti);
}

void Lift::rise_to_height(float height, float lift_max_voltage){
  Lift::rise_to_height(height, lift_max_voltage, lift_settle_error, lift_settle_time, lift_timeout, lift_kp, lift_ki, lift_kd, lift_starti);
}

void Lift::rise_to_height(float height, float lift_max_voltage, float lift_settle_error, float lift_settle_time, float lift_timeout){
  Lift::rise_to_height(height, lift_max_voltage, lift_settle_error, lift_settle_time, lift_timeout, lift_kp, lift_ki, lift_kd, lift_starti);
}

void Lift::rise_to_height(float height, float lift_max_voltage, float lift_settle_error, float lift_settle_time, float lift_timeout, float lift_kp, float lift_ki, float lift_kd, float lift_starti){
  PID liftPID(height, lift_kp, lift_ki, lift_kd, lift_starti, lift_settle_error, lift_settle_time, lift_timeout);
  float average_position = (LiftL.position(deg)+LiftR.position(deg))/2.0;
  while (liftPID.is_settled() == false){
    average_position = (LiftL.position(deg)+LiftR.position(deg))/2.0;
    float lift_error = height - average_position;
    float lift_output = liftPID.compute(lift_error);
    lift_output = clamp(lift_output, -lift_max_voltage, lift_max_voltage);
    lift_with_voltage(lift_output);
    task::sleep(10);
  }
  Lift::lift_stop(vex::brakeType::hold);
}

void Lift::control_lift(float lift_max_voltage, float lift_down_max_voltage){
  if (controller(primary).ButtonR1.pressing()){
    Lift::lift_with_voltage(lift_max_voltage);
  } else if (controller(primary).ButtonR2.pressing()){
    if (!LiftBumper.pressing()){
      Lift::lift_with_voltage(-lift_down_max_voltage);
    } else {
      Lift::lift_stop(vex::brakeType::hold);
      LiftL.resetPosition();
      LiftR.resetPosition();
    }
  } else {
    Lift::lift_stop(vex::brakeType::hold);
  }
}
