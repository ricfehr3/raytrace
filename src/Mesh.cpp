#include <algorithm>
#include <cmath>

#include "Mesh.hpp"
#include "HitType.hpp"


bool Mesh::testHit(const Ray &ray, Vec3 &normal, float &distance) const
{
    std::vector<T_HIT> vHits;
    bool isHit = false;
    int hitCount = 0;

    for (auto& it : tris) 
    {
        if(it.testHit(ray.origin, ray.direction, normal, distance))
        {
            float shadeScale = Vec3::dot(ray.direction, normal);
            if(shadeScale < 0)
            {
                isHit = true;
                T_HIT hit;
                hit.distance = distance;
                hit.normal = normal;
                hitCount++;
                vHits.push_back(hit);
            }
        }
    }

    // determine closest hit
    if(hitCount > 1)
    { 
        std::sort(vHits.begin(), vHits.end(), [](const T_HIT &lhs, const T_HIT &rhs)
                {
                    return lhs.distance < rhs.distance;
                });
    }

    if(isHit)
    {
        distance = vHits.front().distance;
        normal = vHits.front().normal;
    }

    return isHit;
}


bool Mesh::testHit(const Ray &ray, float &distance) const
{
    std::vector<T_HIT> vHits;
    bool isHit = false;
    int hitCount = 0;
    Vec3 normal;

    for (auto& it : tris) 
    {
        if(it.testHit(ray.origin, ray.direction, normal, distance))
        {
            isHit = true;
            T_HIT hit;
            hit.distance = distance;
            hit.normal = normal;
            hitCount++;
            vHits.push_back(hit);
        }
    }

    // determine closest hit
    if(hitCount > 1)
    { 
        std::sort(vHits.begin(), vHits.end(), [](const T_HIT &lhs, const T_HIT &rhs)
                {
                    return lhs.distance < rhs.distance;
                });
    }

    if(isHit)
    {
        distance = vHits.front().distance;
        normal = vHits.front().normal;
    }

    return isHit;
}
