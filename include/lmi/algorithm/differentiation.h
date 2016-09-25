#pragma once

namespace lmi
{
	template<typename T, typename Function, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
	auto forwardDifferentiate(const T &x, const T &h, Function f)
	{
		return (f(x + h) - f(x)) / h;
	}

	template<typename T, typename Function, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
	auto backwardDifferentiate(const T &x, const T &h, Function f)
	{
		return (f(x) - f(x - h)) / h;
	}

	template<typename T, typename Function, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
	auto centralDifferentiate(const T &x, const T &h, Function f)
	{
		return (f(x + h / T{2}) - f(x - h / T{2})) / h;
	}
}