#pragma once

#include "Types.h"

namespace RT
{
	struct Camera
	{
	public:
		Camera(Vector3 pos, Vector3 dir, Vector3 up, float fov, float aspect);

		Vector3 position;
		Vector3 direction;
		Vector3 up;

		float fov;
		float aspect;

		Ray GetRay(float x, float y) const;

	private:
		Vector3 screen_origin;
		Vector3 screen_x;
		Vector3 screen_y;
	};

	
}
