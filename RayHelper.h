#ifndef EXCELSIOR_RAYHELPER_H
#define EXCELSIOR_RAYHELPER_H

#include <string>

namespace Excelsior
{
	enum class CameraRotationType;

	class RayHelper
	{
	public:
		static void FireRays(const std::string& outputFilePath, const CameraRotationType cameraRotationType, const int rotationSpeed = 5, const int numberOfFrames = 60);
	};
}

#endif