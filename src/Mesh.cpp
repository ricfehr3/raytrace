#include <algorithm>
#include <cmath>

#include "Mesh.hpp"


struct T_HIT
{
    Vec3 normal;
    float distance;
};


bool Mesh::testHit(const Ray &ray, Vec3& normal, float &distance) const
{
    std::vector<T_HIT> vHits;
    bool isHit = false;
    int hitCount = 0;

    for (auto& it : tris) 
    {
        if(it.testHit(ray.origin, ray.direction, normal, distance))
        {
            isHit = true;

            float shadeScale = Vec3::dot(ray.direction, normal);
            if(shadeScale < 0)
            {
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

        distance = vHits.front().distance;
        normal = vHits.front().normal;
    }

    return isHit;
}
