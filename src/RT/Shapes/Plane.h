#pragma once

#include "RT/Types.h"

namespace RT
{
	struct Plane
	{
		Vector3 origin;
		Vector3 normal;
	};

	std::optional<HitPoint> Intersect(const Plane& plane, const Ray& ray);
}
