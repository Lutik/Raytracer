#pragma once

#include "Materials/Diffuse.h"
#include "Materials/Light.h"
#include "Materials/Mirror.h"

namespace RT
{
	using Material = std::variant<MtLambert, MtLight, MtMirror>;


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


	struct MaterialTraits
	{
		uint32_t max_rays;
		uint32_t rays_div;
		int recursion_price;
	};

	namespace Traits
	{
		constexpr MaterialTraits Default = { std::numeric_limits<uint32_t>::max(), 1, 1 };
		constexpr MaterialTraits Light = { 0, 1, 1 };
		constexpr MaterialTraits Mirror = { 1, 1, 0 };

		struct Getter {
			const MaterialTraits& operator() (const MtLight&) { return Light; }
			const MaterialTraits& operator() (const MtMirror&) { return Mirror; }

			template<class Mat>
			const MaterialTraits& operator() (const Mat&) { return Default; }
		};
	}

	inline const MaterialTraits& GetMaterialTraits(const Material& mat)
	{
		return std::visit(Traits::Getter{}, mat);
	}
}