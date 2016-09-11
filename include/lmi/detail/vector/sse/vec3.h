#ifndef LMI_VEC3_SSE_H
#define LMI_VEC3_SSE_H

#include <cstdint>

#include "../../defines.h"
#include "../../vector.h"

#include <smmintrin.h>

namespace lmi
{
	template <>
	inline vec3 vec3::operator+(const float other) const
	{
		vec3 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_add_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec3 vec3::operator-(const float other) const
	{
		vec3 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec3 vec3::operator*(const float other) const
	{
		vec3 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec3 vec3::operator/(const float other) const
	{
		vec3 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_div_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec3 vec3::operator+(const vec3 &other) const
	{
		vec3 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_add_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec3 vec3::operator-(const vec3 &other) const
	{
		vec3 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec3 vec3::operator*(const vec3 &other) const
	{
		vec3 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec3 vec3::operator/(const vec3 &other) const
	{
		vec3 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_div_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec3 &vec3::operator+=(const float other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_add_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec3 &vec3::operator-=(const float other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec3 &vec3::operator*=(const float other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec3 &vec3::operator/=(const float other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_div_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec3 &vec3::operator+=(const vec3 &other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_add_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec3 &vec3::operator-=(const vec3 &other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec3 &vec3::operator*=(const vec3 &other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec3 &vec3::operator/=(const vec3 &other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_div_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	vec3 abs(const vec3 &x)
	{
		vec3 res;
		__m128i mask = _mm_set1_epi32(0x7FFFFFFF);
		__m128i v = _mm_load_si128((const __m128i *)&x);
		v = _mm_and_si128(v, mask);
		_mm_store_si128((__m128i *)&res, v);
		return res;
	}

	auto length(const vec3 &x) -> std::decay_t<decltype(x[0])>
	{
		__m128 v = _mm_load_ps(x);
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v, v, 0x77)));
	}

	auto dot(const vec3 &x, const vec3 &y) -> std::decay_t<decltype(x[0])>
	{
		return _mm_cvtss_f32(_mm_dp_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]), 0x77));
	}

	vec3 cross(const vec3 &x, const vec3 &y)
	{
		vec3 res;
		__m128 xreg = _mm_load_ps(x);
		__m128 yreg = _mm_load_ps(y);
		__m128 v = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(xreg, xreg, _MM_SHUFFLE(3, 0, 2, 1)),
										 _mm_shuffle_ps(yreg, yreg, _MM_SHUFFLE(3, 1, 0, 2))),
							  _mm_mul_ps(_mm_shuffle_ps(xreg, xreg, _MM_SHUFFLE(3, 1, 0, 2)),
										 _mm_shuffle_ps(yreg, yreg, _MM_SHUFFLE(3, 0, 2, 1))));

		_mm_store_ps(res, v);
		return res;
	}
}

#endif