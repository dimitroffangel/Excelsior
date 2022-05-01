#ifndef EXCELSIOR_MATRIX_H
#define EXCELSIOR_MATRIX_H

#include "./Core.h"
#include <vector>
#include <cassert>

namespace Excelsior
{
	class Matrix
	{
		static const size_t MATRIX_SIZE = 3;

	private:
		Matrix()
		{
			m_Matrix.resize(MATRIX_SIZE);
			for (size_t i = 0; i < MATRIX_SIZE; ++i)
			{
				m_Matrix[i].resize(MATRIX_SIZE);
			}
		}

	public:
		Matrix(const std::vector<std::vector<Real>> matrix)
			: m_Matrix(matrix.begin(), matrix.end())
		{
			assert(matrix.size() == MATRIX_SIZE);
			assert(matrix[0].size() == MATRIX_SIZE);
		}

		Matrix(const std::vector<Real> container)
		{
			assert(container.size() == MATRIX_SIZE * MATRIX_SIZE);
			m_Matrix.reserve(MATRIX_SIZE);

			for (size_t row = 0; row < MATRIX_SIZE; ++row)
			{
				m_Matrix.reserve(MATRIX_SIZE);
				m_Matrix.push_back({});
				for (size_t col = 0; col < MATRIX_SIZE; ++col)
				{
					m_Matrix[row].push_back(container[row * MATRIX_SIZE + col]);
				}
			}
		}

		Matrix(const Matrix& matrix)
			: m_Matrix(matrix.m_Matrix.begin(), matrix.m_Matrix.end())
		{

		}

		Matrix operator* (const Matrix& rhs)
		{
			// TODO:: Transpose the matrix first so that there are less cache misses ? 
			// Put some tests to record if this is necessary 
			
			Matrix result;
			
			for (size_t row = 0; row < MATRIX_SIZE; ++row)
			{
				for (size_t col = 0; col < MATRIX_SIZE; ++col)
				{
					for (size_t multiplyingIndex = 0; multiplyingIndex < MATRIX_SIZE; ++multiplyingIndex)
					{
						result.m_Matrix[row][col] += m_Matrix[row][multiplyingIndex] * rhs.m_Matrix[multiplyingIndex][col];
					}
				}
			}

			return result;
		}

		friend Vector3 operator*(const Vector3& lhs, const Matrix& rhs);

	private:
		std::vector<std::vector<Real>> m_Matrix;
	};
}

#endif