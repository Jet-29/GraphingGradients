#pragma once
#include "engine/graphics/Drawable.hpp"

class Line {
public:
	Line(float x, float y, float rotation, float scale);
	Spyder::Drawable::Vertex start{};
	Spyder::Drawable::Vertex end{};
};
