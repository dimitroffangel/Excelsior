#ifndef EXCELSIOR_CAMERA_H
#define EXCELSIOR_CAMERA_H

#include "./Core.h"
#include "Precision.h"
#include "Matrix.h"

namespace Excelsior
{
	class Camera
	{
	public:
		Camera(const Vector3& cameraPosition, const Matrix& matrix)
			:m_Position(cameraPosition),
			 m_RotationMatrix(matrix)
		{

		}

		void SetPosition(const Vector3& cameraPosition)
		{
			m_Position = cameraPosition;
		}

		Vector3 GetPosition() const
		{
			return m_Position;
		}

		Vector3 RotateVectorBasedOnCameraRotation(const Vector3& vectorToRotate) const
		{
			return vectorToRotate * m_RotationMatrix;
		}

		void MakePanRotation(const float degreeOfRotation)
		{
			const float radionsOfRotations = degreeOfRotation * (PI / 180.0f);
			const Matrix rotationAroundY = Matrix(
				std::vector<Real>(
					{
						cosf(radionsOfRotations), 0, -sinf(radionsOfRotations),
						0, 1, 0,
						sinf(radionsOfRotations), 0, cosf(radionsOfRotations)
					})
			);
			m_RotationMatrix = m_RotationMatrix * rotationAroundY;
		}

		void MakeTiltRotation(const float degreeOfRotation)
		{
			const float radionsOfRotations = degreeOfRotation * (PI / 180.0f);
			const Matrix rotationAroundX = Matrix(
				std::vector<Real>(
					{
						1, 0, 0,
						0, cosf(radionsOfRotations), sinf(radionsOfRotations),
						0, -sin(radionsOfRotations), cosf(radionsOfRotations)
					})
			);
			m_RotationMatrix = m_RotationMatrix * rotationAroundX;
		}

		void MakeRollRotation(const float degreeOfRotation)
		{
			const float radionsOfRotations = degreeOfRotation * (PI / 180.0f);
			const Matrix rotationAroundZ = Matrix(
				std::vector<Real>(
					{
						cosf(radionsOfRotations), sinf(radionsOfRotations), 0 ,
						-sinf(radionsOfRotations), cosf(radionsOfRotations), 0,
						0, 0, 1
					})
			);
			m_RotationMatrix = m_RotationMatrix * rotationAroundZ;
		}

	private:
		Vector3 m_Position;
		Matrix m_RotationMatrix;
	};
}

#endif