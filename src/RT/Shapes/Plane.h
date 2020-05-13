#pragma once

#include "RT/Types.h"

namespace RT
{
	struct Plane
	{
		Plane(const Vector3& p, const Vector3& n)
			: origin(p)
			, normal(n.Normalized())
		{}

		Vector3 origin;
		Vector3 normal;
	};

	std::optional<HitPoint> Intersect(const Plane& plane, const Ray& ray);
}
