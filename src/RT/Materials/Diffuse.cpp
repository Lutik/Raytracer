#include "Diffuse.h"

namespace RT
{
	Ray EmitRay(const MtLambert& material, const Ray&, const HitPoint& hit)
	{
		const Vector3 dir = hit.normal + random_direction_sphere();
		return { hit.position, dir.Normalized() };
	}

	Light ModifyLight(const MtLambert& material, const Light& light)
	{
		return { light.x * material.color.r, light.y * material.color.g, light.z * material.color.b };
	}
}