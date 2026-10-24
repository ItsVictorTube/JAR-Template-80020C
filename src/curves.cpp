#include "curves.h"

#pragma region Curves Class
double Curves::turningCurve(double x) {
    return sin(k * sin(k * x)) / sin(k);
}
double Curves::easeInOutCubic(double x) {
    return x < 0.5 ? 4 * cube(x) : 1 - cube(-2 * x + 2) / 2;
}
double Curves::normalize(double axis, double (*curve)(double)) {
    if (curve != nullptr) {
        double sign = axis < 0? -1.0 : 1.0;

        double normalized = abs(axis) / 127.0;
        return 127.0 * curve(normalized) * sign;
    } else {
        return axis;
    }
}
#pragma endregion