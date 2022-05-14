#pragma once
#include "engine/graphics/Drawable.hpp"

class Line {
public:
	Line(float x, float y, float rotation, float scale);
private:
	std::vector<Spyer::Drawable::Vertex> sides{};
};
