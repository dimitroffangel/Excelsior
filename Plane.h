#ifndef EXCELSIOR_PLANE_H
#define EXCELSIOR_PLANE_H

#include "./Core.h"
#include "./ColourRGB.h"

#include <vector>

namespace Excelsior
{
	class Plane
	{
	public:
		Plane(const Real A, const Real B, const Real C, const Real D)
		{
			m_Points = { A,B,C, D};
		}

		Vector3 GetNormal() const
		{
			const Vector3 planeNormal = Vector3(m_Points[0], m_Points[1], m_Points[2]);

			// TODO:: normalize it ? 
			return planeNormal;
		}


	public:
		// counter-clocwise order
		std::vector<Real> m_Points;
	};
}

#endif