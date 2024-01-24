#ifndef RAYHPP
    #define RAYHPP
    #include "vec3.hpp"

    class Ray{
        public:
        vec3 A, B;
        Ray(){}
        Ray(const vec3& a, const vec3& b) : A(a), B(b) {}
        vec3 origin() {return A;}
        vec3 point(float t){return B*t + A;}
    };

#endif
