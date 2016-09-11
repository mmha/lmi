#ifndef LMI_TRANSFORM_H
#define LMI_TRANSFORM_H

#include "../detail/matrix.h"
#include <cmath>
#include <cstdint>

namespace lmi
{
	template <typename... T>
	auto translate(T... params)
	{
		const auto vals = {params...};
		const auto DIM = sizeof...(T) + 1;
		using value_type = typename decltype(vals)::value_type;

		Matrix<DIM, DIM, value_type> res(1);
		size_t i = 0;
		for(auto &&v : vals)
		{
			res[DIM - 1][i] = v;
			++i;
		}
		return res;
	}

	template <typename... T>
	auto scale(T... params)
	{
		auto vals = {params...};
		const auto DIM = sizeof...(T);
		using value_type = typename decltype(vals)::value_type;

		Matrix<DIM, DIM, value_type> res(value_type{});
		size_t i = 0;
		for(auto &&v : vals)
		{
			res[i][i] = v;
			++i;
		}
		return res;
	}

	// clang-format off
	template <typename T>
	Matrix<3, 3, T> rotateX(T angle)
	{
		return Matrix<3, 3, T>
		(
			1, 0,                0,
			0, std::cos(angle), -std::sin(angle),
			0, std::sin(angle),  std::cos(angle)
		);
	}

	template <typename T>
	Matrix<3, 3, T> rotateY(T angle)
	{
		return Matrix<3, 3, T>
		(
			std::cos(angle),  0, std::sin(angle),
			0,                1, 0,
			-std::sin(angle), 0, std::cos(angle)
		);
	}

	template <typename T>
	Matrix<3, 3, T> rotateZ(T angle)
	{
		return Matrix<3, 3, T>
		(
			std::cos(angle), -std::sin(angle), 0,
			std::sin(angle),  std::cos(angle), 0,
			0,                0,               1
		);
	}

	template <typename T>
	Matrix<2, 2, T> rotateAngles(T angle)
	{
		return Matrix<2, 2, T>
		(
				std::cos(angle), -std::sin(angle),
				std::sin(angle),  std::cos(angle)
		);
	}

	template <typename T>
	Matrix<3, 3, T> rotateAngles(T yaw, T pitch, T roll)
	{
		return rotateZ(yaw) * rotateY(pitch) * rotateX(roll);
	}
	// clang-format on
}

#endif
