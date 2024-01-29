#ifndef CAMERAHPP
    #define CAMERAHPP
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include <stb/stb_image_write.h>
    #include "general.hpp"
    #include "hittableList.hpp"
    #include "material.hpp"
    enum ch_type{NONE, CH_R, CH_RG, CH_RGB, CH_RGBA};

    static interval colorSpace(0.0f, 255.0f);

    void writeBuffer(vec3& color, unsigned char* buffer, unsigned int index, unsigned int nsamples){
        float scale = 1.0f/(float)nsamples;
        float r = pow(color.r() * scale, 1.0/2.2);
        float g = pow(color.g() * scale, 1.0/2.2);
        float b = pow(color.b() * scale, 1.0/2.2);
        buffer[index + 0] = (unsigned char)colorSpace.clamp(r * 255.0f);
        buffer[index + 1] = (unsigned char)colorSpace.clamp(g * 255.0f);
        buffer[index + 2] = (unsigned char)colorSpace.clamp(b * 255.0f);
    }

    class Camera{
        public:
        int image_width;
        ch_type n_channels;
        float ratio;
        int quad_depth;
        unsigned int max_depth = 10;
        unsigned int nsamples = 10;
        float vfov = 90;
        vec3 lookfrom = vec3(0.0f, 0.0f, 0.0f);
        vec3 lookat = vec3(0.0f, 0.0f, -1.0f);
        vec3 up = vec3(0.0f, 1.0f, 0.0f);
        void render(hittableList& world){
            initialize();
            unsigned char* buffer = new unsigned char[image_width*image_height*(int)n_channels];
            for(int j = 0; j < image_height; j++){
                for(int i = 0; i < image_width; i++){
                    vec3 color = vec3(0.0f, 0.0f, 0.0f);
                    for(int s = 0; s < nsamples; s++){
                        Ray r = getRayByIndex(i, j);
                        color = color + rayColor(r, max_depth, world);
                    }
                    unsigned int index = ((image_height-j-1) * image_width + i) * 3;
                    writeBuffer(color, buffer, index, nsamples);
                }
            }
            stbi_write_jpg("out.jpg", image_width, image_height, (int)n_channels, buffer, 100);
            delete buffer;
        }
        private:
        int image_height;
        vec3 dv;
        vec3 du;
        float focal;
        vec3 cam;
        vec3 p0;
        vec3 u, v, w;
        void initialize(){
            image_width = image_width;
            image_height = (int)((float)image_width/ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            cam = lookfrom;

            focal = (lookfrom - lookat).length();
            float theta = degrees_to_radians(vfov);
            float h = tan(theta/2.0f);
            float vheight = 2 * h * focal;
            
            float vwidth = vheight * ((float)image_width/(float)image_height);

            w = (lookfrom - lookat).makeUnitVector();
            u = cross(up, w).makeUnitVector();
            v = cross(w, u);

            vec3 vu = u * vwidth, vv = -v * vheight;
            du = vu/image_width, dv = vv/image_height;

            vec3 corner = cam - (w * focal) - (vu/2) - (vv/2);
            p0 = corner + ((du + dv)*0.5);
        }
        vec3 rayColor(Ray r, unsigned int depth, hittableList& world){
            if(depth <= 0) return vec3(0.0f, 0.0f, 0.0f);
            hitRecord rec;
            if(world.hit(r, interval(0.001f, infinity), rec)){
                Ray scattered;
                vec3 attenuation;
                if(rec.mat->scatter(r, rec, attenuation, scattered)){
                    return rayColor(scattered, depth - 1, world) * attenuation;
                } else return vec3(0.0f, 0.0f, 0.0f);
            }
            float t = 0.5f*(1.0f + r.B.makeUnitVector().y());
            return vec3(0.5f, 0.0f, 0.5f) * t + vec3(1.0f, 1.0f, 1.0f) * (1.0f - t);
        }
        Ray getRayByIndex(int i, int j){
            vec3 pixel = p0 + (du * i) + (dv * j);
            vec3 pixel_sample = pixel + randomSample();

            vec3 raydir = pixel_sample - cam;
            return Ray(cam, raydir);
        }
        vec3 randomSample(){
            float px = -0.5 + random_float();
            float py = -0.5 + random_float();
            return (du * px) + (dv * py);
        }
    };
#endif