#include <fstream>
#include <stdexcept>

#include "Renderer.hpp"

Renderer::Renderer()
{
    // set to empty for checking to see if scene should be rendered
    // The idea is that if I animate using this renderer each render should be a different image name
    // The time it takes to render is too big for me to fuck with it
    m_imageName = "";
    
    m_bOptionsSet = false;
}


void Renderer::render(const Scene &scene)
{
    if(m_imageName == "") 
        throw std::runtime_error("No image name for renderer");

    if(!scene.hasCamera()) 
        throw std::runtime_error("Scene has no camera");

    if(!scene.hasLight()) 
        throw std::runtime_error("Scene has no light");

    if(!m_bOptionsSet)
        throw std::runtime_error("Renderer options are not set");

    std::ofstream outfile;
    outfile.open("test.ppm", std::ios::out | std::ios::trunc);

    outfile << "P3\n" << m_options.width << " " << m_options.height << "\n255\n";

    for(int j = 0; j < m_options.height; j++)
    {
        for(int i = 0; i < m_options.width; i++)
        { 
            float x = (2 * (i + 0.5) / (float)m_options.width - 1) * m_options.imageAspectRatio * m_options.scale;
            float y = (1 - 2 * (j + 0.5) / (float)m_options.height) * m_options.scale;
            Vec3 dir(x, y, -1);
            Vec3 orig(0, 0, 0);
            dir = Vec3::normalize(dir);

            Ray ray = scene.m_camera.castRay(dir);
            orig = ray.origin;
            dir = ray.direction;

            int ir;
            int ig;
            int ib;

            ir = 0;
            ig = 0;
            ib = 128.0f;

            Vec3 color;
            Vec3 normal;
            //scene.m_mesh.testHit(orig, dir, scene.m_light, normal, color);
            scene.m_mesh.testHit(orig, dir, scene.m_vLights[0], normal, color);

            ir = color.x;
            ig = color.y;
            ib = color.z;

            outfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    outfile.close();
}


void Renderer::setImageName(const std::string &imageName)
{
    m_imageName = imageName;
}


void Renderer::setOptions(const RendererOptions &options)
{
    m_options = options;
    m_bOptionsSet = true;
}
