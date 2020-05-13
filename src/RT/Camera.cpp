#include "Camera.h"

namespace RT
{
	Camera::Camera(Vector3 pos, Vector3 dir, Vector3 u, float f, float a)
		: position(pos)
		, direction(dir.Normalized())
		, up(u)
		, fov(f)
		, aspect(a)
	{
		float width = aspect;
		float dist = width / std::tan(0.5f * fov);

		Vector3 center = position + direction * dist;

		Vector3 right = cross(up, direction).Normalized();

		up = cross(direction, right).Normalized();

		screen_origin = center - 0.5f * aspect * right + 0.5f * up;
		screen_x = right * aspect;
		screen_y = -up;
	}

	Ray Camera::GetRay(float x, float y) const
	{
		const Vector3 pos = screen_origin + screen_x * x + screen_y * y;
		return { position, (pos - position).Normalized() };
	}
}