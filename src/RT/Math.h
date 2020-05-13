#pragma once

#include <cmath>

namespace RT
{
	inline constexpr float PI = 3.1415926535f;

	constexpr float deg2rad(float angle) { return angle * PI / 180.0f; }
	constexpr float rad2deg(float angle) { return angle * 180.0f / PI; }

	/********************************************************************/

	struct Vector3
	{
		float x, y, z;

		float Length() const;
		float LengthSq() const;
		void Normalize();
		Vector3 Normalized() const;

		Vector3& operator+= (const Vector3& v);
		Vector3& operator*= (const float v);
		Vector3& operator/= (const float v);
	};

	constexpr Vector3 operator+ (const Vector3& v1, const Vector3& v2) {
		return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}
	constexpr Vector3 operator- (const Vector3& v1, const Vector3& v2) {
		return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}
	constexpr Vector3 operator* (const Vector3& v, const float s) {
		return { v.x * s, v.y * s, v.z * s };
	}
	constexpr Vector3 operator/ (const Vector3& v, const float s) {
		return { v.x / s, v.y / s, v.z / s };
	}
	constexpr Vector3 operator* (const float s, const Vector3& v) {
		return { v.x * s, v.y * s, v.z * s };
	}
	constexpr Vector3 operator- (const Vector3& v) {
		return { -v.x, -v.y, -v.z };
	}

	constexpr float dot(const Vector3& v1, const Vector3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	constexpr Vector3 cross(const Vector3& v1, const Vector3& v2) {
		return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	}

	inline constexpr Vector3 UnitVecX { 1, 0, 0 };
	inline constexpr Vector3 UnitVecY { 0, 1, 0 };
	inline constexpr Vector3 UnitVecZ { 0, 0, 1 };

	/********************************************************************/

	struct Rect
	{
		int x, y, width, height;
	};

	/********************************************************************/

	constexpr float lerp(float a, float b, float t) { return a + (b - a) * t; }

	float random();
	inline float random(float min, float max) { return lerp(min, max, random()); }

	Vector3 random_direction_sphere();
	Vector3 random_direction_hemisphere(const Vector3& normal);
}