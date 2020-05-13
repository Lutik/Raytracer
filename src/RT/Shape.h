#pragma once

#include "Shapes/Sphere.h"

namespace RT
{
	using Shape = std::variant<Sphere>;

	inline std::optional<HitPoint> Intersect(const Shape& shape, const Ray& ray)
	{
		auto visitor = [&ray](const auto& shape) { return Intersect(shape, ray); };
		return std::visit(visitor, shape);
	}
}