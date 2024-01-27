#ifndef RANDOMHPP
    #define RANDOMHPP
    #include <random>
    inline float random_float(){
        std::random_device dev;
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        std::mt19937 gen(dev());
        return dist(gen);
    }

    inline float random_float(float min, float max){
        return min + (max - min) * random_float();
    }
#endif