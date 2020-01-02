#ifndef HITABLEMESHOBJECT_HPP
#define HITABLEMESHOBJECT_HPP

#include "HitableObject.hpp"
#include "Mesh.hpp"

class HitableMeshObject : public HitableObject
{
public:
    HitableMeshObject();
    bool testHit(const Ray &ray, Vec3 &normal, float &distance);
    bool testHit(const Ray& ray);

    void setMesh(const Mesh &mesh);

private:
    Mesh m_mesh;
};

#endif
