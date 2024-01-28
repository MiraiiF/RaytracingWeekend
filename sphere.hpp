#ifndef SPHEREHPP
    #define SPHEREHPP
    #include "hittable.hpp"
    class Sphere : public Hittable{
        vec3 C;
        float R;
        std::shared_ptr<Material> M;
        public:
        Sphere(vec3 center, float radius, std::shared_ptr<Material> mat) : C(center), R(radius), M(mat){}

        bool hit(Ray& r, interval t, hitRecord& rec) const override{
            vec3 diff = r.A - C;
            float a = r.B.squared_length();
            float hb = dot(diff, r.B);
            float c = diff.squared_length() - R*R;
            float delta = hb*hb - a * c;

            if(delta < 0) return false;
            float sqrtdelta = sqrt(delta);
            float root = (-hb - sqrtdelta)/a;
            if(!t.surrounds(root)){
                root = (-hb + sqrtdelta)/a;
                if(!t.surrounds(root)) return false;
            }
            rec.t = root;
            rec.p = r.point(rec.t);
            vec3 normal = (rec.p - C)/R;
            rec.setFaceNormal(r, normal);
            rec.mat = M;

            return true;
        }
    };
#endif