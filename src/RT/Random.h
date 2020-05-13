#pragma once

class xorshift32
{
public:
	using result_type = uint32_t;

	xorshift32() : x(0) {}
	xorshift32(result_type seed) : x(seed) {}
	xorshift32(std::seed_seq& s) { s.generate(&x, &x + 1); }

	result_type operator() () {
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		return x;
	}

	static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
	static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

private:
	uint32_t x;
};

// based on algorithm from
// https://xor0110.wordpress.com/2010/09/24/how-to-generate-floating-point-random-numbers-efficiently/
class fast_canonical_float_distribution
{
public:
	using result_type = float;

	template<class Generator>
	result_type operator() (Generator& gen) {
		uint32_t v = gen();
		v = v & 0x007FFFFF | 0x3F800000;
		float f;
		std::memcpy(&f, &v, sizeof(f));
		return f - 1.0f;
	}

	static constexpr result_type min() { return 0.0f; }
	static constexpr result_type max() { return 1.0f; }
};