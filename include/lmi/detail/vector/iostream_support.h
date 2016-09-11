#ifndef LMI_VECTOR_IOSTREAM_SUPPORT_H
#define LMI_VECTOR_IOSTREAM_SUPPORT_H

// TODO split this into multiple files
#include "../matrix.h"
#include "../quaternion.h"
#include "../vector.h"
#include <ostream>

namespace lmi
{
	template <size_t DIM, typename T>
	inline std::ostream &operator<<(std::ostream &stream, const Vector<DIM, T> &v)
	{
		stream << "[";
		for(size_t i = 0; i < DIM - 1; ++i)
			stream << v[i] << "\t";
		stream << v[DIM - 1] << "]'";
		return stream;
	}

	template <size_t ROWS, size_t COLS, typename T>
	inline std::ostream &operator<<(std::ostream &stream, const Matrix<COLS, ROWS, T> &v)
	{
		stream << "[";
		for(size_t i = 0; i < COLS - 1; ++i)
		{
			for(size_t j = 0; j < ROWS - 1; ++j)
			{
				stream << v[j][i] << '\t';
			}
			stream << v[COLS - 1][i] << ";\n";
		}
		for(size_t j = 0; j < ROWS - 1; ++j)
		{
			stream << v[j][ROWS - 1] << '\t';
		}
		stream << v[ROWS - 1][COLS - 1] << "]";
		return stream;
	}

	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Quaternion<T> &rhs)
	{
		os << rhs.q0 << " + " << rhs.q1 << "i + " << rhs.q2 << "j + " << rhs.q3 << "k";
		return os;
	}
}

#endif
