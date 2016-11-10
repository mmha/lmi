#ifndef LMI_MATRIX_H
#define LMI_MATRIX_H

#include <cstdint>
#include <tuple>
#include <type_traits>

#include "defines.h"
#include "vector.h"
//#include "../algorithm/decomposition.h"

namespace lmi
{
	template <size_t COLS, size_t ROWS, typename T = float>
	class Matrix
	{
		public:
		constexpr Matrix() = default;

		constexpr explicit Matrix(T y)
		{
			for(unsigned int i = 0; i < COLS; ++i)
				for(unsigned int j = 0; j < ROWS; ++j)
				{
					if(i == j)
						col[i][j] = y;
					else
						col[i][j] = T{};
				}
		}

		constexpr operator T *()
		{
			return &col[0][0];
		}

		constexpr operator const T *() const
		{
			return &col[0][0];
		}

		constexpr Matrix(const Vector<ROWS, T> &other)
			: col{other}
		{
			static_assert(COLS == 1, "Cannot convert a Matrix with more than one column to a Vector");
		}

		constexpr operator Vector<ROWS, T>() const
		{
			static_assert(COLS == 1, "Cannot convert a Matrix with more than one column to a Vector");
			return col[0];
		}

		template <typename... E,
				  typename = typename std::enable_if_t<(ROWS * COLS != 0) && ((sizeof...(E) == ROWS * COLS))>>
		constexpr Matrix(E &&... args)
		{
			fillArray(0, std::forward<E>(args)...);
		}

		constexpr Vector<ROWS, T> &operator[](size_t i)
		{
			return col[i];
		}

		constexpr const Vector<ROWS, T> &operator[](size_t i) const
		{
			return col[i];
		}

		constexpr Matrix operator+(const T other) const
		{
			return Matrix(*this) += other;
		}

		constexpr friend Matrix operator+(const T other, const Matrix &m)
		{
			return m + other;
		}

		constexpr Matrix operator-(const T other) const
		{
			return Matrix(*this) -= other;
		}

		constexpr friend Matrix operator-(const T other, const Matrix &m)
		{
			return m - other;
		}

		constexpr Matrix operator*(const T other) const
		{
			return Matrix(*this) *= other;
		}

		constexpr friend Matrix operator*(const T other, const Matrix &m)
		{
			return m * other;
		}

		constexpr Matrix operator/(const T other) const
		{
			return Matrix(*this) /= other;
		}

		constexpr friend Matrix operator/(const T other, const Matrix &m)
		{
			return m / other;
		}

		constexpr Matrix operator+(const Matrix &other) const
		{
			return Matrix(*this) += other;
		}

		constexpr Matrix operator-(const Matrix &other) const
		{
			return Matrix(*this) -= other;
		}

		constexpr Vector<ROWS, T> operator*(const Vector<ROWS, T> &other) const
		{
			return operator*<1>(other);
		}

		template <size_t OTHERCOLS>
		constexpr Matrix<OTHERCOLS, ROWS, T> operator*(const Matrix<OTHERCOLS, COLS, T> &other) const
		{
			Matrix<OTHERCOLS, ROWS, T> res(T{});

			for(size_t k = 0; k < COLS; ++k)
			for(size_t j = 0; j < OTHERCOLS; ++j)
			for(size_t i = 0; i < ROWS; ++i)
			{
				res[j][i] += col[k][i] * other[j][k];
			}

			return res;
		}

		constexpr Matrix &operator+=(const T other)
		{
			for(unsigned int i = 0; i < ROWS; ++i)
			{
				col[i] = col[i] + other;
			}
			return *this;
		}

		constexpr friend Matrix &operator+=(const T other, const Matrix &m)
		{
			return m += other;
		}

		constexpr Matrix &operator-=(const T other)
		{
			for(unsigned int i = 0; i < ROWS; ++i)
			{
				col[i] = col[i] + other;
			}
			return *this;
		}

		constexpr friend Matrix &operator-=(const T other, const Matrix &m)
		{
			return m -= other;
		}

		constexpr Matrix &operator*=(const T other)
		{
			for(unsigned int i = 0; i < ROWS; ++i)
			{
				col[i] = col[i] * other;
			}
			return *this;
		}

		constexpr friend Matrix &operator*=(const T other, const Matrix &m)
		{
			return m *= other;
		}

		constexpr Matrix &operator/=(const T other)
		{
			for(unsigned int i = 0; i < ROWS; ++i)
			{
				col[i] = col[i] / other;
			}
			return *this;
		}

		constexpr friend Matrix &operator/=(const T other, const Matrix &m)
		{
			return m /= other;
		}

		constexpr Matrix &operator+=(const Matrix &other)
		{
			for(unsigned int i = 0; i < ROWS; ++i)
			{
				col[i] = col[i] + other[i];
			}
			return *this;
		}

		constexpr Matrix &operator-=(const Matrix &other)
		{
			for(unsigned int i = 0; i < ROWS; ++i)
			{
				col[i] = col[i] - other[i];
			}
			return *this;
		}

		constexpr Matrix &operator*=(const Matrix &other)
		{
			for(unsigned int i = 0; i < ROWS; ++i)
			{
				col[i] = col[i] * other[i];
			}
			return *this;
		}

		private:
		constexpr void fillArray(size_t)
		{
		}

		template <typename U, typename... E>
		constexpr void fillArray(size_t i, U &&u, E &&... e)
		{
			col[i % COLS][i / COLS] = std::forward<U>(u);
			fillArray(i + 1, std::forward<E>(e)...);
		}

		Vector<ROWS, T> col[COLS];
	};

	template <typename T, size_t DIM>
	constexpr T det(const Matrix<DIM, DIM, T> &m)
	{
		/*auto LU = algorithm::LUDecompose(m);
		T det = LU[0][0]
		for (int i = 1; i < DIM; ++i)
		{
			det *= LU[i][i];
		}
		return det;*/
		return T{};
	}

	template <typename T>
	constexpr T det(const Matrix<2, 2, T> &m)
	{
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}

	template <typename T>
	constexpr T det(const Matrix<3, 3, T> &m)
	{
		return dot(m[0], cross(m[1], m[2]));
	}

	template <size_t ROWS, size_t COLS, typename T>
	constexpr Matrix<COLS, ROWS, T> transpose(const Matrix<ROWS, COLS, T> &m)
	{
		Matrix<COLS, ROWS, T> res;
		for(size_t i = 0; i < ROWS; ++i)
		for(size_t j = 0; j < COLS; ++j)
		{
			res[j][i] = m[i][j];
		}
		return res;
	}

	// FIXME needs Pivoting
	template <size_t DIM, typename T>
	constexpr Matrix<DIM, DIM, T> inverse(const Matrix<DIM, DIM, T> &m)
	{
		Matrix<DIM, DIM, T> res(1), cpy(m);
		for(size_t i = 0; i < DIM; ++i)
		{
			res[i] /= cpy[i][i];
			cpy[i] /= cpy[i][i];
			for(size_t j = 0; j < DIM; ++j)
			{
				if(i == j)
					continue;
				res[j] -= res[i] * cpy[j][i];
				cpy[j] -= cpy[i] * cpy[j][i];
			}
		}

		return res;
	}

	template <typename T>
	constexpr Matrix<2, 2, T> inverse(const Matrix<2, 2, T> &m)
	{
		return Matrix<2, 2, T>(m[1][1], -m[1][0], -m[0][1], m[0][0]) / det(m);
	}

	template <typename T>
	constexpr Matrix<3, 3, T> inverse(const Matrix<3, 3, T> &m)
	{
		Matrix<3, 3, T> res;
		res[0] = cross(m[1], m[2]);
		res[1] = cross(m[2], m[0]);
		res[2] = cross(m[0], m[1]);
		res /= det(m);
		return transpose(res);
	}
	/*
	template<typename T>
	Matrix<4, 4, T> inverse(const Matrix<4, 4, T> &m)
	{
		auto trM = transpose(m);

	}
	*/
	using mat2 = Matrix<2, 2, float>;
	using mat2x2 = Matrix<2, 2, float>;
	using mat2x3 = Matrix<2, 3, float>;
	using mat2x4 = Matrix<2, 4, float>;
	using mat3x2 = Matrix<3, 2, float>;
	using mat3 = Matrix<3, 3, float>;
	using mat3x3 = Matrix<3, 3, float>;
	using mat3x4 = Matrix<3, 4, float>;
	using mat4x2 = Matrix<4, 2, float>;
	using mat4x3 = Matrix<4, 3, float>;
	using mat4 = Matrix<4, 4, float>;
	using mat4x4 = Matrix<4, 4, float>;
}

#endif
