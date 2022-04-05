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
		if (triangle.GetNormal().ScalarProduct(ray.GetDirection()) == 0)
		{
			return false;
		}

		if (!IsVectorLookingTowardsTriangle(ray.GetOrigin(), triangle))
		{
			return false;
		}

		return false;
	}

	ColourRGB GetRayColour(const Ray& ray)
	{
		const Vector3 unitDirection = ray.GetDirection().GetNormalize();
		const float t = 0.5 * (unitDirection.m_Y + unitDirection.m_X + 1.0);
		return (1.0 - t) * ColourRGB(1, 1, 1) + t * ColourRGB(0.5, 0.7, 1.0);
	}
}

#endif