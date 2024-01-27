#ifndef INTERVALHPP
    #define INTERVALHPP
    #include <limits>
    const float infinity = std::numeric_limits<float>::infinity();
    class interval{
        public:
        float min, max;
        interval() : min(infinity), max(-infinity){}
        interval(float mint, float maxt): min(mint), max(maxt){}
        bool contains(float x){
            return min <= x && max >= x;
        }
        bool surrounds(float x){
            return min < x && max > x;
        }
        float clamp(float x){
            if(x < min) {return min;} else if(x > max) return max; 
            return x;
        }
    };
    const static interval empty, universe(-infinity, infinity);
#endif