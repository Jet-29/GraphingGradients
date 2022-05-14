#pragma once
#include "Line.hpp"

class GradientLines {
public:
	GradientLines(int xCount, int yCount, float scale);

	static float derivative(float x, float y);

	[[nodiscard]] const std::vector<Spyder::Drawable::Vertex> &getAllLines() const;

private:
	std::vector<Spyder::Drawable::Vertex> allLines{};

	int horizontalCount;
	int verticalCount;
	float xSpacing;
	float ySpacing;
};
