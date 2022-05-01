#ifndef EXCELSIOR_CAMERA_H
#define EXCELSIOR_CAMERA_H

#include "./Core.h"

namespace Excelsior
{
	class Camera
	{
	public:
		Camera(const Vector3& cameraPosition)
			:m_Position(cameraPosition)
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

	private:
		Vector3 m_Position;
	};
}

#endif