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


void Scene::addLight(std::unique_ptr<Light>& light)
{
    std::cout <<
        "From Scene... " << std::endl <<
        "intensity: " << light->intensity << std::endl <<
        "direction: " << light->direction << std::endl <<
        "color:     " << light->color << std::endl <<
        "position:  " << light->position << std::endl <<
        std::endl;

    m_vLights.push_back(std::move(light));
    
    std::cout <<
        "From Scene... " << std::endl <<
        "intensity: " << m_vLights[0]->intensity << std::endl <<
        "direction: " << m_vLights[0]->direction << std::endl <<
        "color:     " << m_vLights[0]->color << std::endl <<
        "position:  " << m_vLights[0]->position << std::endl <<
        std::endl;

    //m_light = light;
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
