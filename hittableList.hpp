#ifndef HITTABLELISTHPP
    #define HITTABLELISTHPP
    #include "hittable.hpp"
    #include <memory>
    #include <vector>

    class hittableList : public Hittable{
        public:
        std::vector<std::shared_ptr<Hittable>> objects;

        hittableList(){}
        hittableList(std::shared_ptr<Hittable> object){add(object);}

        void clear(){objects.clear();}
        void add(std::shared_ptr<Hittable> object){objects.push_back(object);}

        bool hit(Ray& r, interval t, hitRecord& rec) const override{
            hitRecord placeholder;
            bool hit = false;
            float closest = t.max;

            for(const auto& object : objects){
                if(object->hit(r, interval(t.min, closest), placeholder)){
                    hit = true;
                    closest = placeholder.t;
                    rec = placeholder;
                }
            }

            return hit;
        }
    };
#endif