#include "Line.hpp"

#include <cmath>

Line::Line(float x, float y, float rotation, float scale) {
	float dx = std::cos(rotation) * (scale / 2);
	float dy = std::sin(rotation) * (scale / 2);
	start.position = {x - dx, -(y - dy)};
	start.color = {1.0f, 1.0f, 1.0f, 1.0f};
	end.position = {x + dx, -(y + dy)};
	end.color = {1.0f, 1.0f, 1.0f, 1.0f};
}
