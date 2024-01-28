#ifndef HITTABLEHPP
    #define HITTABLEHPP
    #include "ray.hpp"
    #include <memory>
    class Material;
    class hitRecord{
        public:
        vec3 p, normal;
        float t;
        bool front_face;
        std::shared_ptr<Material> mat;

        void setFaceNormal(Ray& r, vec3& outwardNormal){
            front_face = dot(r.B, outwardNormal) < 0;
            normal = front_face ? outwardNormal : -outwardNormal;
        }
    };

    class Hittable{
        public:
        virtual ~Hittable() = default;

        virtual bool hit(Ray& r, interval t, hitRecord& rec) const = 0;
    };
#endif