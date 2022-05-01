#include "Test_Rotations.h"

#include "RayHelper.h"
#include "Camera.h"

#include <string>

void Excelsior::Test_Rotations::TestRollRotation()
{
	const std::string fileName = "./resultPictures/gifs/rotations/roll/pyramid/pyramid";

	const int numberOfFrames = 60;
	int currentRotationSpeed = 0;

	for (size_t i = 0; i < numberOfFrames; ++i)
	{
		RayHelper::FireRays(fileName + std::to_string(i) + ".ppm", CameraRotationType::Roll, currentRotationSpeed, numberOfFrames);
		currentRotationSpeed += 5;
	}
}

void Excelsior::Test_Rotations::TestPanRotation()
{
	const std::string fileName = "./resultPictures/gifs/rotations/pan/pyramid/pyramid";

	const int numberOfFrames = 60;
	int currentRotationSpeed = -30;

	for (size_t i = 0; i < numberOfFrames; ++i)
	{
		RayHelper::FireRays(fileName + std::to_string(i) + ".ppm", CameraRotationType::Pan, currentRotationSpeed, numberOfFrames);
		currentRotationSpeed += 5;
	}
}

void Excelsior::Test_Rotations::TestTiltRotation()
{
	const std::string fileName = "./resultPictures/gifs/rotations/tilt/pyramid/pyramid";

	const int numberOfFrames = 60;
	int currentRotationSpeed = -30;

	for (size_t i = 0; i < numberOfFrames; ++i)
	{
		RayHelper::FireRays(fileName + std::to_string(i) + ".ppm", CameraRotationType::Tilt, currentRotationSpeed, numberOfFrames);
		currentRotationSpeed += 5;
	}
}