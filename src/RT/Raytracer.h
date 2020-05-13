#pragma once

#include "Array2D.h"
#include "Scene.h"
#include "Camera.h"

namespace RT
{
	using LightMap = Array2D<Light>;

	LightMap Render(const Scene& scene, const Camera& camera, const Rect& screen);

	float CalcExposition(const LightMap& lightMap);
}