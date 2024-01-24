#ifndef VEC3HPP
#define VEC3HPP
#include <math.h>
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
};

vec3 operator+(const vec3& v1, const vec3& v2);
vec3 operator-(const vec3& v1, const vec3& v2);
vec3 operator*(const vec3& v1, const vec3& v2);
vec3 operator/(const vec3& v1, const vec3& v2);

float dot(const vec3 &v1, const vec3 &v2);
vec3 cross(const vec3 &v1, const vec3 &v2);

inline std::ostream& operator<<(std::ostream& s, vec3 v){
        s << "( " << v.e[0] << ", " << v.e[1] << ", " << v.e[2] << " )";
        return s;
}
#endif