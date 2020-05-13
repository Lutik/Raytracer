#pragma once

#include "Array2D.h"
#include "Scene.h"
#include "Camera.h"

namespace RT
{
	using LightMap = Array2D<Light>;

	struct Config
	{
		uint32_t rays;
		int soft_recursion;
		int hard_recursion;
		Light ambient_light;
	};

	inline constexpr Config DefaultConfig { 256, 2, 8, {0.01f, 0.01f, 0.01f} };

	LightMap Render(const Scene& scene, const Camera& camera, const Rect& screen, const Rect& area, const Config& config = DefaultConfig);

	float CalcExposition(const LightMap& lightMap);
}