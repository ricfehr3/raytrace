#include "Renderer.hpp"

Renderer::Renderer()
{
    // set to empty for checking to see if scene should be rendered
    // The idea is that if I animate using this renderer each render should be a different image name
    // The time it takes to render is too big for me to fuck with it
    m_imageName = "";
    
    m_bOptionsSet = false;
}


void Renderer::Render(Scene scene)
{
    if(m_imageName == "") 
        throw "No image name for renderer";

    if(!scene.hasCamera()) 
        throw "Scene has no camera";

    if(!m_bOptionsSet)
        throw "Renderer options are not set";


    for(int j = 0; j < m_options.height; j++)
    {
        for(int i = 0; i < m_options.width; i++)
        {
            /*
            float x = (2 * (i + 0.5) / (float)width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)height) * scale;
            Vec3 dir(x, y, -1);
            Vec3 orig(0, 0, 0);
            dir = Vec3::normalize(dir);

            Ray ray = cam.castRay(dir);
            orig = ray.origin;
            dir = ray.direction;

            float r;
            float g;
            float b;
            int ir;
            int ig;
            int ib;

            ir = 0;
            ig = 0;
            ib = 128.0f;

            Vec3 color;
            Vec3 normal;
            mesh.testHit(orig, dir, normal, color);

            ir = color.x;
            ig = color.y;
            ib = color.z;

            outfile << ir << " " << ig << " " << ib << "\n";
            */
        }
    }
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
