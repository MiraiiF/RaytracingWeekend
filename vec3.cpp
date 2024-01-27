#include "vec3.hpp"

vec3 vec3::makeUnitVector(){
    return *this / this->length();
}

vec3 operator+(const vec3& v1, const vec3& v2){
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

vec3 operator-(const vec3& v1, const vec3& v2){
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

vec3 operator*(const vec3& v1, const vec3& v2){
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

vec3 operator/(const vec3& v1, const vec3& v2){
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

float dot(const vec3 &v1, const vec3 &v2){
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

vec3 cross(const vec3 &v1, const vec3 &v2){
    return vec3(
        v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
      -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
        v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
    );
}

vec3 flipIfInverted(vec3& reference, const vec3& checking){
    if(dot(checking, reference) > 0.0f){
        return checking;
    } else return -checking;
}