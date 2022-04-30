#include "Core.h"

using namespace Excelsior;

Vector3 Excelsior::operator*(const Real scalarMultiplier, const Vector3& rhs)
{
	return Vector3(rhs.m_X * scalarMultiplier, rhs.m_Y * scalarMultiplier, rhs.m_Z * scalarMultiplier);
}

Vector3 operator/(const Real scalarMultiplier, const Vector3& rhs)
{
	return Vector3(rhs.m_X / scalarMultiplier, rhs.m_Y / scalarMultiplier, rhs.m_Z / scalarMultiplier);
}