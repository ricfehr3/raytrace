#include "HitableMeshObject.hpp"

HitableMeshObject::HitableMeshObject()
{

}


bool HitableMeshObject::testHit(const Ray& ray, Vec3& normal, float &distance)
{
    // lmao I just realized it spells I Shit, keeping it in here forever
    bool isHit = m_mesh.testHit(ray, normal, distance);

    return isHit;
}


void HitableMeshObject::setMesh(const Mesh &mesh)
{
    m_mesh = mesh;
}

