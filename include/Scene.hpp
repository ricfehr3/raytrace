#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "Mesh.hpp"
#include "Light.hpp"
#include "Camera.hpp"

// I feel that the scene object should only be described in as a list of meshes and lights.
// All rendering functionality should be handled by a separate object.
// I may need to fix some methods with the triangle and what not. Maybe move the detect hit functionality higher to the renderer.

class Scene
{
public:
	Scene();

    void addMesh(const Mesh &mesh);
    void addLight(const Light &light);
    void addCamera(const Camera &camera);
    bool hasCamera();

private:
    Mesh m_mesh; 
    Light m_light;
    Camera m_camera;
    bool m_bHasCamera;
};

#endif
