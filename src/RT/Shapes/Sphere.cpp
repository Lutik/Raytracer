#include "Sphere.h"

#include "../Math.h"

namespace RT
{
    std::optional<HitPoint> Intersect(const Sphere& sphere, const Ray& ray)
    {
        const Vector3 dir = sphere.center - ray.origin;
        const float tca = dot(dir, ray.direction);
        const float d2 = dir.LengthSq() - tca * tca;
        const float radius2 = sphere.radius * sphere.radius;

        if (d2 > radius2) return std::nullopt;
        const float thc = std::sqrt(radius2 - d2);

        float t = tca - thc;
        if (t <= 0.0f) {
            //t = tca + thc;
            //if (t <= 0.0f) {
                return std::nullopt;
            //}
        }

        const Vector3 position = ray.origin + ray.direction * t;
        const Vector3 normal = (position - sphere.center).Normalized();

        return HitPoint{ position, normal };
    }
}