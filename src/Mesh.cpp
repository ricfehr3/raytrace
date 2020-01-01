#include <algorithm>
#include <cmath>

#include "Mesh.hpp"


struct T_HIT
{
    Vec3 hitColor;
    float distance;
};


bool Mesh::testHit(const Vec3 &origin, const Vec3 &direction, const Light &light, Vec3 &normal, Vec3 &color) const
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
                /*
                shadeScale = -shadeScale;
                color.x = int(255.99*shadeScale);
                color.y = int(255.99*shadeScale);
                color.z = int(255.99*shadeScale);
                */
                Vec3 albedo(0.0f, 1.0f, 1.0f);
                color = albedo / M_PI;
                float testing = light.intensity * std::max(0.0f, Vec3::dot(normal, light.direction));
                Vec3 tempVec3 = light.color * color;
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
