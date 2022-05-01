#include "Test_CameraMovement.h"

#include "RayHelper.h"
#include "Camera.h"

#include <string>

void Excelsior::Test_CameraMovement::TestDollyRotation()
{
	const std::string fileName = "./resultPictures/gifs/movements/dolly/pyramid/pyramid";

	const int numberOfFrames = 15;
	Real currentCameraVelocity = 0;

	for (size_t i = 0; i < numberOfFrames; ++i)
	{
		RayHelper::FireRays(fileName + std::to_string(i) + ".ppm", CameraMovementType::Dolly, CameraRotationType::None, currentCameraVelocity, 0, numberOfFrames);
		currentCameraVelocity += 0.2;
	}
}

void Excelsior::Test_CameraMovement::TestTruckRotation()
{
	const std::string fileName = "./resultPictures/gifs/movements/truck/pyramid/pyramid";

	const int numberOfFrames = 10;
	Real currentCameraVelocity = 0;

	for (size_t i = 0; i < numberOfFrames; ++i)
	{
		RayHelper::FireRays(fileName + std::to_string(i) + ".ppm", CameraMovementType::Truck, CameraRotationType::None, currentCameraVelocity, 0, numberOfFrames);
		currentCameraVelocity += 0.2;
	}
}

void Excelsior::Test_CameraMovement::TestPedestalRotation()
{
	const std::string fileName = "./resultPictures/gifs/movements/pedestal/pyramid/pyramid";

	const int numberOfFrames = 10;
	Real currentCameraVelocity = 0;

	for (size_t i = 0; i < numberOfFrames; ++i)
	{
		RayHelper::FireRays(fileName + std::to_string(i) + ".ppm", CameraMovementType::Pedestal, CameraRotationType::None, currentCameraVelocity, 0, numberOfFrames);
		currentCameraVelocity += 0.2;
	}
}
