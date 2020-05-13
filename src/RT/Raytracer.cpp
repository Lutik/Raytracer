#include "Raytracer.h"

#include <algorithm>

namespace RT
{
	Light TraceRay(const Scene& scene, const Ray& primaryRay, int soft_rec_limit, int hard_rec_limit, const Config& config)
	{
		auto hit = Intersect(scene, primaryRay);
		if (hit)
		{
			Light light = NoLight;
			if (soft_rec_limit > 0 && hard_rec_limit > 0)
			{
				const auto& traits = GetMaterialTraits(hit->obj->material);
				const uint32_t numRays = std::min(traits.max_rays, config.rays / traits.rays_div);

				for (int i = 0; i < numRays; ++i) {
					auto ray = EmitRay(hit->obj->material, primaryRay, hit->hit_point);
					light += TraceRay(scene, ray, soft_rec_limit - 1, hard_rec_limit - 1, config);
				}
				light /= numRays;
			}
			return ModifyLight(hit->obj->material, light + config.ambient_light);
		}
		return NoLight;
	}

	LightMap Render(const Scene& scene, const Camera& camera, const Rect& screen, const Rect& area, const Config& config)
	{
		LightMap screen_light(area, NoLight);

		for (int y = area.y; y < area.y + area.height; ++y)
		{
			for (int x = area.x; x < area.x + area.width; ++x)
			{
				const float rx = (x + 0.5f) / screen.width;
				const float ry = (y + 0.5f) / screen.height;
				const Ray ray = camera.GetRay(rx, ry);
				screen_light[{x, y}] = TraceRay(scene, ray, config.soft_recursion, config.hard_recursion, config);
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