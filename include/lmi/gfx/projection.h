#ifndef LMI_PROJECTION_H
#define LMI_PROJECTION_H

#include "../detail/matrix.h"
#include <cmath>
#include <limits>

namespace lmi
{
	template <typename T>
	Matrix<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar = std::numeric_limits<T>::infinity())
	{
		auto tanHalfFovy = std::tan(fovy / T{2});
		
		// clang-format off
		return {1 / (aspect * tanHalfFovy),  0,               0,                                0,
				0,                           1 / tanHalfFovy, 0,                                0,
				0,                           0,               -(zFar + zNear) / (zFar - zNear), -(T{2} * zFar * zNear) / (zFar - zNear),
				0,                           0,               -1,                               0};
		// clang-format on
	}
}

#endif
