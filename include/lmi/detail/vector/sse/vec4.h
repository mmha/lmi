#ifndef LMI_VEC4_SSE_H
#define LMI_VEC4_SSE_H

#include <cstdint>

#include "../../defines.h"
#include "../../vector.h"

#include <smmintrin.h>

namespace lmi
{
	template <>
	inline vec4 vec4::operator+(const float other) const
	{
		vec4 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_add_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec4 vec4::operator-(const float other) const
	{
		vec4 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec4 vec4::operator*(const float other) const
	{
		vec4 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec4 vec4::operator/(const float other) const
	{
		vec4 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_div_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec4 vec4::operator+(const vec4 &other) const
	{
		vec4 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_add_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec4 vec4::operator-(const vec4 &other) const
	{
		vec4 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec4 vec4::operator*(const vec4 &other) const
	{
		vec4 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec4 vec4::operator/(const vec4 &other) const
	{
		vec4 res;
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_div_ps(v, o);
		_mm_store_ps(res, v);
		return res;
	}

	template <>
	inline vec4 &vec4::operator+=(const float other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_add_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec4 &vec4::operator-=(const float other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec4 &vec4::operator*=(const float other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec4 &vec4::operator/=(const float other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_div_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec4 &vec4::operator+=(const vec4 &other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_add_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec4 &vec4::operator-=(const vec4 &other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec4 &vec4::operator*=(const vec4 &other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec4 &vec4::operator/=(const vec4 &other)
	{
		__m128 v = _mm_load_ps(*this);
		__m128 o = _mm_load_ps(other);
		v = _mm_div_ps(v, o);
		_mm_store_ps(*this, v);
		return *this;
	}

	template <>
	inline vec4 abs(const vec4 &x)
	{
		vec4 res;
		__m128i mask = _mm_set1_epi32(0x7FFFFFFF);
		__m128i v = _mm_load_si128((__m128i *)&x);
		v = _mm_and_si128(v, mask);
		_mm_store_si128((__m128i *)&res, v);
		return res;
	}

	template <>
	inline auto length(const vec4 &x) -> std::decay_t<decltype(x[0])>
	{
		__m128 v = _mm_load_ps(x);
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v, v, 0xF1)));
	}

	template <>
	inline auto dot(const vec4 &x, const vec4 &y) -> std::decay_t<decltype(x[0])>
	{
		return _mm_cvtss_f32(_mm_dp_ps(_mm_load_ps(x), _mm_load_ps(y), 0xF1));
	}
}

#endif