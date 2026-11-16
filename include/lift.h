#pragma once
#include "vex.h"

class Lift {
    private:
        float low_height;
        float mid_height;
        float high_height;
        vex::triport LiftPort = vex::triport(vex::PORT22);
    public:
        motor LiftL;
        motor LiftR;
        bumper LiftBumper;

        float lift_kp = 0;
        float lift_ki = 0;
        float lift_kd = 0;
        float lift_starti = 0;

        float lift_settle_error;
        float lift_settle_time;
        float lift_timeout;

        Lift(motor LiftL, motor LiftR, int LiftBumper_Port);

        void set_lift_constants(float lift_kp, float lift_ki, float lift_kd, float lift_starti);
        void set_lift_exit_conditions(float lift_settle_error, float lift_settle_time, float lift_timeout);

        void set_heights(float low_height, float mid_height, float high_height);
        void rise_to_height(float height);

};