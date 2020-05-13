#include "RT/Types.h"

namespace RT
{
	struct MtLight
	{
		Light light{ 1.0f, 1.0f, 1.0f };
	};

	Ray EmitRay(const MtLight& material, const Ray& incoming, const HitPoint& hit);
	Light ModifyLight(const MtLight& material, const Light& light);
}