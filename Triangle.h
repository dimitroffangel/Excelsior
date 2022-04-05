#ifndef EXCELSIOR_TRIANGLE_H
#define EXCELSIOR_TRIANGLE_H

#include "./Core.h"
#include "./ColourRGB.h"
#include "./Plane.h"

#include <vector>

namespace Excelsior
{
	class Triangle
	{
	public:
		Triangle(const Vector3& A, const Vector3& B, const Vector3& C)
		{
			m_Points = { A,B,C };
		}


		Vector3 GetNormal() const
		{
			const Vector3 firstSide = m_Points[1] - m_Points[0];
			const Vector3 secondSide = m_Points[2] - m_Points[0];

			return firstSide.VectorProduct(secondSide).GetNormalize();
		}


	public:
		// counter-clocwise order
		std::vector<Vector3> m_Points;
	};

	bool IsVectorLookingTowardsTriangle(const Vector3& vector, const Triangle& triangle)
	{
		return vector.ScalarProduct(triangle.m_Points[0]) > 0;
	}

	Plane GetPlaneFromTriangle(const Triangle& triangle)
	{
		/*
			Plane Equation: Ax + By + Cz + D = 0 <=>
			D = -(Ax + By + Cz)
		*/ 

		const Vector3 triangleNormal = triangle.GetNormal();
		const Real planeD = -(triangleNormal.ScalarProduct(triangle.m_Points[0]));
		return Plane(triangleNormal.m_X, triangleNormal.m_Y, triangleNormal.m_Z, planeD);
	}
}

#endif