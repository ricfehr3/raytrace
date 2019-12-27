#include <cmath>

#include "ScreenConfig.hpp"

double deg2rad (double degrees) {
        return degrees * 4.0 * atan (1.0) / 180.0;
}


ScreenConfig::ScreenConfig(int width, int height, float fov)
{
    this->width = width;
    this->height = height;
    this->fov = fov;
    scale = tan(deg2rad(fov * 0.5f));
    imageAspectRatio = width/(float)height;
}

