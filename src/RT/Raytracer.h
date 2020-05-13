#pragma once

#include "Array2D.h"
#include "Scene.h"
#include "Camera.h"

namespace RT
{
	using LightMap = Array2D<Light>;

	struct Config
	{
		const Scene& scene;
		const Camera& camera;
		Rect screen;

		uint32_t rays{ 256 };
		int soft_recursion{ 2 };
		int hard_recursion{ 8 };
		Light ambient_light{ 0.01f, 0.01f, 0.01f };
	};

	LightMap Render(const Config& config, const Rect& area);

	float CalcExposition(const LightMap& lightMap);
}