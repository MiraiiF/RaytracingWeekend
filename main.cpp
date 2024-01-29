#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "camera.hpp"
#include "sphere.hpp"

#define w 400
#define h 200
#define depth 1

int main(){
    Camera c;
    c.image_width = w;
    c.ratio = (float)w/(float)h;
    c.n_channels = CH_RGB;
    c.quad_depth = depth;
    c.nsamples = 100;
    c.max_depth = 50;
    c.vfov = 20;
    c.lookfrom = vec3(-2.0f, 2.0f, 1.0f);
    c.lookat = vec3(0.0f, 0.0f, -1.0f);
    c.up = vec3(0.0f, -1.0f, 0.0f);

    std::shared_ptr<Material> ground = std::make_shared<Lambertian>(vec3(0.3f, 0.8f, 0.0f));
    std::shared_ptr<Material> main = std::make_shared<Lambertian>(vec3(0.7f, 0.3f, 0.7f));
    std::shared_ptr<Material> reflective = std::make_shared<Metal>(vec3(0.8f, 0.8f, 0.8f), 0.0f);
    std::shared_ptr<Material> metallic = std::make_shared<Metal>(vec3(0.8f, 0.8f, 0.8f), 0.5f);
    

    hittableList world;
    world.add(std::make_shared<Sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f, main));
    world.add(std::make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f, ground));
    world.add(std::make_shared<Sphere>(vec3(1.0f, 0.0f, -1.0f), -0.5f, reflective));
    world.add(std::make_shared<Sphere>(vec3(-1.0f, 0.0f, -1.0f), 0.5f, metallic));

    
    c.render(world);
    
}