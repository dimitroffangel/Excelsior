#ifndef EXCELSIOR_RAYHELPER_H
#define EXCELSIOR_RAYHELPER_H

#include <string>
#include "Core.h"

namespace Excelsior
{
	enum class CameraRotationType;
	enum class CameraMovementType;

	class RayHelper
	{
	public:
		static void FireRays(const std::string& outputFilePath, const CameraMovementType cameraMovementType,const CameraRotationType cameraRotationType, const Real cameraSpeed = 0, const int rotationSpeed = 0, const int numberOfFrames = 60);
	};
}

#endif