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


void Scene::addLight(const Light &light)
{
    m_light = light;
}


void Scene::addCamera(const Camera &camera)
{
    if(!m_bHasCamera)
        m_camera = camera;
    else
        throw "Scene already has camera";

    m_bHasCamera = true;
    m_bHasLight = true;
}


bool Scene::hasCamera() const
{
    return m_bHasCamera;
}


bool Scene::hasLight() const
{
    return m_bHasLight;
}
