#pragma once

#include <vector>

#include "Shape.h"
#include "Material.h"

namespace RT
{
	struct SceneObject
	{
		Shape shape;
		Material material;
	};

	using Scene = std::vector<SceneObject>;


	struct HitResult {
		HitPoint hit_point;
		const SceneObject* obj;
	};

	std::optional<HitResult> Intersect(const SceneObject& obj, const Ray& ray);
	std::optional<HitResult> Intersect(const Scene& scene, const Ray& ray);
}