#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
#include <chrono>
       
#include "OBJParser.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Ray.hpp"
#include "HitableObject.hpp"
#include "HitableMeshObject.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "Color.hpp"

int main() 
{
    Mesh mesh;
    Mesh mesh2;
    OBJParser::ParseMesh("centered_sphere.obj", mesh);
    OBJParser::ParseMesh("floor.obj", mesh2);

    //Vec3 camDir(0.5f, 0.5f, -1.0f);
    Vec3 camDir(0.0f, 1.0f, -1.0f);
    //Vec3 camDir(0.0f, 0.0f, -1.0f);
    //Camera cam(Vec3(2.0f, 2.0f, 0.0f), Vec3::normalize(camDir), 0.1, 100);
    Camera cam(Vec3(0.0f, 5.0f, 5.0f), Vec3::normalize(camDir), 0.1, 100);
    //Camera cam(Vec3(0.0f, 0.0f, 0.0f), Vec3::normalize(camDir), 0.1, 100);

    Vec3 lightColor(1.0f, 1.0f, 1.0f);
    Vec3 lightPos(0.0f, 0.0f, 0.0f);
    Vec3 lightDir(0.1f, 1.5f, 0.0f);
    //Vec3 lightDir(1.0f, 2.5f, 1.0f);
    float lightIntensity = 1.0f;
    DirectionalLight light;
    light.color = lightColor;
    light.position = lightPos;
    light.direction = lightDir;
    light.intensity = lightIntensity;

    //auto lightUniqPtr = std::make_unique<Light>(light);
    
    HitableMeshObject hitable;
    HitableMeshObject hitable2;
    hitable.material.albedo = Color(1.0f, 0.0f, 0.0f); 
    hitable2.material.albedo = Color(0.0f, 0.0f, 1.0f); 
    hitable.setMesh(mesh);
    hitable2.setMesh(mesh2);
    //auto hitablePtr = std::make_unique<HitableMeshObject>(hitable);
    //auto fuck = std::dynamic_pointer_cast<HitableObject>(hitablePtr);
    //auto hitablePtr2 = std::make_unique<HitableMeshObject>(hitable2);
    //auto fuck2 = std::dynamic_pointer_cast<HitableObject>(hitablePtr2);
        
    Scene scene;
    //scene.addMesh(mesh);
    scene.addHitableObject(std::unique_ptr<HitableObject>(new HitableMeshObject(hitable)));
    scene.addHitableObject(std::unique_ptr<HitableObject>(new HitableMeshObject(hitable2)));
    //scene.addHitableObject(fuck2);
    scene.addCamera(cam);
    scene.addLight(std::unique_ptr<Light>(new DirectionalLight(light)));

    Renderer renderer;
    RendererOptions options;
    renderer.setOptions(options);
    renderer.setImageName("test.ppm");

    auto t1 = std::chrono::high_resolution_clock::now();
    try
    {
        renderer.render(scene); 
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught Exception: " << e.what() << std::endl;
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "that took uh.... " << duration << " milliseconds" << std::endl;
}
