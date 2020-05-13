#include "Plane.h"

namespace RT
{
	std::optional<HitPoint> Intersect(const Plane& plane, const Ray& ray)
	{
        const float denom = dot(-plane.normal, ray.direction);
        if (denom > 1e-6) {
            Vector3 p0l0 = plane.origin - ray.origin;
            const float t = dot(p0l0, -plane.normal) / denom;
            if (t >= 0.0f) {
                return HitPoint{ ray.origin + ray.direction * t, plane.normal };
            }
        }

        return std::nullopt;
	}
}