#pragma once

#include "Shapes/Sphere.h"
#include "Shapes/Plane.h"
#include "Shapes/Triangle.h"

namespace RT
{
	using Shape = std::variant<Sphere, Plane, Triangle>;

	inline std::optional<HitPoint> Intersect(const Shape& shape, const Ray& ray)
	{
		auto visitor = [&ray](const auto& shape) { return Intersect(shape, ray); };
		return std::visit(visitor, shape);
	}
}