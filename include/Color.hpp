#ifndef COLOR_HPP
#define COLOR_HPP

// In my head a color is different than a vector, so it gets its own class
class Color
{
public:
    Color(float r, float g, float b);
    Color() : Color(0.0f, 0.0f, 0.0f) {}

    float r,g,b;
private:

};

#endif
