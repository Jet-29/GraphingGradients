#pragma once

#include "engine/Engine.hpp"
#include "framework/GradientLines.hpp"


class Framework {
public:
	Framework(int width, int height, const char *title);
	void runGameLoop();

private:
	Spyder::Engine engine{};
	GradientLines gradientLines;
};
