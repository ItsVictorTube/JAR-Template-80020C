#pragma once
#include "vex.h"

#pragma region Curves Class
class Curves {
    public:
        constexpr static double cube(double x) {
            return ((x) * (x) * (x));
        }
        static double turningCurve(double x);
        static double easeInOutCubic(double x);
        static double normalize(double axis, double (*curve)(double));
    private:
        constexpr static double k = M_PI / 2;
};
#pragma endregion