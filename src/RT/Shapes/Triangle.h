#pragma once

#include "RT/Types.h"

namespace RT
{
	struct Triangle
	{
		Vector3 v0;
		Vector3 v1;
		Vector3 v2;
	};

	std::optional<HitPoint> Intersect(const Triangle& triangle, const Ray& ray);
}
