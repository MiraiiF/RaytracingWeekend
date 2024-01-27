#ifndef GENERALHPP
    #define GENERALHPP
    #include <cmath>
    #include <iostream>
    

    //constants
    
    const float pi = 3.1415926;

    //utility
    inline float degrees_to_radians(float degrees){
        return (degrees * pi)/180;
    }

    #include "ray.hpp"
    #include "interval.hpp"
#endif