#ifndef EXCELSIOR_FIGURE_H
#define EXCELSIOR_FIGURE_H

#include "./Core.h"
#include "./ColourRGB.h"
#include "./Ray.h"

namespace Excelsior
{
	class Figure
	{
	public:
		virtual bool TryGettingColour(const Ray& ray, ColourRGB& resultColour, const bool isSingleSided = false) const = 0;

	public:
		ColourRGB m_Colour;
	};
}
#endif