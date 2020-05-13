#include "Math.h"

#include <algorithm>
#include <random>

#include "Random.h"

namespace RT
{
	float Vector3::LengthSq() const
	{
		return x * x + y * y + z * z;
	}

	float Vector3::Length() const
	{
		return std::sqrt(LengthSq());
	}

	void Vector3::Normalize()
	{
		const float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	Vector3 Vector3::Normalized() const
	{
		const float length = Length();
		return { x / length, y / length, z / length };
	}

	Vector3& Vector3::operator+= (const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& Vector3::operator*= (const float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	Vector3& Vector3::operator/= (const float v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	/********************************************************************/

	using RandomEngine = xorshift32;

	RandomEngine InitRNG()
	{
		std::random_device rnd_device;
		std::seed_seq seed{ rnd_device(), rnd_device(), rnd_device(), rnd_device() };
		return RandomEngine{ seed };
	}

	float random()
	{
		static thread_local auto rnd_engine = InitRNG();
		static thread_local auto distr01 = fast_canonical_float_distribution{};

		return distr01(rnd_engine);
	}

	Vector3 random_vec_in_unit_cube()
	{
		return 2.0f * Vector3{ random(), random(), random() } - Vector3{ 1, 1, 1 };
	}

	Vector3 random_direction_sphere()
	{
		Vector3 dir;
		float lengthSq;
		do {
			dir = random_vec_in_unit_cube();
			lengthSq = dir.LengthSq();
		} while (lengthSq > 1.0f);

		return dir / std::sqrt(lengthSq);
	}

	Vector3 random_direction_hemisphere(const Vector3& normal)
	{
		Vector3 dir;
		do {
			dir = random_direction_sphere();
		} while (dot(dir, normal) < 0.0f);

		return dir;
	}
}