#ifndef LMI_DECOMPOSITION_H
#define LMI_DECOMPOSITION_H

#include "../detail/matrix.h"
#include <utility>

namespace lmi
{
	namespace algorithm
	{
		template <uint32_t DIM, typename T>
		constexpr Matrix<DIM, DIM, T> LUDecompose(const Matrix<DIM, DIM, T> &m)
		{
			Matrix<DIM, DIM, T> LU;
			for(int j = 0; j < DIM; ++j)
			{
				for(int i = 0; i <= j; ++i)
				{
					T sum{};
					for(int k = 0; k < i; ++k)
					{
						sum += LU[i][k] * LU[k][j];
					}
					LU[i][j] = m[i][j] - sum;
				}
				for(int i = j + 1; i < DIM; ++i)
				{
					T sum{};
					for(int k = 0; k < j; ++k)
					{
						sum += LU[i][k] * LU[k][j];
					}
					LU[i][j] = (m[i][j] - sum) / LU[j][j];
				}
			}
			return LU;
		}
	}
}

#endif
