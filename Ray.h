#ifndef EXCELSIOR_RAY_H
#define EXCELSIOR_RAY_H

#include "./Core.h"
#include "./ColourRGB.h"

#include "Triangle.h"

namespace Excelsior
{
	class Ray
	{
		public:
			Ray() {}

			Ray(const Vector3& origin, const Vector3& direction)
				:m_Origin(origin), m_Direction(direction)
			{

			}

			Vector3 GetOrigin() const
			{
				return m_Origin;
			}

			Vector3 GetDirection() const
			{
				return m_Direction;
			}

			Vector3 ResultAt(const Real t) const
			{
				return m_Origin + t * m_Direction;
			}

		public:
			Vector3 m_Origin;
			Vector3 m_Direction;
	};

	bool HasHitTriangle_Moller_Trumbore(const Triangle& triangle, const Ray& ray, Real& uShading, Real& vShading, Real& t, const bool isSingleSided)
	{
		const Vector3 AB = triangle.m_Points[1] - triangle.m_Points[0];
		const Vector3 AC = triangle.m_Points[2] - triangle.m_Points[0];

		const Vector3 crossProductRayDirectionAC = ray.GetDirection().VectorProduct(AC);
		const Real determinant = crossProductRayDirectionAC.ScalarProduct(AB);

		// the ray is hitting from behind the triangle
		if (determinant < 0.0001 && determinant > -0.0001)
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

	bool HasHitTriangle(const Triangle& triangle, const Ray& ray, Real& uShading, Real& vShading, const bool isSingleSided)
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

	ColourRGB GetRayColour(const Ray& ray, const bool isSingleSided)
	{
		Triangle foo = Triangle(Vector3(-1.75, -1.75, -3), Vector3(1.75, -1.75, -3), Vector3(0, 1.75, -3));
		Triangle foo2 = Triangle(Vector3(0, 0, -1), Vector3(1, 0, -3), Vector3(0, 1, -3));

		Real uTriangleShading = 0.0;
		Real vTriangleShading = 0.0;
		Real tTriangleShading = 0.0;
		Vector3 cols[3] = { {0.6, 0.4, 0.1}, {0.1, 0.5, 0.3}, {0.1, 0.3, 0.7} };

		if (HasHitTriangle_Moller_Trumbore(foo, ray, uTriangleShading, vTriangleShading, tTriangleShading, isSingleSided))
		{
			return uTriangleShading * cols[0] + vTriangleShading * cols[1] + (1 - uTriangleShading - vTriangleShading) * cols[2];
			//return ColourRGB(uTriangleShading, vTriangleShading, 1- uTriangleShading - vTriangleShading);
		}

		//if (HasHitTriangle(foo, ray, uTriangleShading, vTriangleShading, isSingleSided))
		//{
		//	return ColourRGB(uTriangleShading, vTriangleShading, 1- uTriangleShading - vTriangleShading);
		//}

		//if (HasHitTriangle(foo2, ray, uTriangleShading, vTriangleShading, isSingleSided))
		//{
		//	return ColourRGB(1, 0, 0);
		//}

		const Vector3 unitDirection = ray.GetDirection().GetNormalize();
		const float t = 0.5 * (unitDirection.m_Y + unitDirection.m_X + 1.0);
		return (1.0 - t) * ColourRGB(1, 1, 1) + t * ColourRGB(0.5, 0.7, 1.0);
	}
}

#endif