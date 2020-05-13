#pragma once

#include "RT/Types.h"

namespace RT
{
	struct Sphere
	{
		Vector3 center;
		float radius;
	};

	std::optional<HitPoint> Intersect(const Sphere& sphere, const Ray& ray);
}