#ifndef VEC3HPP
#define VEC3HPP
#include "random.hpp"
#include <ostream>

class vec3{
    public:
    float e[3];
    vec3(){}
    vec3(float f0, float f1, float f2){ e[0] = f0; e[1] = f1; e[2] = f2;}
    inline float x(){return e[0];}
    inline float y(){return e[1];}
    inline float z(){return e[2];}
    inline float r(){return e[0];}
    inline float g(){return e[1];}
    inline float b(){return e[2];}

    inline const vec3& operator+() const{return *this;}
    inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    inline float operator[](unsigned int i) const {return e[i];}
    inline float operator[](unsigned int i){return e[i];}

    inline vec3 operator*(const float &t){return vec3(e[0]*t, e[1]*t, e[2]*t);}
    inline vec3 operator/(const float &t){return vec3(e[0]/t, e[1]/t, e[2]/t);}

    inline float length() const{return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}
    inline float squared_length() const {return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
    vec3 makeUnitVector();
    static vec3 random(){return vec3(random_float(), random_float(), random_float());}
    static vec3 random(float min, float max){return vec3(random_float(min, max), random_float(min, max), random_float(min, max));}
    static vec3 randomUnit(){
        while(true){
            vec3 p = vec3::random(-1.0f, 1.0f);
            if(p.squared_length() < 1){
                return p.makeUnitVector();
            }
        }
    }
    bool isNearZero(){
        return fabs(e[0]) < 0.0001 && fabs(e[1]) < 0.0001 && fabs(e[2]) < 0.0001;
    }
};

vec3 operator+(const vec3& v1, const vec3& v2);
vec3 operator-(const vec3& v1, const vec3& v2);
vec3 operator*(const vec3& v1, const vec3& v2);
vec3 operator/(const vec3& v1, const vec3& v2);

float dot(const vec3 &v1, const vec3 &v2);
vec3 cross(const vec3 &v1, const vec3 &v2);

vec3 flipIfInverted(vec3& reference, const vec3& checking);
vec3 reflect(vec3 v, vec3& normal);
vec3 refract(vec3 v, vec3 n, float ratio);

inline std::ostream& operator<<(std::ostream& s, vec3 v){
        s << "( " << v.e[0] << ", " << v.e[1] << ", " << v.e[2] << " )";
        return s;
}
#endif