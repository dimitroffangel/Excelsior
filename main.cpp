#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "DrawColouredRectangles.h"
#include "Core.h"
#include "ColourRGB.h"
#include "ImageData.h"
#include "Ray.h"
#include "Figure.h"
#include "Triangle.h"

#include <cassert>


using namespace Convolution;
using namespace Excelsior;

const unsigned NUMBER_OF_RECTANGLES_ON_ROW = 32;
const unsigned NUMBER_OF_RECTANGLES_ON_COL = 32;
const bool IS_SIGNLE_SIDED = false;

std::vector<unsigned> GenerateRandomVector(const size_t size, const size_t fromInterval, const size_t toInterval)
{
	std::vector<unsigned> resultedVector;
	resultedVector.resize(size);

	for (size_t i = 0; i < size; i++)
		resultedVector[i] = rand() % toInterval + fromInterval;

	return resultedVector;
}

void DrawColourfulRectangles(const unsigned width, const unsigned height, const unsigned maxColourComponent, 
	const double factorConvolution, const double biasConvolution,
	const std::vector<std::vector<double>>& convolutionMatrix, const std::string& outputFilePath)
{
	assert(width % NUMBER_OF_RECTANGLES_ON_ROW == 0);
	assert(height % NUMBER_OF_RECTANGLES_ON_COL == 0);

	const unsigned rectangleXLength = width / NUMBER_OF_RECTANGLES_ON_ROW;
	const unsigned rectangleYLength = height / NUMBER_OF_RECTANGLES_ON_COL;

	std::vector<ColourRGB> colours;

	for (size_t currentColour = 0; currentColour < NUMBER_OF_RECTANGLES_ON_COL * NUMBER_OF_RECTANGLES_ON_ROW; ++currentColour)
	{
		std::vector<unsigned> currentColourValues = GenerateRandomVector(3, 0, maxColourComponent);
		colours.push_back(
			ColourRGB{ 
				static_cast<Real>(currentColourValues[0]), 
				static_cast<Real>(currentColourValues[1]), 
				static_cast<Real>(currentColourValues[2]) 
			}
		);
	}

	std::ofstream outputFile(outputFilePath);

	outputFile << "P3" << '\n';
	outputFile << width << " " << height << '\n';
	outputFile << maxColourComponent << '\n';

	std::vector<ColourRGB> image;

	for (size_t row = 0; row < height; ++row)
	{
		for (size_t col = 0; col < width; ++col)
		{
			const size_t currentRectangleRow = row / rectangleYLength;
			const size_t currentRectangleCol = col / rectangleXLength;
			const size_t rectangleIndex = NUMBER_OF_RECTANGLES_ON_ROW * currentRectangleRow + currentRectangleCol;

			image.push_back(colours[rectangleIndex]);
		}
	}

	for (size_t col = 0; col < width; ++col)
	{
		for (size_t row = 0; row < height; ++row)
		{
			double redIntensity = 0.0;
			double greenIntensity = 0.0;
			double blueIntensity = 0.0;

			for (size_t filterY = 0; filterY < convolutionMatrix.size(); ++filterY)
			{
				for (size_t filterX = 0; filterX < convolutionMatrix[0].size(); ++filterX)
				{
					const size_t imageX = (col - convolutionMatrix[0].size() / 2 + filterX + width) % width;
					const size_t imageY = (row - convolutionMatrix.size() / 2 + filterY + height) % height;

					redIntensity += image[imageY * width + imageX].m_X * convolutionMatrix[filterY][filterX];
					greenIntensity += image[imageY * width + imageX].m_Y * convolutionMatrix[filterY][filterX];
					blueIntensity += image[imageY * width + imageX].m_Z * convolutionMatrix[filterY][filterX];
				}
			}

			image[row * width + col].m_X = std::min(std::max(static_cast<int>(factorConvolution * redIntensity + biasConvolution), 0), 255);
			image[row * width + col].m_Y = std::min(std::max(static_cast<int>(factorConvolution * greenIntensity + biasConvolution), 0), 255);
			image[row * width + col].m_Z = std::min(std::max(static_cast<int>(factorConvolution * blueIntensity + biasConvolution), 0), 255);

			outputFile <<
				image[row * width + col].m_X << " " <<
				image[row * width + col].m_Y << " " <<
				image[row * width + col].m_Z << '\t';
		}
		outputFile << '\n';
	}
}

void DrawCircle(const unsigned width, const unsigned height, const unsigned maxColourComponent,
	const ColourRGB& innerCircleColour, const std::string& outputFilePath)
{
	assert(width % NUMBER_OF_RECTANGLES_ON_ROW == 0);
	assert(height % NUMBER_OF_RECTANGLES_ON_COL == 0);

	const unsigned rectangleXLength = width / NUMBER_OF_RECTANGLES_ON_ROW;
	const unsigned rectangleYLength = height / NUMBER_OF_RECTANGLES_ON_COL;

	std::vector<ColourRGB> colours = { innerCircleColour };

	for (size_t currentColour = 0; currentColour < 1; ++currentColour)
	{
		std::vector<unsigned> currentColourValues = GenerateRandomVector(3, 0, maxColourComponent);
		colours.push_back(
			ColourRGB{
				static_cast<Real>(currentColourValues[0]),
				static_cast<Real>(currentColourValues[1]),
				static_cast<Real>(currentColourValues[2])
			}
		);
	}

	std::ofstream outputFile(outputFilePath);

	outputFile << "P3" << '\n';
	outputFile << width << " " << height << '\n';
	outputFile << maxColourComponent << '\n';

	std::vector<ColourRGB> image;

	// insert magical offset that looks centre-ish
	const size_t centerX = width / 2;
	const size_t centerY = height / 2;
	const size_t radius = 2 * std::floor(std::sqrt(width + height));

	for (size_t row = 0; row < height; ++row)
	{
		for (size_t col = 0; col < width; ++col)
		{
			const size_t xDifference = col - centerX;
			const size_t yDifference = row - centerY;

			if (xDifference * xDifference + yDifference * yDifference <= radius * radius)
			{
				outputFile <<
					colours[1].m_X << " " <<
					colours[1].m_Y << " " <<
					colours[1].m_Z << '\t';
			}

			else
			{
				outputFile <<
					colours[0].m_X << " " <<
					colours[0].m_Y << " " <<
					colours[0].m_Z << '\t';
			}
		}

		outputFile << '\n';
	}
}

void PrintDifferentConvolutions()
{
	DrawColourfulRectangles(256, 256, 255, FIND_EDGE_FILTER_FACTOR, FIND_EDGE_FILTER_BIAS, FIND_HORIZONTAL_EDGE_FILTER, "./all_horizontal_edge_filter.ppm");
	DrawColourfulRectangles(256, 256, 255, FIND_EDGE_FILTER_FACTOR, FIND_EDGE_FILTER_BIAS, FIND_VERTICAL_EDGES_FILTER, "./all_vertical_edge_filter.ppm");
	DrawColourfulRectangles(256, 256, 255, FIND_EDGE_FILTER_FACTOR, FIND_EDGE_FILTER_BIAS, FIND_45_Degree_EDGES_FILTER, "./all_45_degree_edge_filter.ppm");
	DrawColourfulRectangles(256, 256, 255, FIND_EDGE_FILTER_FACTOR, FIND_EDGE_FILTER_BIAS, FIND_ALL_DIRECTION_EDGES_FILTER, "./all_direction_edge_filter.ppm");
	DrawColourfulRectangles(256, 256, 255, EMBOSS_FILTER_FACTOR, EMBOSS_FILTER_BIAS, EMBOSS_FILTER, "./emboss_convolution.ppm");

}

void PrintFigures()
{
	DrawCircle(512, 128, 255, { 171, 171, 171 }, "./circle.ppm");
}

void FireRays(const std::string& outputFilePath)
{
	std::ofstream outputFile(outputFilePath);

	outputFile << "P3" << '\n';
	outputFile << IMAGE_WIDTH << " " << IMAGE_HEIGHT << '\n';
	outputFile << 255 << '\n';

	std::vector<ColourRGB> image;

	std::vector<std::shared_ptr<Figure>> figures;
	Vector3 a(-1.75, -1.75, -3);
	Vector3 b(1.75, -1.75, -3);
	Vector3 c(0, -1.75, -6);
	Vector3 d(0, 1.75, -3);
	std::shared_ptr<Triangle> pyramidGround = std::make_shared<Triangle>(a, b, c);
	std::shared_ptr<Triangle> wall1 = std::make_shared<Triangle>(a, b, d);
	std::shared_ptr<Triangle> wall2 = std::make_shared<Triangle>(c, a, d);
	std::shared_ptr<Triangle> wall3 = std::make_shared<Triangle>(b, c, d);
	figures = { pyramidGround, wall1, wall2, wall3};

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

			const Ray ray(ORIGIN, Vector3(u, v, -1));

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

int main()
{
	std::srand(time(NULL));

	//PrintDifferentConvolutions();
	//PrintFigures();

	FireRays("./pyramid.ppm");

	return 0;
}