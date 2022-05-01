#ifndef EXCELSIOR_IMAGEDATA_H
#define EXCELSIOR_IMAGEDATA_H

#include "./Core.h"

namespace Excelsior
{
	const Real ASPECT_RATIO = 4 / 3;
	const unsigned IMAGE_WIDTH = 400;
	const unsigned IMAGE_HEIGHT = static_cast<unsigned>(IMAGE_WIDTH / ASPECT_RATIO);
	//const unsigned IMAGE_HEIGHT = 400;

	const Real VIEWPORT_HEIGHT = 2.0;
	const Real VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
	//const Real VIEWPORT_WIDTH = 1.0;

	const Real FOCAL_LENGTH = 1.0;
	
	const Vector3 ORIGIN = Vector3(0, 1, 0);
	const Vector3 HORIZONTAL = Vector3(VIEWPORT_WIDTH, 0, 0);
	const Vector3 VERTICAL = Vector3(0, VIEWPORT_HEIGHT, 0);
	const Vector3 LOWER_LEFT_CORNER = ORIGIN - HORIZONTAL / 2 + VERTICAL / 2 - Vector3(0, 0, FOCAL_LENGTH);
}

#endif