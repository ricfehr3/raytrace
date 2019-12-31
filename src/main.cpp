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
    std::cout << "From main... " << mesh.tris.size() << std::endl;
    std::cout << "tris v1 " << mesh.tris[0].vert[0].v << std::endl
              << "tris v2 " << mesh.tris[0].vert[1].v << std::endl
              << "tris v3 " << mesh.tris[0].vert[2].v << std::endl;

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
