#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#include <iostream>
#include <vector>
#include "sphere.hpp"

#define w 800
#define h 450
#define ch 3
#define depth 1

vec3 rayColor(Ray r){
    hitRecord hsphere;
    Sphere s(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    if(s.hit(r, 0.0f, 10.0f, hsphere)){
        vec3 normal = hsphere.normal;
        return vec3(normal.x() + 1, normal.y() + 1, normal.z() + 1) * 0.5;
    }
    float t = 0.5f*(1.0f + r.B.makeUnitVector().y());
    return vec3(0.3f, 0.0f, 0.3f) * t + vec3(0.1f, 0.0f, 0.1f) * (1.0f - t);
}

int main(){
    unsigned char* buffer = new unsigned char[w*h*ch];

    float ratio = (float)w/(float)h;
    int image_width = w;
    int image_height = (int)((float)image_width/ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    float vheight = (float)h/100;
    float vwidth = vheight * ((float)image_width/(float)image_height);
    vec3 vu = vec3(vwidth, 0.0f, 0.0f), vv = vec3(0.0f, vheight, 0.0f);
    vec3 du = vu/image_width, dv = vv/image_height;

    float focal = (float)depth;
    vec3 cam = vec3(0.0f, 0.0f, 0.0f);

    vec3 corner = cam - vec3(0.0f, 0.0f, focal) - (vu/2) - (vv/2);
    vec3 p0 = corner + ((du + dv)*0.5);

    for(int j = 0; j < image_height; j++){
        for(int i = 0; i < image_width; i++){
            vec3 pixel = p0 + (du * i) + (dv * j);
            vec3 raydir = pixel - cam;
            Ray r(cam, raydir);

            vec3 color = rayColor(r);
            unsigned int index = ((h-j-1) * w + i) * 3;
            buffer[index + 0] = color.r() * 255;
            buffer[index + 1] = color.g() * 255;
            buffer[index + 2] = color.b() * 255;
        }
    }

    stbi_write_jpg("out.jpg", w, h, ch, buffer, 100);
}