#include <cmath>

#include "MathHelper.hpp"

double MathHelper::deg2rad(double degrees)
{
    return degrees * 4.0 * atan (1.0) / 180.0;
}
