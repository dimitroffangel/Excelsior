#ifndef EXCELSIOR_RAY_H
#define EXCELSIOR_RAY_H

#include "./Core.h"
#include "./ColourRGB.h"

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
}

#endif