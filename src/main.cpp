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
    Vec3 vapePink(1.0f, 0.5215686274509804f, 0.807843137254902f);
    Color vapeBlue(1.0f/255.0f, 205.0f/255.0f, 254.0f/255.0f);
    Vec3 vapeGreen(5.0f/255.0f, 255.0f/255.0f, 161.0f/255.0f);
    Color white(1.0f, 1.0f, 1.0f);
    Color babyBlue(0.1176470588235294, 0.796078431372549, 0.8823529411764706);
    Color blue(0.1176470588235294, 0.4156862745098039, 0.8823529411764706);
    Color seafoam(0.1176470588235294, 0.8823529411764706, 0.5882352941176471);
    Mesh mesh;
    Mesh mesh2;
    OBJParser::ParseMesh("centered_sphere.obj", mesh);
    //OBJParser::ParseMesh("plainplane.obj", mesh);
    OBJParser::ParseMesh("floor.obj", mesh2);

    //Vec3 camDir(0.5f, 0.5f, -1.0f);
    Vec3 camDir(0.0f, 0.3f, -1.0f);
    //Vec3 camDir(0.0f, 0.0f, -1.0f);
    //Camera cam(Vec3(2.0f, 2.0f, 0.0f), Vec3::normalize(camDir), 0.1, 100);
    Camera cam(Vec3(0.0f, 2.0f, 6.0f), Vec3::normalize(camDir), 0.1, 100);
    //Camera cam(Vec3(0.0f, 0.0f, 0.0f), Vec3::normalize(camDir), 0.1, 100);

    Vec3 lightColor(1.0f, 1.0f, 1.0f);
    Vec3 lightPos(-1.5f, 3.5f, -1.5f);
    Vec3 lightDir(-0.7f, -1.0f, -0.5f);
    Vec3 light2Color(1.5f, 1.0f, -1.5f);
    Vec3 light2Pos(1.5f, 3.5f, 1.5f);
    Vec3 light2Dir(-0.7f, -1.0f, -0.5f);
    //Vec3 lightDir(1.0f, 2.5f, 1.0f);
    float lightIntensity = 20.0f;
    float light2Intensity = 20.0f;
    //DirectionalLight light;
    PointLight light;
    PointLight light2;
    light.color = vapePink;
    light.position = lightPos;
    light.direction = lightDir;
    light.intensity = lightIntensity;
    light2.color = vapeGreen;
    light2.position = light2Pos;
    light2.direction = light2Dir;
    light2.intensity = light2Intensity;
    //light.radius = 1.0f;

    //auto lightUniqPtr = std::make_unique<Light>(light);
    
    HitableMeshObject hitable;
    HitableMeshObject hitable2;
    hitable.material.albedo = white; 
    hitable2.material.albedo = white; 
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
    //scene.addLight(std::unique_ptr<Light>(new DirectionalLight(light)));
    scene.addLight(std::unique_ptr<Light>(new PointLight(light)));
    scene.addLight(std::unique_ptr<Light>(new PointLight(light2)));

    Renderer renderer;
    RendererOptions options;
    options.backgroundColor = vapeBlue;
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
