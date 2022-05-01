#ifndef EXCELSIOR_RAYHELPER_H
#define EXCELSIOR_RAYHELPER_H

#include <string>

namespace Excelsior
{
	class RayHelper
	{
	public:
		static void FireRays(const std::string& outputFilePath, const int rotationSpeed = 5, const int numberOfFrames = 60);
	};
}

#endif