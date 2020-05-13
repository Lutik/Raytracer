#pragma once

#include "RT/Types.h"

namespace RT
{
	struct MtMirror {};

	Ray EmitRay(const MtMirror& material, const Ray& incoming, const HitPoint& hit);
	Light ModifyLight(const MtMirror& material, const Light& light);
}