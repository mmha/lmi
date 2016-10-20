#ifndef LMI_QUATERNION_H
#define LMI_QUATERNION_H

#include "matrix.h"
#include "vector.h"

namespace lmi
{
	template <typename T, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
	class Quaternion
	{
		public:
		constexpr Quaternion()
			: q0(T{})
			, q1(T{})
			, q2(T{})
			, q3(T{})
		{
		}

		constexpr explicit Quaternion(T real)
			: Quaternion()
		{
			q0 = real;
		}

		constexpr explicit Quaternion(T real, const Vector<3, T> &vec)
		{
			q0 = real;
			q1 = vec[0];
			q2 = vec[1];
			q3 = vec[2];
		}

		constexpr explicit Quaternion(const Vector<3, T> &vec)
			: q0(T{})
		{
			q1 = vec[0];
			q2 = vec[1];
			q3 = vec[2];
		}

		constexpr explicit Quaternion(const lmi::Matrix<4, 4, T> &m)
		{
			q0 = m[0][0];
			q1 = m[1][0];
			q2 = m[2][0];
			q3 = m[3][0];
		}

		constexpr Quaternion(T a, T b, T c, T d)
			: q0(a)
			, q1(b)
			, q2(c)
			, q3(d)
		{
		}

		//===========================================================================
		//						OPERATORS
		//===========================================================================

		// ==================== Access operators ====================

		constexpr const T &operator[](const int i) const
		{
			if(i == 0)
			{
				return q0;
			}
			else if(i == 1)
			{
				return q1;
			}
			else if(i == 2)
			{
				return q2;
			}
			else if(i == 3)
			{
				return q3;
			}
			else
			{
				assert(!"Unexpected index");
			}
		}

		// ==================== Arithmetic operators ====================

		constexpr Quaternion operator-() const
		{
			return Quaternion(-q0, -q1, -q2, -q3);
		}

		constexpr Quaternion &operator+=(const Quaternion &rhs)
		{
			q0 += rhs.q0;
			q1 += rhs.q1;
			q2 += rhs.q2;
			q3 += rhs.q3;
			return *this;
		}

		constexpr Quaternion &operator-=(const Quaternion &rhs)
		{
			q0 -= rhs.q0;
			q1 -= rhs.q1;
			q2 -= rhs.q2;
			q3 -= rhs.q3;
			return *this;
		}

		constexpr Quaternion &operator*=(const Quaternion &rhs)
		{
			T t0 = q0, t1 = q1, t2 = q2, t3 = q3;
			q0 = t0 * rhs.q0 - t1 * rhs.q1 - t2 * rhs.q2 - t3 * rhs.q3;
			q1 = t0 * rhs.q1 + t1 * rhs.q0 + t2 * rhs.q3 - t3 * rhs.q2;
			q2 = t0 * rhs.q2 - t1 * rhs.q3 + t2 * rhs.q0 + t3 * rhs.q1;
			q3 = t0 * rhs.q3 + t1 * rhs.q2 - t2 * rhs.q1 + t3 * rhs.q0;
			return *this;
		}

		// Multiplication with scalar

		constexpr Quaternion &operator*=(const T &rhs)
		{
			q0 *= rhs;
			q1 *= rhs;
			q2 *= rhs;
			q3 *= rhs;
			return *this;
		}

		constexpr Quaternion &operator/=(const T &rhs)
		{
			q0 /= rhs;
			q1 /= rhs;
			q2 /= rhs;
			q3 /= rhs;
			return *this;
		}

		// ==================== Cast operators ====================

		constexpr explicit operator Matrix<4, 4, T>() const
		{
			// clang-format off
			return {1 -  2 * q2 * q2 - 2 * q3 * q3, 2 * q1 * q2 - 2 * q0 * q3,     2 * q1 * q3 + 2 * q0 * q2,     0,
					2 * q1 * q2 + 2 * q0 * q3,      1 - 2 * q1 * q1 - 2 * q3 * q3, 2 * q2 * q3 - 2 * q0 * q1,     0,
					2 * q1 * q3 - 2 * q0 * q2,      2 * q1 * q3 + 2 * q0 * q1,     1 - 2 * q1 * q1 - 2 * q2 * q2, 0,
					0,                              0,                             0,                             1};
			// clang-format off
		}

		//===========================================================================
		//						FUNCTIONS
		//===========================================================================

		constexpr void swap(Quaternion &other)
		{
			std::swap(this->q0, other.q0);
			std::swap(this->q1, other.q1);
			std::swap(this->q2, other.q2);
			std::swap(this->q3, other.q3);
		}

		private:
		T q0, q1, q2, q3;
	};

	//=================================================================================
	//						NON-MEMBER OPERATORS
	//=================================================================================

	// ==================== Comparison operators ====================

	template <typename T>
	constexpr bool operator==(const Quaternion<T> &lhs, const Quaternion<T> &rhs)
	{
		return (lhs[0] == rhs[0]) && (lhs[1] == rhs[1]) && (lhs[2] == rhs[2]) && (lhs[3] == rhs[3]);
	}

	template <typename T>
	constexpr bool operator!=(const Quaternion<T> &lhs, const Quaternion<T> &rhs)
	{
		return !(lhs == rhs);
	}

	// ==================== Arithmetic operators ====================

	template <typename T>
	constexpr Quaternion<T> operator+(const Quaternion<T> &lhs, const Quaternion<T> &rhs)
	{
		return (Quaternion<T>(lhs) += rhs);
	}

	template <typename T>
	constexpr Quaternion<T> operator-(const Quaternion<T> &lhs, const Quaternion<T> &rhs)
	{
		return (Quaternion<T>(lhs) -= rhs);
	}

	template <typename T>
	constexpr Quaternion<T> operator*(const Quaternion<T> &lhs, const Quaternion<T> &rhs)
	{
		return (Quaternion<T>(lhs) *= rhs);
	}

	// Multiplication with scalar

	template <typename T>
	constexpr Quaternion<T> operator*(const T &lhs, const Quaternion<T> &rhs)
	{
		return (Quaternion<T>(rhs) *= lhs);
	}

	template <typename T>
	constexpr Quaternion<T> operator*(const Quaternion<T> &lhs, const T &rhs)
	{
		return (Quaternion<T>(lhs) *= rhs);
	}

	template <typename T>
	constexpr Quaternion<T> operator/(const Quaternion<T> &lhs, const T &rhs)
	{
		return (Quaternion<T>(lhs) /= rhs);
	}

	//=================================================================================
	//						NON-MEMBER FUNCTIONS
	//=================================================================================

	// ==================== Arithmetic functions ====================

	template <typename T>
	constexpr T norm(const Quaternion<T> &q)
	{
		return sqrt(normsq(q));
	}

	template <typename T>
	constexpr T normsq(const Quaternion<T> &q)
	{
		return q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
	}

	template <typename T>
	constexpr Quaternion<T> conjugate(const Quaternion<T> &q)
	{
		return Quaternion<T>(q[0], -q[1], -q[2], -q[3]);
	}

	template <typename T>
	constexpr Quaternion<T> inverse(const Quaternion<T> &q)
	{
		return conjugate(q) / normsq(q);
	}

	template <typename T>
	constexpr Quaternion<T> normalize(const Quaternion<T> &q)
	{
		return q / norm(q);
	}

	// Real part, imaginary part

	template <typename T>
	constexpr T realPart(const Quaternion<T> &q)
	{
		return q[0];
	}

	template <typename T>
	constexpr Quaternion<T> imaginaryPart(const Quaternion<T> &q)
	{
		return Quaternion<T>(T{}, q[1], q[2], q[3]);
	}

	// same as imaginaryPart, just different return type
	template <typename T>
	constexpr Vector<3, T> vectorPart(const Quaternion<T> &q)
	{
		return Vector<3, T>(q[1], q[2], q[3]);
	}

	// Dot and cross product

	template <typename T>
	constexpr T dot(const Quaternion<T> &a, Quaternion<T> b)
	{
		return Quaternion<T>(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]);
	}

	template <typename T>
	constexpr Quaternion<T> cross(const Quaternion<T> &a, const Quaternion<T> &b)
	{
		return Quaternion<T>(T{}, a[2] * b[3] - a[3] * b[2], a[3] * b[1] - a[1] * b[3], a[1] * b[2] - a[2] * b[1]);
	}

	// Exp, Log, Pow

	template <typename T>
	constexpr Quaternion<T> exp(const Quaternion<T> &q)
	{
		T vn = sqrt(q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);

		return exp(q[0]) * (Quaternion<T>(cos(vn)) + imaginaryPart(q) * sin(vn) / vn);
	}

	template <typename T>
	constexpr Quaternion<T> log(const Quaternion<T> &q)
	{
		T nq = norm(q);
		Quaternion<T> v = imaginaryPart(q);
		T nv = norm(v);

		return Quaternion<T>(log(nq)) + (v / nv) * acos(realPart(q) / nq);
	}

	template <typename T>
	constexpr Quaternion<T> log2(const Quaternion<T> &q)
	{
		return log(q) / std::log(T{2});
	}

	template <typename T>
	constexpr Quaternion<T> log10(const Quaternion<T> &q)
	{
		return log(q) / std::log(T{10});
	}

	template <typename T>
	constexpr Quaternion<T> pow(const Quaternion<T> &q, T exponent)
	{
		T nq = norm(q);
		T phi = std::acos(realPart(q) / nq);
		return std::pow(nq, exponent) *
			   (Quaternion<T>(std::cos(exponent * phi)) + normalize(q) * std::sin(exponent * phi));
	}

	// ==================== General functions ====================

	template <typename T>
	constexpr bool isReal(const Quaternion<T> &q)
	{
		return (q[1] == T{}) && (q[2] == T{}) && (q[3] == T{});
	}

	template <typename T>
	constexpr bool isPureImaginary(const Quaternion<T> &q)
	{
		return q[0] == T{};
	}

	template <typename T>
	constexpr Quaternion<T> commutator(const Quaternion<T> &a, const Quaternion<T> &b)
	{
		return a * b - b * a;
	}

	// ==================== 3D graphics functions ====================

	// Rotation

	template <typename T>
	constexpr Quaternion<T> createRotationQuaternion(Vector<3, T> axis, T angle)
	{
		return Quaternion<T>(cos(angle / 2), axis * sin(angle / 2));
	}

	template <typename T>
	constexpr Quaternion<T> rotate(Quaternion<T> a, Quaternion<T> b)
	{
		return a * b * inverse(a);
	}

	template <typename T>
	constexpr Vector<3, T> rotate(Quaternion<T> a, Vector<3, T> b)
	{
		return vectorPart(a * Quaternion<T>(b) * inverse(a));
	}

	// (Spherical) Linear interpolation

	template <typename T>
	constexpr Quaternion<T> lerp(Quaternion<T> t0, Quaternion<T> t1, T t)
	{
		return t0 * (1 - t) + t1 * t;
	}

	template <typename T>
	constexpr Quaternion<T> slerp(Quaternion<T> t0, Quaternion<T> t1, T t)
	{
		return pow(t1 * inverse(t0), t) * t0;
	}

	// Typedefs

	using Quat = Quaternion<float>;
}

#endif	// QUATERNION_H
