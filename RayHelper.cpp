#include "RayHelper.h"

#include "ImageData.h"
#include "ColourRGB.h"
#include "Triangle.h"
#include "Matrix.h"
#include "Camera.h"

#include <fstream>
#include <iostream>
#include <vector>

void Excelsior::RayHelper::FireRays(const std::string& outputFilePath, const CameraRotationType cameraRotationType, const int rotationSpeed, const int numberOfFrames)
{
	std::ofstream outputFile(outputFilePath);

	outputFile << "P3" << '\n';
	outputFile << IMAGE_WIDTH << " " << IMAGE_HEIGHT << '\n';
	outputFile << 255 << '\n';

	std::vector<ColourRGB> image;

	const Vector3 a(-1.75, -1.75, -3);
	const Vector3 b(1.75, -1.75, -3);
	const Vector3 c(0, -1.75, -6);
	const Vector3 d(0, 1.75, -3);
	const std::shared_ptr<Triangle> pyramidGround = std::make_shared<Triangle>(a, b, c);
	const std::shared_ptr<Triangle> wall1 = std::make_shared<Triangle>(a, b, d);
	const std::shared_ptr<Triangle> wall2 = std::make_shared<Triangle>(c, a, d);
	const std::shared_ptr<Triangle> wall3 = std::make_shared<Triangle>(b, c, d);
	const std::vector<std::shared_ptr<Figure>> figures = { pyramidGround, wall1, wall2, wall3 };

	const Matrix identityMatrix = Matrix(
		std::vector<Real>(
			{
				1, 0, 0,
				0, 1, 0,
				0, 0, 1,
			})
			);

	Camera camera(ORIGIN, identityMatrix);
	int currentRotation = rotationSpeed;

	switch (cameraRotationType)
	{
		case CameraRotationType::Pan:
			camera.MakePanRotation(currentRotation);
			break;
		case CameraRotationType::Tilt:
			camera.MakeTiltRotation(currentRotation);
			break;
		case CameraRotationType::Roll:
			camera.MakeRollRotation(currentRotation);
			break;
		default:
			break;
	};

	for (size_t row = 0; row < IMAGE_HEIGHT; ++row)
	{
		for (size_t col = 0; col < IMAGE_WIDTH; ++col)
		{
			Real u = col + 0.5;
			Real v = row + 0.5;

			u /= IMAGE_WIDTH;
			v /= IMAGE_HEIGHT;

			u = (2.0 * u) - 1.0;
			v = 1.0 - (2.0 * v);

			u *= static_cast<Real>(IMAGE_WIDTH / IMAGE_HEIGHT);

			const Ray ray(camera.GetPosition(), camera.RotateVectorBasedOnCameraRotation(Vector3(u, v, -1)));

			const Vector3 unitDirection = ray.GetDirection().GetNormalize();
			const float t = 0.5 * (unitDirection.m_Y + unitDirection.m_X + 1.0);
			ColourRGB pixelColour = (1.0 - t) * ColourRGB(1, 1, 1) + t * ColourRGB(0.5, 0.7, 1.0);

			for (const std::shared_ptr<Figure>& figure : figures)
			{
				ColourRGB colourIfRayHit;
				if (figure->TryGettingColour(ray, colourIfRayHit, false))
				{
					pixelColour = colourIfRayHit;
				}
			}

			outputFile <<
				static_cast<unsigned>(pixelColour.m_X * 255) << " " <<
				static_cast<unsigned>(pixelColour.m_Y * 255) << " " <<
				static_cast<unsigned>(pixelColour.m_Z * 255) << '\t';
		}

		outputFile << '\n';
	}
}