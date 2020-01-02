#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "Renderer.hpp"
#include "Ray.hpp"

struct HitRecord
{
    Vec3 color;
    float distance;
};

Renderer::Renderer()
{
    // set to empty for checking to see if scene should be rendered
    // The idea is that if I animate using this renderer each render should be a different image name
    // The time it takes to render is too big for me to fuck with it
    m_imageName = "";
    
    m_bOptionsSet = false;
}


void Renderer::render(const Scene &scene) const
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

    auto &light = std::move(scene.m_vLights[0]);
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

            int ir = 0;
            int ig = 0;
            int ib = 128;

            Vec3 color;
            Vec3 normal;

            //scene.m_mesh.testHit(ray, scene.m_vLights[0], normal, color);

            float distance;
            bool isHit = false;
            int hitCount = 0;
            std::vector<HitRecord> vHitRecords;
            Vec3 finalNormal;
            for(auto& it : scene.m_vHitables)
            {
                if(it->testHit(ray, normal, distance))
                {
                    isHit = true;
                    HitRecord record;
                    
                    Vec3 color;
                    Vec3 dumbTest;
                    dumbTest.x = it->material.albedo.r;  
                    dumbTest.y = it->material.albedo.g;  
                    dumbTest.z = it->material.albedo.b;  
                    color = dumbTest / M_PI;
                    float testing = light->intensity * std::max(0.0f, Vec3::dot(normal, light->direction));
                    Vec3 tempVec3 = light->color * color;

                    color = tempVec3 * testing;
                    color.x = int(255.99*color.x);
                    color.y = int(255.99*color.y);
                    color.z = int(255.99*color.z);

                    if(color.x > 255)
                        color.x = 255;
                    if(color.y > 255)
                        color.y = 255;
                    if(color.z > 255)
                        color.z = 255;

                    record.color = color;
                    record.distance = distance;
                    vHitRecords.push_back(record); 
                    hitCount++;
                } 
            }

            // determine closest hit
            if(hitCount > 1)
            { 
                std::sort(vHitRecords.begin(), vHitRecords.end(), [](const HitRecord &lhs, const HitRecord &rhs)
                        {
                            return lhs.distance < rhs.distance;
                        });
            }

            if(isHit)
            {
                ir = vHitRecords.front().color.x;
                ig = vHitRecords.front().color.y;
                ib = vHitRecords.front().color.z;
            }
            else
            {

            }

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
