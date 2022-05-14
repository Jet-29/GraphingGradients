#include "Framework.hpp"

Framework::Framework(const int width, const int height, const char *title) : gradientLines{20, 20, 0.1f} {
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