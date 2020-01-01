#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <cmath>

#include "Scene.hpp"
#include "MathHelper.hpp"

struct RendererOptions
{
    RendererOptions(int w, int h, float fov)
    {
        width = w;
        height = h;
        this->fov = fov;
        scale = tan(MathHelper::deg2rad(fov * 0.5));
        imageAspectRatio = width/(float)height;
    }

    RendererOptions()
    {
        width = 640;
        height = 480;
        fov = 51.52;
        scale = tan(MathHelper::deg2rad(fov * 0.5));
        imageAspectRatio = width/(float)height;
    }

    int width;
    int height;
    float fov;
    float scale;
    float imageAspectRatio;
};

class Renderer
{
public:
    Renderer();
    void render(const Scene &scene) const;
    void setImageName(const std::string &imageName);
    void setOptions(const RendererOptions &options);

private:
    std::string m_imageName;
    RendererOptions m_options;
    bool m_bOptionsSet;
};

#endif
