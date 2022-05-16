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

	// axis dashing x
	for (int i = 1; i <= horizontalCount; ++i) {
		Line line{0.0f, -1 + i * ySpacing, 0, 0.02};
		allLines.push_back(line.start);
		allLines.push_back(line.end);
	}

	for (int i = 1; i <= verticalCount; ++i) {
		Line line{-1 + i * xSpacing, 0.0f, 1.571, 0.02};
		allLines.push_back(line.start);
		allLines.push_back(line.end);
	}

	{
		// axis x
		Line line{0.0f, 0.0f, 0, 1.95};
		allLines.push_back(line.start);
		allLines.push_back(line.end);
	}
	{
		// axis y
		Line line{0.0f, 0.0f, 1.571, 1.95};
		allLines.push_back(line.start);
		allLines.push_back(line.end);
	}
}

float GradientLines::derivative(float x, float y) {
	float scaleX = 5.5f;
	float scaleY = 5.5f;
	x *= scaleX;
	y *= scaleY;
//	return (float)std::abs(std::fmod(x, 4) * y * x);
	return (y - 2 * x) / (2 * y + x);
}

const std::vector<Spyder::Drawable::Vertex> &GradientLines::getAllLines() const {
	return allLines;
}
