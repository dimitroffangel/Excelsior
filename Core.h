#ifndef EXCELSIOR_CORE_H
#define EXCELSIOR_CORE_H

#include <math.h>

#include "./Precision.h"

namespace Excelsior
{	
	class Vector3
	{
	public:
		Real m_X;
		Real m_Y;
		Real m_Z;


		Vector3()
			:m_X(0), m_Y(0), m_Z(0)
		{

		}

		Vector3(const Real x, const Real y, const Real z)
			:m_X(x), m_Y(y), m_Z(z)
		{

		}

		Real GetMagnitude() const
		{
			return REAL_SQRT(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
		}

		Real GetSquaredMagnitude() const
		{
			return m_X * m_X + m_Y * m_Y + m_Z * m_Z;
		}

		Vector3 GetNormalize() const
		{
			const Real magnitude = GetMagnitude();

			if (magnitude == 0)
			{
				return *this;
			}

			Vector3 currentVector = *this;
			return currentVector * (1 / magnitude);
		}

		void AddScaledVector(const Vector3& vectorToBeScaled, const Real multiplier)
		{
			m_X += multiplier * vectorToBeScaled.m_X;
			m_Y += multiplier * vectorToBeScaled.m_Y;
			m_Z += multiplier * vectorToBeScaled.m_Z;
		}

		Real ScalarProduct(const Vector3& rhs) const
		{
			return m_X * rhs.m_X + m_Y * rhs.m_Y + m_Z * rhs.m_Z;
		}

		// multiply the vector with the rhs' coordinates
		void ComponentProductModify(const Vector3& rhs)
		{
			m_X *= rhs.m_X;
			m_Y *= rhs.m_Y;
			m_Z *= rhs.m_Z;
		}

		Vector3 ComponentProduct(const Vector3& rhs) const
		{
			return Vector3(m_X * rhs.m_X, m_Y * rhs.m_Y, m_Z * rhs.m_Z);
		}

		Vector3 VectorProduct(const Vector3& rhs) const
		{
			return Vector3(
				m_Y * rhs.m_Z - m_Z * rhs.m_Y,
				m_Z * rhs.m_X - m_X * rhs.m_Z,
				m_X * rhs.m_Y - m_Y * rhs.m_X
			);
		}

		Vector3& operator*=(const Real scalarMultiplier)
		{
			m_X *= scalarMultiplier;
			m_Y *= scalarMultiplier;
			m_Z *= scalarMultiplier;

			return *this;
		}

		Vector3& operator+=(const Vector3& rhs)
		{
			m_X += rhs.m_X;
			m_Y += rhs.m_Y;
			m_Z += rhs.m_Z;

			return *this;
		}

		Vector3& operator-=(const Vector3& rhs)
		{
			m_X -= rhs.m_X;
			m_Y -= rhs.m_Y;
			m_Z -= rhs.m_Z;

			return *this;
		}

		Vector3& operator%=(const Vector3& rhs)
		{
			*this = VectorProduct(rhs);

			return *this;
		}

		Vector3 operator%(const Vector3& rhs) const
		{
			return VectorProduct(rhs);
		}

		Real operator*(const Vector3& rhs) const
		{
			return m_X * rhs.m_X + m_Y * rhs.m_Y + m_Z * rhs.m_Z;
		}

		Vector3 operator+(const Vector3& rhs) const
		{
			return Vector3(m_X + rhs.m_X, m_Y + rhs.m_Y, m_Z + rhs.m_Z);
		}

		Vector3 operator-(const Vector3& rhs) const
		{
			return Vector3(m_X - rhs.m_X, m_Y - rhs.m_Y, m_Z - rhs.m_Z);
		}

		Vector3 operator*(const Real scalarMultiplier) const
		{
			return Vector3(m_X * scalarMultiplier, m_Y * scalarMultiplier, m_Z * scalarMultiplier);
		}

		Vector3 operator/(const Real scalarMultiplier) const
		{
			return Vector3(m_X / scalarMultiplier, m_Y / scalarMultiplier, m_Z / scalarMultiplier);
		}
	};

	Vector3 operator*(const Real scalarMultiplier, const Vector3& rhs)
	{
		return Vector3(rhs.m_X * scalarMultiplier, rhs.m_Y * scalarMultiplier, rhs.m_Z * scalarMultiplier);
	}

	Vector3 operator/(const Real scalarMultiplier, const Vector3& rhs)
	{
		return Vector3(rhs.m_X / scalarMultiplier, rhs.m_Y / scalarMultiplier, rhs.m_Z / scalarMultiplier);
	}
}

#endif