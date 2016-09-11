#pragma once

#include <type_traits>

#include "../defines.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

namespace lmi
{
	namespace detail
	{
		constexpr auto roundToNextPower(size_t v)
		{
			return ((v - 1) | (v >> 1) | (v >> 2) | (v >> 4) | (v >> 8) | (v >> 16)) + 1;
		}

		constexpr auto alignIfSIMD(size_t v)
		{
			return simd_alignment ? roundToNextPower(v) : 1;
		}

		template <size_t DIM, typename T>
		struct alignas(alignIfSIMD(DIM) * sizeof(T)) VectorBase
		{
			union {
				T vals[roundToNextPower(DIM)];
			};
		};

		template <typename T>
		struct alignas(alignIfSIMD(2) * sizeof(T)) VectorBase<2, T>
		{
			union {
				T vals[2];
				struct
				{
					T x, y;
				};
				struct
				{
					T s, t;
				};
				struct
				{
					T u, v;
				};
			};
		};

		template <typename T>
		struct alignas(alignIfSIMD(3) * sizeof(T)) VectorBase<3, T>
		{
			union {
				T vals[3];
				struct
				{
					T x, y, z;
				};
				struct
				{
					T r, g, b;
				};
			};
		};

		template <typename T>
		struct alignas(alignIfSIMD(4) * sizeof(T)) VectorBase<4, T>
		{
			union {
				T vals[4];
				struct
				{
					T x, y, z, w;
				};
				struct
				{
					T r, g, b, a;
				};
			};
		};
	}
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
