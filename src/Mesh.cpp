#include <algorithm>

#include "Mesh.hpp"


struct T_HIT
{
    Vec3 hitColor;
    float distance;
};


bool Mesh::testHit(const Vec3 &origin, const Vec3 &direction, Vec3 &normal, Vec3 &color) const
{
    std::vector<T_HIT> hitDistances;
    bool isHit = false;
    int hitCount = 0;

    for (auto& it : tris) 
    {
        float distance = 0.0f;
        if(it.testHit(origin, direction, normal, distance))
        {
            isHit = true;

            float shadeScale = Vec3::dot(direction, normal);
            if(shadeScale < 0)
            {
                shadeScale = -shadeScale;
                color.x = int(255.99*shadeScale);
                color.y = int(255.99*shadeScale);
                color.z = int(255.99*shadeScale);
                hitCount++;
                struct T_HIT hit {color, distance};
                hitDistances.push_back(hit);
            }
        }
    }

    // determine closest hit
    if(hitCount > 1)
    { 
        std::sort(hitDistances.begin(), hitDistances.end(), [](const T_HIT &lhs, const T_HIT &rhs)
                {
                    return lhs.distance < rhs.distance;
                });

        color = hitDistances.front().hitColor;
    }

    return isHit;
}
