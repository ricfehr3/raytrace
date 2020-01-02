#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>

#include "Mesh.hpp"
#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "Camera.hpp"
#include "HitableObject.hpp"
#include "HitableMeshObject.hpp"

// forward declare for friend class
class Renderer;

// I feel that the scene object should only be described in as a list of meshes and lights.
// All rendering functionality should be handled by a separate object.
// I may need to fix some methods with the triangle and what not. Maybe move the detect hit functionality higher to the renderer.

class Scene
{
public:
	Scene();

    void addMesh(const Mesh &mesh);
    void addHitableObject(std::shared_ptr<HitableObject> hitableObject);
    void addLight(std::shared_ptr<Light> &light);
    void addCamera(const Camera &camera);
    bool hasCamera() const;
    bool hasLight() const;

private:
    friend class Renderer;
    Mesh m_mesh; 
    std::vector<std::shared_ptr<HitableObject>> m_vHitables;
    std::vector<std::shared_ptr<Light>> m_vLights;
    //DirectionalLight m_light;
    Camera m_camera;
    bool m_bHasCamera;
    bool m_bHasLight;
};

#endif
