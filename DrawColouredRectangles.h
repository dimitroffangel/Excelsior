#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "ColourRGB.h"

namespace Convolution
{
	static const std::vector<std::vector<double>> FIND_HORIZONTAL_EDGE_FILTER =
	{
	  {-1, -1, -1},
	  {-1,  9, -1},
	  {-1, -1, -1}
	};

	static const double FIND_EDGE_FILTER_FACTOR = 1.0;
	static const double FIND_EDGE_FILTER_BIAS = 0.0;

	static const std::vector<std::vector<double>> FIND_VERTICAL_EDGES_FILTER =
	{
	   {0,  0, -1,  0,  0},
	   {0,  0, -1,  0,  0},
	   {0,  0,  4,  0,  0},
	   {0,  0, -1,  0,  0},
	   {0,  0, -1,  0,  0},
	};

	static const std::vector<std::vector<double>> FIND_45_Degree_EDGES_FILTER =
	{
		{-1,  0,  0,  0,  0},
		{ 0, -2,  0,  0,  0},
		{ 0,  0,  6,  0,  0},
		{ 0,  0,  0, -2,  0},
		{ 0,  0,  0,  0, -1},
	};

	static const std::vector<std::vector<double>> FIND_ALL_DIRECTION_EDGES_FILTER =
	{
		{-1, -1, -1},
		{-1,  8, -1},
		{-1, -1, -1}
	};

	static const std::vector<std::vector<double>> EMBOSS_FILTER =
	{
		{-1, -1, -1, -1,  0},
		{-1, -1, -1,  0,  1},
		{-1, -1,  0,  1,  1},
		{-1,  0,  1,  1,  1},
		{ 0,  1,  1,  1,  1}
	};

	static const double EMBOSS_FILTER_FACTOR = 1.0;
	static const double EMBOSS_FILTER_BIAS = 128;
};