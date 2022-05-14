#include "Framework.hpp"

Framework::Framework(const int width, const int height, const char *title) : gradientLines{50, 50, 0.05f} {
	Spyder::EngineInitParams initParams{width, height, title, true};
	engine.init(initParams);
	engine.getWindow().setBackground({0.01f, 0.01f, 0.01f, 1.0f});

	engine.lineBatch.addToBatch(gradientLines.getAllLines());

}

void Framework::runGameLoop() {
	while (!engine.getWindow().shouldClose()) {
		engine.beginFrame();
		engine.endFrame();
	}
	engine.close();
}