#include "Light.h"

namespace RT
{
	Ray EmitRay(const MtLight& material, const Ray& incoming, const HitPoint& hit)
	{
		return { hit.position, hit.normal };
	}

	Light ModifyLight(const MtLight& material, const Light&)
	{
		return material.light;
	}
}