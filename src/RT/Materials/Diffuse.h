#pragma once

#include "RT/Types.h"

namespace RT
{
	struct MtLambert
	{
		Color color;
	};

	using MtDiffuse = MtLambert;

	Ray EmitRay(const MtLambert& material, const Ray& incoming, const HitPoint& hit);
	Light ModifyLight(const MtLambert& material, const Light& light);
}