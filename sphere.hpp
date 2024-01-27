#ifndef SPHEREHPP
    #define SPHEREHPP
    #include "hittable.hpp"
    class Sphere : public Hittable{
        vec3 C;
        float R;
        public:
        Sphere(vec3 center, float radius) : C(center), R(radius){}

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

            return true;
        }
    };
#endif