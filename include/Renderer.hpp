#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <cmath>

#include "Scene.hpp"
#include "MathHelper.hpp"
#include "Color.hpp"

struct RendererOptions
{
    RendererOptions(int w, int h, float fov)
    {
        width = w;
        height = h;
        this->fov = fov;
        scale = tan(MathHelper::deg2rad(fov * 0.5));
        imageAspectRatio = width/(float)height;
        backgroundColor = Color(0.0f, 0.0f, 0.0f);
    }

    RendererOptions()
    {
        width = 640;
        height = 480;
        fov = 51.52;
        scale = tan(MathHelper::deg2rad(fov * 0.5));
        imageAspectRatio = width/(float)height;
        backgroundColor = Color(0.0f, 0.0f, 0.0f);
    }

    int width;
    int height;
    float fov;
    float scale;
    float imageAspectRatio;
    Color backgroundColor;
};

class Renderer
{
public:
    Renderer();
    void render(const Scene &scene) const;
    void setImageName(const std::string &imageName);
    void setOptions(const RendererOptions &options);
    bool trace(const Ray &ray, float &distance);

private:
    std::string m_imageName;
    RendererOptions m_options;
    bool m_bOptionsSet;
};

#endif
