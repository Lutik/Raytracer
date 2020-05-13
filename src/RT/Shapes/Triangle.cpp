#include "Triangle.h"

namespace RT
{
	std::optional<HitPoint> Intersect(const Triangle& tri, const Ray& ray)
	{
        constexpr float EPSILON = 0.0000001f;

        const Vector3 edge1 = tri.v1 - tri.v0;
        const Vector3 edge2 = tri.v2 - tri.v0;

        Vector3 h = cross(ray.direction, edge2);
        float a = dot(edge1, h);


        if (a > -EPSILON && a < EPSILON)
            return std::nullopt;    // This ray is parallel to this triangle.


        float f = 1.0f / a;
        Vector3 s = ray.origin - tri.v0;
        float u = f * dot(s, h);
        if (u < 0.0 || u > 1.0)
            return std::nullopt;

        Vector3 q = cross(s, edge1);
        float v = f * dot(ray.direction, q);
        if (v < 0.0 || u + v > 1.0)
            return std::nullopt;

        // At this stage we can compute t to find out where the intersection point is on the line.
        float t = f * dot(edge2, q);
        if (t > EPSILON) // ray intersection
        {
            Vector3 position = ray.origin + ray.direction * t;
            Vector3 normal = cross(edge1, edge2).Normalized();
            return HitPoint{ position, normal };
        }
        else // This means that there is a line intersection but not a ray intersection.
            return std::nullopt;
	}
}