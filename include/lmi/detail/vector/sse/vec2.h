#ifndef LMI_VEC2_SSE_H
#define LMI_VEC2_SSE_H

#include <cstdint>

#include "../../defines.h"
#include "../../vector.h"

#include <smmintrin.h>

namespace lmi
{
	template <>
	inline vec2 vec2::operator+(const float other) const
	{
		vec2 res;
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_add_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)res, v);
		return res;
	}

	template <>
	inline vec2 vec2::operator-(const float other) const
	{
		vec2 res;
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)res, v);
		return res;
	}

	template <>
	inline vec2 vec2::operator*(const float other) const
	{
		vec2 res;
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)res, v);
		return res;
	}

	template <>
	inline vec2 vec2::operator/(const float other) const
	{
		vec2 res;
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_div_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)res, v);
		return res;
	}

	template <>
	inline vec2 vec2::operator+(const vec2 &other) const
	{
		vec2 res;
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)other);
		v = _mm_add_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)res, v);
		return res;
	}

	template <>
	inline vec2 vec2::operator-(const vec2 &other) const
	{
		vec2 res;
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)other);
		v = _mm_sub_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)res, v);
		return res;
	}

	template <>
	inline vec2 vec2::operator*(const vec2 &other) const
	{
		vec2 res;
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)other);
		v = _mm_mul_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)res, v);
		return res;
	}

	template <>
	inline vec2 vec2::operator/(const vec2 &other) const
	{
		vec2 res;
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)other);
		v = _mm_div_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)res, v);
		return res;
	}

	template <>
	inline vec2 &vec2::operator+=(const float other)
	{
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_add_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)*this, v);
		return *this;
	}

	template <>
	inline vec2 &vec2::operator-=(const float other)
	{
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_sub_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)*this, v);
		return *this;
	}

	template <>
	inline vec2 &vec2::operator*=(const float other)
	{
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_mul_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)*this, v);
		return *this;
	}

	template <>
	inline vec2 &vec2::operator/=(const float other)
	{
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_set1_ps(other);
		v = _mm_div_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)*this, v);
		return *this;
	}

	template <>
	inline vec2 &vec2::operator+=(const vec2 &other)
	{
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)other);
		v = _mm_add_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)*this, v);
		return *this;
	}

	template <>
	inline vec2 &vec2::operator-=(const vec2 &other)
	{
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)other);
		v = _mm_sub_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)*this, v);
		return *this;
	}

	template <>
	inline vec2 &vec2::operator*=(const vec2 &other)
	{
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)other);
		v = _mm_mul_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)*this, v);
		return *this;
	}

	template <>
	inline vec2 &vec2::operator/=(const vec2 &other)
	{
		__m128 v = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)*this);
		__m128 o = _mm_loadl_pi(_mm_setzero_ps(), (const __m64 *)(const float *)other);
		v = _mm_div_ps(v, o);
		_mm_storel_pi((__m64 *)(float *)*this, v);
		return *this;
	}

	template <>
	inline vec2 abs(const vec2 &x)
	{
		vec2 res;
		__m128i mask = _mm_set1_epi32(0x7FFFFFFF);
		__m128i v = _mm_loadl_epi64((const __m128i *)&x[0]);
		v = _mm_and_si128(v, mask);
		_mm_storel_epi64((__m128i *)(float *)res, v);
		return res;
	}

	inline auto length(const vec2 &x) -> std::decay_t<decltype(x[0])>
	{
		__m128 v = _mm_load_ps(x);
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v, v, 0x33)));
	}

	inline auto dot(const vec2 &x, const vec2 &y) -> std::decay_t<decltype(x[0])>
	{
		return _mm_cvtss_f32(_mm_dp_ps(_mm_load_ps(x), _mm_load_ps(y), 0x33));
	}
}

#endif