#include "Scene.h"

#include <numeric>

namespace RT
{
	std::optional<HitResult> Intersect(const SceneObject& obj, const Ray& ray)
	{
		auto hit = Intersect(obj.shape, ray);
		if (hit) {
			return HitResult{ *hit, &obj };
		}
		return std::nullopt;
	}

	struct SelectClosestHit
	{
		const Ray& ray;
		const SceneObject* from;

		std::optional<HitResult> operator() (const std::optional<HitResult>& best, const SceneObject& obj) const
		{
			auto hit = (&obj != from) ? Intersect(obj, ray) : std::nullopt;
			if (!best) return hit;
			if (!hit) return best;

			const float dist_best = (best->hit_point.position - ray.origin).LengthSq();
			const float dist_hit = (hit->hit_point.position - ray.origin).LengthSq();
			return (dist_hit < dist_best) ? hit : best;
		}
	};

	std::optional<HitResult> Intersect(const Scene& scene, const Ray& ray, const SceneObject* from)
	{
		return std::accumulate(scene.begin(), scene.end(), std::optional<HitResult>{}, SelectClosestHit{ ray, from });
	}
}