#ifndef MATERIALHPP
    #define MATERIALHPP
    #include "general.hpp"
    #include "hittable.hpp"
    class Material{
        public:
        virtual ~Material() = default;
        virtual bool scatter(Ray in, hitRecord& rec, vec3& att, Ray& scattered) = 0;
    };

    class Lambertian : public Material{
        vec3 albedo;
        public:
        Lambertian(vec3 color) : albedo(color){}

        bool scatter(Ray in, hitRecord& rec, vec3& att, Ray& scattered) override {
            vec3 scatter_dir = rec.normal + vec3::randomUnit();
            if(scatter_dir.isNearZero()) scatter_dir = rec.normal;
            scattered = Ray(rec.p, scatter_dir);
            att = albedo;
            return true;
        }
    };

    class Metal : public Material{
        vec3 albedo;
        float fuzziness;
        public:
        Metal(vec3 color, float fuzz) : albedo(color), fuzziness(fuzz){}

        bool scatter(Ray in, hitRecord& rec, vec3& att, Ray& scattered) override {
            vec3 reflected = reflect(in.B.makeUnitVector(), rec.normal);
            scattered = Ray(rec.p, reflected + (vec3::randomUnit() * fuzziness));
            att = albedo;
            return true;
        }
    };

    class Dieletric : public Material{
        float ref;
        public:
        Dieletric(float ref_idx) : ref(ref_idx){}
        bool scatter(Ray in, hitRecord& rec, vec3& att, Ray& scattered) override {
            vec3 albedo = vec3(1.0f, 1.0f, 1.0f);
            float ref_ratio = rec.front_face ? (1.0f/ref) : ref;
            vec3 dir = in.B.makeUnitVector();
            vec3 refracted = refract(dir, rec.normal, ref_ratio);

            scattered = Ray(rec.p, refracted);
            return true;
        }
    };
#endif