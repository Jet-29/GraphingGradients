#pragma once
#include "Line.hpp"

class GradientLines {
public:
	GradientLines(float width, float height, int xCount, int yCount);

	static float derivative(float x, float y);

private:
	std::vector<Spyder::Drawable::Vertex> allLines{};

	int horizontalCount;
	int verticalCount;
	float xSpacing;
	float ySpacing;
};
