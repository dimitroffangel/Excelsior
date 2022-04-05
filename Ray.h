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

	bool HasHitTriangle(const Triangle& triangle, const Ray& ray)
	{
		const Vector3 triangleNormal = triangle.GetNormal();

		if (triangleNormal.ScalarProduct(ray.GetDirection()) == 0)
		{
			return false;
		}

		//if (!IsVectorLookingTowardsTriangle(ray.GetOrigin(), triangle))
		//{
		//	return false;
		//}
		
		// WTF is t in :
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

		for (int i = 0; i < 3; ++i)
		{
			const Vector3 edge = triangle.m_Points[(i + 1) % 3] - triangle.m_Points[i];

			const Vector3 CI = rayResult - triangle.m_Points[i];

			if (triangleNormal.ScalarProduct(edge.VectorProduct(CI)) <= 0)
			{
				return false;
			}
		}

		return true;
	}

	ColourRGB GetRayColour(const Ray& ray)
	{
		Triangle foo = Triangle(Vector3(-1.75, -1.75, -3), Vector3(1.75, -1.75, -3), Vector3(0, 1.75, -3));

		if (HasHitTriangle(foo, ray))
		{
			return ColourRGB(1, 0, 0);
		}

		const Vector3 unitDirection = ray.GetDirection().GetNormalize();
		const float t = 0.5 * (unitDirection.m_Y + unitDirection.m_X + 1.0);
		return (1.0 - t) * ColourRGB(1, 1, 1) + t * ColourRGB(0.5, 0.7, 1.0);
	}
}

#endif