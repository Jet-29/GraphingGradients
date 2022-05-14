#pragma once

#include "engine/Engine.hpp"

class Framework {
public:
	Framework(int width, int height, const char *title);
	void runGameLoop();

private:

	Spyder::Engine engine{};
};
