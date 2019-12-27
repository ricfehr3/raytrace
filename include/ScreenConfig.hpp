#ifndef SCREENCONFIG_HPP
#define SCREENCONFIG_HPP

struct ScreenConfig
{
    ScreenConfig(int width, int height, float fov);
    ScreenConfig() : ScreenConfig(640, 480, 51.52f) {}
    
    int width;
    int height;
    float fov;
    float scale;
    float imageAspectRatio;
};

#endif
