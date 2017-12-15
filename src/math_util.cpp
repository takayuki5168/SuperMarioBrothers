#include <iostream>
#include "include/math_util.hpp"

namespace MathUtil
{
double setInRange(double val, double max)
{
    if (val != 0 and std::abs(val) > max) {
        return val / std::abs(val) * max;
    } else {
        return val;
    }
}

double setInRange(double val, double max, double min)
{
    if (val >= max) {
        return max;
    } else if (val <= min) {
        return min;
    } else {
        return val;
    }
}

double setPlus(double val)
{
    if (val < 0) {
        val = 0;
    }
    return val;
}

double setMinus(double val)
{
    if (val > 0) {
        val = 0;
    }
    return val;
}

}  // namespace of MathUtil
