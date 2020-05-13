#pragma once

#include "Materials/Diffuse.h"
#include "Materials/Light.h"

namespace RT
{
	using Material = std::variant<MtLambert, MtLight>;


	inline Ray EmitRay(const Material& material, const Ray& incoming, const HitPoint& hit)
	{
		auto visitor = [&](const auto& mat) { return EmitRay(mat, incoming, hit); };
		return std::visit(visitor, material);
	}

	inline Light ModifyLight(const Material& material, const Light& light)
	{
		auto visitor = [&](const auto& mat) { return ModifyLight(mat, light); };
		return std::visit(visitor, material);
	}
}