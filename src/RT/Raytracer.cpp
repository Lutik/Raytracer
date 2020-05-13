#include "Raytracer.h"

#include <algorithm>

namespace RT
{
	struct RayInfo
	{
		const SceneObject* from;
		int soft_rec_limit;
		int hard_rec_limit;
	};

	Light TraceRay(const Config& config, const Ray& primaryRay, const RayInfo& ray_info)
	{
		auto hit = Intersect(config.scene, primaryRay);
		if (hit)
		{
			Light light = NoLight;
			if (ray_info.soft_rec_limit > 0 && ray_info.hard_rec_limit > 0)
			{
				const auto& traits = GetMaterialTraits(hit->obj->material);
				const uint32_t numRays = std::min(traits.max_rays, config.rays / traits.rays_div);

				const RayInfo ri{ hit->obj, ray_info.soft_rec_limit - traits.recursion_price, ray_info.hard_rec_limit - 1 };

				for (uint32_t i = 0; i < numRays; ++i) {
					auto ray = EmitRay(hit->obj->material, primaryRay, hit->hit_point);
					light += TraceRay(config, ray, ri);
				}
				light /= static_cast<float>(numRays);
			}
			return ModifyLight(hit->obj->material, light + config.ambient_light);
		}
		return NoLight;
	}

	LightMap Render(const Config& config, const Rect& area)
	{
		LightMap screen_light(area, NoLight);

		for (int y = area.y; y < area.y + area.height; ++y)
		{
			for (int x = area.x; x < area.x + area.width; ++x)
			{
				const float rx = (x + 0.5f) / config.screen.width;
				const float ry = (y + 0.5f) / config.screen.height;
				const Ray ray = config.camera.GetRay(rx, ry);
				screen_light[{x, y}] = TraceRay(config, ray, { nullptr, config.soft_recursion, config.hard_recursion });
			}
		}

		return screen_light;
	}


	float CalcExposition(const LightMap& lightMap)
	{
		float max_intensity = 0.1f;
		for (const auto& l : lightMap) {
			max_intensity = std::max({ max_intensity, l.x, l.y, l.z });
		}
		return max_intensity;
	}
}