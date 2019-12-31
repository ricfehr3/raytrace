#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

#include "Scene.hpp"

struct RendererOptions
{
    RendererOptions(int w, int h)
    {
        width = w;
        height = h;
    }

    RendererOptions()
    {
        width = 0;
        height = 0;
    }

    int width;
    int height;
};

class Renderer
{
public:
    Renderer();
    void Render(Scene scene);
    void setImageName(const std::string &imageName);
    void setOptions(const RendererOptions &options);

private:
    std::string m_imageName;
    RendererOptions m_options;
    bool m_bOptionsSet;
};

#endif
