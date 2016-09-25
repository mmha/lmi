#pragma once

namespace lmi
{
	template<typename T, typename Function, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
	auto newtonIntegrate(const T &a, const T &b, Function f)
	{
		return (b - a) * (f(a) + f(b)) / T{2};
	}

	// D'oh!
	template<typename T, typename Function, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
	auto simpsonIntegrate(const T &a, const T &b, Function f)
	{
		return (b - a) * (f(a) + T{4} * f((a + b) / T{2}) + f(b)) / T{6};
	}
}