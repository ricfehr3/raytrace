#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
       
#include "OBJParser.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

int main() 
{
    Mesh mesh;
    OBJParser::ParseMesh("sphere_smooth.obj", mesh);

    //Vec3 camDir(0.5f, 0.5f, -1.0f);
    Vec3 camDir(0.0f, 0.0f, -1.0f);
    //Camera cam(Vec3(2.0f, 2.0f, 0.0f), Vec3::normalize(camDir), 0.1, 100);
    Camera cam(Vec3(0.0f, 0.0f, 0.0f), Vec3::normalize(camDir), 0.1, 100);

    Vec3 lightColor(1.0f, 1.0f, 1.0f);
    Vec3 lightPos(0.0f, 0.0f, 0.0f);
    Vec3 lightDir(1.0f, 0.5f, -1.0f);
    float lightIntensity = 1.0f;
    Light light;
    light.color = lightColor;
    light.position = lightPos;
    light.direction = lightDir;
    light.intensity = lightIntensity;

    Scene scene;
    scene.addMesh(mesh);
    scene.addCamera(cam);
    scene.addLight(light);

    Renderer renderer;
    RendererOptions options;
    renderer.setOptions(options);
    renderer.setImageName("test.ppm");

    try
    {
        renderer.render(scene); 
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught Exception: " << e.what() << std::endl;
    }
}
