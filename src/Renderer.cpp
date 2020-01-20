#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "Renderer.hpp"
#include "Ray.hpp"
#include "HitType.hpp"

Renderer::Renderer()
{
    // set to empty for checking to see if scene should be rendered
    // The idea is that if I animate using this renderer each render should be a different image name
    // The time it takes to render is too big for me to fuck with it
    m_imageName = "";
    
    m_bOptionsSet = false;
    //m_scene = Scene();
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

            int ir = std::min(255.0, m_options.backgroundColor.r*(255.99));
            int ig = std::min(255.0, m_options.backgroundColor.g*(255.99));
            int ib = std::min(255.0, m_options.backgroundColor.b*(255.99));

            Vec3 color;
            Vec3 normal;

            //scene.m_mesh.testHit(ray, scene.m_vLights[0], normal, color);

            float distance;
            bool isHit = false;
            int hitCount = 0;
            std::vector<T_HIT> vHitRecords;
            Vec3 finalNormal;
            Vec3 hitPoint;
            for(auto& it : scene.m_vHitables)
            {
                int depth = 0;
                if(it->testHit(ray, normal, distance))
                {
                    color.x = 0;
                    color.y = 0;
                    color.z = 0;
                    
                    isHit = true;
                    T_HIT record;


                    for(auto& lightItr : scene.m_vLights)
                    {
                        Vec3 lightIntensity;
                        Vec3 lightDirection;
                        float lightDistance;
                        hitPoint = ray.origin + ray.direction * distance;
                        lightItr->getDirectionAndIntensity(hitPoint, lightDirection, lightIntensity, lightDistance);

                        bool inShadow = false;
                        // calculate shadows, epic time:
                        // first, make a ray
                        Ray shadowRay;
                        // second, find the origin
                        // the math should make sense intuitively
                        Vec3 shadowOrigin = hitPoint + normal * 1e-4;
                        // third, get the direction
                        // subtract the shadow origin from the light source position and normalize
                        Vec3 shadowDirection = Vec3::normalize(-lightDirection);
                        shadowRay.origin = shadowOrigin;
                        shadowRay.direction = shadowDirection;
                        Vec3 shadowNormal;
                        float shadowDistance;
                        // fourth, run through the scene and determine if a hit happens
                        for(auto& hitable : scene.m_vHitables)
                        {
                            if(hitable->testHit(shadowRay, shadowDistance) && shadowDistance < lightDistance)
                            {
                                inShadow = true;
                            } 
                            else
                            {
                                Vec3 colorTemp;
                                Vec3 dumbTest;
                                dumbTest.x = it->material.albedo.r;  
                                dumbTest.y = it->material.albedo.g;  
                                dumbTest.z = it->material.albedo.b;  

                                colorTemp = dumbTest / M_PI * lightIntensity * std::max(0.0f, Vec3::dot(normal, -lightDirection));

                                color.x += int(255.99*colorTemp.x);
                                color.y += int(255.99*colorTemp.y);
                                color.z += int(255.99*colorTemp.z);

                                if(color.x > 255)
                                    color.x = 255;
                                if(color.y > 255)
                                    color.y = 255;
                                if(color.z > 255)
                                    color.z = 255;
                            }
                        }
                    }

                    record.color = color;
                    record.distance = distance;
                    vHitRecords.push_back(record); 
                    hitCount++;
                } 
            }

            // determine closest hit
            if(hitCount > 1)
            { 
                std::sort(vHitRecords.begin(), vHitRecords.end(), [](const T_HIT &lhs, const T_HIT &rhs)
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


void Renderer::setScene(std::unique_ptr<Scene> scene)
{
    m_scene = std::move(scene);
}


bool Renderer::trace(const Ray &ray, HitInfo &hitInfo)
{
    bool isHit = false;
    float oldDistance = std::numeric_limits<float>::infinity();
    float distance;
    Vec3 normal;

    for(auto& hitable : m_scene->m_vHitables)
    {
        if(isHit = (hitable->testHit(ray, normal, distance)))
        {
            if(distance < oldDistance)
            {
                hitInfo.distance = distance;
                hitInfo.normal = normal;
                hitInfo.object = hitable.get();
            }
        }
    } 

    return isHit;
}


bool Renderer::castRay(const Ray &ray)
{
    bool isHit = false;
    HitInfo hitInfo; 
    if(trace(ray, hitInfo))
    {
        for(auto& lightItr : m_scene->m_vLights)
        {
            Vec3 color;
            Vec3 lightIntensity;
            Vec3 lightDirection;
            float lightDistance;
            Vec3 hitPoint = ray.origin + ray.direction * hitInfo.distance;
            lightItr->getDirectionAndIntensity(hitPoint, lightDirection, lightIntensity, lightDistance);

            Ray shadowRay;
            Vec3 shadowOrigin = hitPoint + hitInfo.normal * 1e-4;
            Vec3 shadowDirection = Vec3::normalize(-lightDirection);
            shadowRay.origin = shadowOrigin;
            shadowRay.direction = shadowDirection;
            float shadowDistance;
            
            if(hitInfo.object->testHit(shadowRay, shadowDistance) && shadowDistance < lightDistance)
            {
                //inShadow = true;
            } 
            else
            {
                Vec3 dumbTest;
                dumbTest.x = hitInfo.object->material.albedo.r;  
                dumbTest.y = hitInfo.object->material.albedo.g;  
                dumbTest.z = hitInfo.object->material.albedo.b;  

                color = dumbTest / M_PI * lightIntensity * std::max(0.0f, Vec3::dot(hitInfo.normal, -lightDirection));

                if(color.x > 255)
                    color.x = 255;
                if(color.y > 255)
                    color.y = 255;
                if(color.z > 255)
                    color.z = 255;
            }
        }
    }
}


Vec3 Renderer::reflect(const Vec3 &I, const Vec3 &N)
{
    return I - 2 * Vec3::dot(I, N) * N;
}
