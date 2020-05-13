#include "Raytracer.h"

#include <algorithm>

namespace RT
{
	Light TraceRay(const Scene& scene, const Ray& primaryRay, int rec_limit)
	{
		constexpr Light AmbientLight{ 1.0f, 1.0f, 1.0f };
		constexpr uint32_t NumRays = 128;

		auto hit = Intersect(scene, primaryRay);
		if (hit)
		{
			Light light = NoLight;
			if (rec_limit > 0)
			{
				
				for (int i = 0; i < NumRays; ++i) {
					auto ray = EmitRay(hit->obj->material, primaryRay, hit->hit_point);
					light += TraceRay(scene, ray, rec_limit - 1);
				}
				light /= NumRays;
			}
			return ModifyLight(hit->obj->material, light + AmbientLight);
		}
		return NoLight;
	}

	LightMap Render(const Scene& scene, const Camera& camera, const Rect& screen)
	{
		LightMap screen_light(screen, NoLight);

		for (int y = screen.y; y < screen.y + screen.height; ++y)
		{
			for (int x = screen.x; x < screen.x + screen.width; ++x)
			{
				const float rx = (x + 0.5f) / screen.width;
				const float ry = (y + 0.5f) / screen.height;
				const Ray ray = camera.GetRay(rx, ry);
				screen_light[{x, y}] = TraceRay(scene, ray, 1);
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