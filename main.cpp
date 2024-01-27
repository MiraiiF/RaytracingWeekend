#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "camera.hpp"
#include "sphere.hpp"

#define w 800
#define h 450
#define depth 1

int main(){
    Camera c;
    c.image_width = w;
    c.ratio = (float)w/(float)h;
    c.n_channels = CH_RGB;
    c.quad_depth = depth;
    c.nsamples = 100;
    c.max_depth = 50;
    

    hittableList world;
    world.add(std::make_shared<Sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
    world.add(std::make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f));

    
    c.render(world);
    
}