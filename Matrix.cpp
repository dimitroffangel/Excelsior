#include "Matrix.h"

#include "./Core.h"

#include <cassert>

using namespace Excelsior;

Vector3 Excelsior::operator*(const Vector3& lhs, const Matrix& rhs)
{
	// TODO:: Transpose the matrix first so that there are less cache misses ? 
	// Put some tests to record if this is necessary 

	const int vectorSize = 3;
	assert(vectorSize == rhs.MATRIX_SIZE);

	const std::vector<Real> vectorCoordinates = { lhs.m_X, lhs.m_Y, lhs.m_Z };
	std::vector<Real> resultedVectorCoordinates = { 0, 0, 0 };
	for (size_t col = 0; col < vectorSize; ++col)
	{
		for (size_t i = 0; i < vectorSize; ++i)
		{
			resultedVectorCoordinates[col] += vectorCoordinates[i] * rhs.m_Matrix[col][i];
		}
	}

	const Vector3 result = Vector3(resultedVectorCoordinates[0], resultedVectorCoordinates[1], resultedVectorCoordinates[2]);
	return result;
}
