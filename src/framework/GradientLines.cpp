#include "GradientLines.hpp"

#include <cmath>

GradientLines::GradientLines(int xCount, int yCount, float scale) : horizontalCount{xCount}, verticalCount{yCount} {
	xSpacing = 2.0f / (float)(horizontalCount + 1);
	ySpacing = 2.0f / (float)(verticalCount + 1);

	float x = -1.0f + xSpacing;
	float y = -1.0f + ySpacing;

	for (int i = 1; i <= horizontalCount; ++i) {
		for (int j = 1; j <= verticalCount; ++j) {
			float rotation = std::atan2(derivative(x, y), 1.0f);
			Line line{x, y, rotation, scale};
			allLines.push_back(line.start);
			allLines.push_back(line.end);

			y += ySpacing;
		}
		y = -1.0f + ySpacing;
		x += xSpacing;
	}
}

float GradientLines::derivative(float x, float y) {
//	float scaleX = 3.0f;
//	float scaleY = 3.0f;
//	x *= scaleX;
//	y *= scaleY;
	return y + x;
}

const std::vector<Spyder::Drawable::Vertex> &GradientLines::getAllLines() const {
	return allLines;
}
