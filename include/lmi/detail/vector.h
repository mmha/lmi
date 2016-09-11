#ifndef LMI_VECTOR_H
#define LMI_VECTOR_H

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <tuple>

#include "defines.h"
#include "vector/vector_base.h"

namespace lmi
{
	template <size_t DIM, typename T = float>
	class Vector : public detail::VectorBase<DIM, T>
	{
		using detail::VectorBase<DIM, T>::vals;

		public:
		constexpr Vector()	// Zero initialize?
		{
		}

		constexpr explicit Vector(T y)	// implcit could be useful...
		{
			for(auto &x : vals)
			{
				x = y;
			}
		}

		constexpr operator T *()
		{
			return &vals[0];
		}

		constexpr operator const T *() const
		{
			return &vals[0];
		}

		constexpr Vector(const Vector &other) = default;
		constexpr Vector(Vector &&other) = default;
		constexpr Vector &operator=(const Vector &other) = default;
		constexpr Vector &operator=(Vector &&other) = default;

		template <typename... E, typename = typename std::enable_if_t<(DIM > 1) && ((sizeof...(E) == DIM))>>
		constexpr Vector(E &&... args)
		{
			fillArray(std::forward_as_tuple(args...));
		}

		constexpr Vector(std::initializer_list<T> other)
		{
			assert(other.size() == DIM && "initializer_list size does not match vector dimension");
			size_t i = 0;
			for(auto it = other.begin(); it != other.end(); ++it)
			{
				vals[i] = *it;
				++i;
			}
		}

		constexpr T &operator[](const size_t i)
		{
			return vals[i];
		}

		constexpr const T &operator[](const size_t i) const
		{
			return vals[i];
		}

		constexpr bool operator==(const Vector &other) const
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				if(vals[i] != other[i])
					return false;
			}
			return true;
		}

		constexpr Vector operator+(const T other) const
		{
			return Vector(*this) += other;
		}

		constexpr Vector operator-(const T other) const
		{
			return Vector(*this) -= other;
		}

		constexpr Vector operator*(const T other) const
		{
			return Vector(*this) *= other;
		}

		constexpr Vector operator/(const T other) const
		{
			return Vector(*this) /= other;
		}

		constexpr Vector operator+(const Vector &other) const
		{
			return Vector(*this) += other;
		}

		constexpr Vector operator-(const Vector &other) const
		{
			return Vector(*this) -= other;
		}

		constexpr Vector operator*(const Vector &other) const
		{
			return Vector(*this) *= other;
		}

		constexpr Vector operator/(const Vector &other) const
		{
			return Vector(*this) /= other;
		}

		constexpr Vector &operator+=(const T other)
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				vals[i] = vals[i] + other;
			}
			return *this;
		}

		constexpr Vector &operator-=(const T other)
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				vals[i] = vals[i] - other;
			}
			return *this;
		}

		constexpr Vector &operator*=(const T other)
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				vals[i] = vals[i] * other;
			}
			return *this;
		}

		constexpr Vector &operator/=(const T other)
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				vals[i] = vals[i] / other;
			}
			return *this;
		}

		constexpr Vector &operator+=(const Vector &other)
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				vals[i] = vals[i] + other[i];
			}
			return *this;
		}

		constexpr Vector &operator-=(const Vector &other)
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				vals[i] = vals[i] - other[i];
			}
			return *this;
		}

		constexpr Vector &operator*=(const Vector &other)
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				vals[i] = vals[i] * other[i];
			}
			return *this;
		}

		constexpr Vector &operator/=(const Vector &other)
		{
			for(unsigned int i = 0; i < DIM; ++i)
			{
				vals[i] = vals[i] / other[i];
			}
			return *this;
		}

		constexpr static size_t length()
		{
			return DIM;
		}

		protected:
		template <size_t i = 0, typename... E>
		constexpr typename std::enable_if_t<i == DIM, void> fillArray(std::tuple<E...>)
		{
		}

		template <size_t i = 0, typename... E>
			constexpr typename std::enable_if_t < i<DIM, void> fillArray(std::tuple<E...> tuple)
		{
			vals[i] = std::get<i>(tuple);
			fillArray<i + 1, E...>(tuple);
		}
	};

	template <typename V>
	constexpr V abs(const V &x)
	{
		V res{};
		for(size_t i = 0; i < V::length(); ++i)
		{
			res[i] = abs(x[i]);
		}
		return res;
	}

	template <size_t DIM, typename T>
	constexpr T length(const Vector<DIM, T> &x)
	{
		return sqrt(dot(x, x));
	}

	template <size_t DIM, typename T>
	constexpr T dot(const Vector<DIM, T> &x, const Vector<DIM, T> &y)
	{
		std::remove_const_t<decltype(x[0] * y[0])> res{};
		for(unsigned int i = 0; i < DIM; ++i)
		{
			res = res + x[i] * y[i];
		}
		return res;
	}

	template <typename T>
	constexpr Vector<3, T> cross(const Vector<3, T> &x, const Vector<3, T> &y)
	{
		return {x[1] * y[2] - x[2] * y[1], x[2] * y[0] - x[0] * y[2], x[0] * y[1] - x[1] * y[0]};
	}

	template <typename Func, uint32_t DIM, typename... Arg>
	constexpr auto apply(Func f, Vector<DIM, Arg> &&... args)
	{
		Vector<DIM, decltype(f(args[0]...))> res;
		for(unsigned int i = 0; i < DIM; ++i)
			res[i] = f(args[i]...);
		return res;
	}

	using vec2 = Vector<2, float>;
	using vec3 = Vector<3, float>;
	using vec4 = Vector<4, float>;
	using vec2f = Vector<2, float>;
	using vec3f = Vector<3, float>;
	using vec4f = Vector<4, float>;
	using vec2d = Vector<2, double>;
	using vec3d = Vector<3, double>;
	using vec4d = Vector<4, double>;
	using vec2i = Vector<2, int>;
	using vec3i = Vector<3, int>;
	using vec4i = Vector<4, int>;
	using vec2ui = Vector<2, unsigned>;
	using vec3ui = Vector<3, unsigned>;
	using vec4ui = Vector<4, unsigned>;
}

#endif
