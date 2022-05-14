#include "Framework.hpp"

Framework::Framework(const int width, const int height, const char *title) {
	Spyder::EngineInitParams initParams{width, height, title};
	engine.init(initParams);
	engine.getWindow().setBackground({0.01f, 0.01f, 0.01f, 1.0f});



}

void Framework::runGameLoop() {
	while (!engine.getWindow().shouldClose()) {
		engine.beginFrame();
		engine.endFrame();
	}
	engine.close();
}