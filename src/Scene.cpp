#include "Scene.hpp"


Scene::Scene()
{
    m_bHasCamera = false;
    m_bHasLight = false;
}


void Scene::addMesh(const Mesh &mesh)
{
    m_mesh = mesh;
}


void Scene::addHitableObject(std::unique_ptr<HitableObject> hitableObject)
{
    m_vHitables.push_back(std::move(hitableObject));
}


void Scene::addLight(std::unique_ptr<Light>& light)
{
    m_vLights.push_back(std::move(light));
    
    m_bHasLight = true;
}


void Scene::addCamera(const Camera &camera)
{
    if(!m_bHasCamera)
        m_camera = camera;
    else
        throw "Scene already has camera";

    m_bHasCamera = true;
}


bool Scene::hasCamera() const
{
    return m_bHasCamera;
}


bool Scene::hasLight() const
{
    return m_bHasLight;
}
