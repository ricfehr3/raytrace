#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
       
#include "OBJParser.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

int main() 
{
    Mesh mesh;
    OBJParser::ParseMesh("man_scene.obj", mesh);

    Vec3 camDir(0.5f, 0.5f, -1.0f);
    Camera cam(Vec3(2.0f, 2.0f, 0.0f), Vec3::normalize(camDir), 0.1, 100);

    Scene scene;
    scene.addMesh(mesh);
    scene.addCamera(cam);

    Renderer renderer;
    RendererOptions options;
    renderer.setOptions(options);
    renderer.setImageName("test.ppm");

    renderer.render(scene); 
}
