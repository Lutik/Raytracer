#pragma once

#include "Math.h"

#include <optional>
#include <variant>

namespace RT
{
	struct Ray
	{
		Vector3 origin;
		Vector3 direction;
	};

	struct HitPoint
	{
		Vector3 position;
		Vector3 normal;
	};

	struct Color
	{
		float r, g, b;

		operator Vector3() const { return { r,g,b }; }
	};

	using Light = Vector3;

	inline constexpr Light NoLight{ 0, 0, 0 };
}