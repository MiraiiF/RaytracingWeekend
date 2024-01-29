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

        float reflectance(float cos, float ref_idx){
            float r0 = (1 - ref_idx)/(1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1-cos), 5);
        }
        public:
        Dieletric(float ref_idx) : ref(ref_idx){}
        bool scatter(Ray in, hitRecord& rec, vec3& att, Ray& scattered) override {
            vec3 albedo = vec3(1.0f, 1.0f, 1.0f);
            float ref_ratio = rec.front_face ? (1.0f/ref) : ref;
            vec3 dir = in.B.makeUnitVector();

            float cosT = fmin(dot(-dir, rec.normal), 1.0f);
            float senT = sqrt(1.0f - cosT * cosT);

            vec3 scatterdir;

            if(ref_ratio * senT > 1.0f || reflectance(cosT, ref_ratio) > random_float()){
                scatterdir = reflect(dir, rec.normal);
            } else{
                scatterdir = refract(dir, rec.normal, ref_ratio);
            }

            scatterdir = refract(dir, rec.normal, ref_ratio);

            scattered = Ray(rec.p, scatterdir);
            return true;
        }
    };
#endif