#include "Test_Rotations.h"

#include "RayHelper.h"

#include <string>

void Excelsior::Test_Rotations::TestRollRotation()
{
	const std::string fileName = "./resultPictures/gifs/rotations/roll/pyramid/pyramid";

	const int numberOfFrames = 60;
	int currentRotationSpeed = 0;

	for (size_t i = 0; i < numberOfFrames; ++i)
	{
		RayHelper::FireRays(fileName + std::to_string(i) + ".ppm", currentRotationSpeed, numberOfFrames);
		currentRotationSpeed += 5;
	}
}
