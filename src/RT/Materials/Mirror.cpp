#include "Mirror.h"

namespace RT
{
	Ray EmitRay(const MtMirror& material, const Ray& incoming, const HitPoint& hit)
	{
		return { hit.position, reflect(incoming.direction, hit.normal).Normalized() };
	}

	Light ModifyLight(const MtMirror& material, const Light& light)
	{
		return light;
	}
}