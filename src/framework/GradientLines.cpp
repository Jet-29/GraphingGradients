#include "GradientLines.hpp"

#include <cmath>

GradientLines::GradientLines(float width, float height, int xCount, int yCount) : horizontalCount{xCount}, verticalCount{yCount} {
	xSpacing = width / (horizontalCount + 1);
	ySpacing = height / (verticalCount + 1);

	for (int i = 1; i <= horizontalCount; ++i) {
		for (int j = 1; j <= verticalCount; ++j) {
			float rotation = std::atan2(derivitive())
			Line line{j * xSpacing, i * ySpacing, 0, 1}
		}
	}
	
}

float GradientLines::derivative(float x, float y) {
	return x + y;
}
