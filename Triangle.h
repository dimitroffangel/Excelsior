#ifndef EXCELSIOR_TRIANGLE_H
#define EXCELSIOR_TRIANGLE_H

#include "./Figure.h"
#include "./Plane.h"

#include <vector>

namespace Excelsior
{
	class Triangle : public Figure
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

			return firstSide.VectorProduct(secondSide);
		}

		virtual bool TryGettingColour(const Ray& ray, ColourRGB& resultColour, const bool isSingleSided = false) const override
		{
			Real uTriangleShading = 0.0;
			Real vTriangleShading = 0.0;
			Real tTriangleShading = 0.0;

			if (HasHitTriangle(*this, ray, uTriangleShading, vTriangleShading, isSingleSided))
			{		
				resultColour = uTriangleShading * m_BarrycentricColours[0] + 
					vTriangleShading * m_BarrycentricColours[1] + 
					(1 - uTriangleShading - vTriangleShading) * m_BarrycentricColours[2];
				return true;
			}

			return false;
		}

		bool HasHitTriangle(const Triangle& triangle, const Ray& ray, Real& uShading, Real& vShading, const bool isSingleSided) const
		{
			const Vector3 triangleNormal = triangle.GetNormal();

			if (isSingleSided && triangleNormal.ScalarProduct(ray.GetDirection()))
			{
				return false;
			}

			if (triangleNormal.ScalarProduct(ray.GetDirection()) == 0)
			{
				return false;
			}

			const Real triangleNormalSquaredMagnitude = triangleNormal.GetSquaredMagnitude();

			//if (triangleNormal.ScalarProduct(triangle.m_Points[0]) >= 0)
			//{
			//	return false;
			//}

			// WTF is t in the ray that is intersecting the triangle's plane :
			// |RayPoint = RayOrigin + t * RayDirection 
			// |Ax + By + Cz + D = 0 <=>
			// A*(RayPoint.X) + B*(RayPoint.Y) + C*(RayPoint.Z) + D = 0 <=>
			// A*(RayOrigin.X + t * RayDirection.X) + B*(RayOrigin.Y + t * RayDirection.Y) + ... + D = 0 <=>
			// ScalarProduct(triangleNormal, RayOrigin) + t * ScalarProduct(triangleNormal, RayDirection) + D = 0 <=>
			// t = -[ScalarProduct(triangleNormal, RayOrigin) + D] / (ScalarProduct(triangleNormal, RayDirection)

			const Real planeD = -(triangleNormal.ScalarProduct(triangle.m_Points[0]));

			const Real t = -(triangleNormal.ScalarProduct(ray.GetOrigin()) + planeD) / (triangleNormal.ScalarProduct(ray.GetDirection()));

			if (t < 0)
			{
				return false;
			}

			const Vector3 rayResult = ray.ResultAt(t);
			std::vector<Real> scalarTripleProductsResults;
			scalarTripleProductsResults.reserve(3);

			for (int i = 0; i < 3; ++i)
			{
				const Vector3 edge = triangle.m_Points[(i + 1) % 3] - triangle.m_Points[i];

				const Vector3 CI = rayResult - triangle.m_Points[i];

				scalarTripleProductsResults.push_back(triangleNormal.ScalarProduct(edge.VectorProduct(CI)));

				if (scalarTripleProductsResults[i] < 0)
				{
					return false;
				}
			}

			uShading = scalarTripleProductsResults[1] / triangleNormalSquaredMagnitude;
			vShading = scalarTripleProductsResults[2] / triangleNormalSquaredMagnitude;

			return true;
		}

		bool HasHitTriangle_Moller_Trumbore(const Triangle& triangle, const Ray& ray, Real& uShading, Real& vShading, Real& t, const bool isSingleSided)
		{
			const Vector3 AB = triangle.m_Points[1] - triangle.m_Points[0];
			const Vector3 AC = triangle.m_Points[2] - triangle.m_Points[0];

			const Vector3 crossProductRayDirectionAC = ray.GetDirection().VectorProduct(AC);
			const Real determinant = crossProductRayDirectionAC.ScalarProduct(AB);

			// the ray is hitting from behind the triangle
			if (determinant < EPSILON && determinant > -EPSILON)
			{
				return false;
			}

			const Real inversedDeterminant = 1 / determinant;
			const Vector3 AOrigin = ray.GetOrigin() - triangle.m_Points[0];
			uShading = AOrigin.ScalarProduct(crossProductRayDirectionAC) * inversedDeterminant;

			if (uShading < 0 || uShading > 1)
			{
				return false;
			}

			const Vector3 crossProductAOrigin= AOrigin.VectorProduct(AB);
			vShading = ray.GetDirection().ScalarProduct(crossProductAOrigin) * inversedDeterminant;
			if (vShading < 0 || uShading + vShading > 1)
			{
				return false;
			}

			t = crossProductAOrigin.ScalarProduct(AB) * inversedDeterminant;

			return true;
		}

		public:
			// counter-clocwise order
			std::vector<Vector3> m_Points;
			std::vector<Vector3> m_BarrycentricColours = { {0.6, 0.4, 0.1}, {0.1, 0.5, 0.3}, {0.1, 0.3, 0.7} };
		};

	static bool IsVectorLookingTowardsTriangle(const Vector3& vector, const Triangle& triangle)
	{
		return vector.ScalarProduct(triangle.m_Points[0]) < 0;
	}

	static Plane GetPlaneFromTriangle(const Triangle& triangle)
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