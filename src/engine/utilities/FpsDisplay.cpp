#include "FpsDisplay.hpp"

#include "engine/debugging/Logger.hpp"

namespace Spyder {
	FpsDisplay::FpsDisplay(float printFreq, float maxAge) {
		printFrequency = printFreq;
		maxSampleAge = maxAge;
		currentTime = 0;
		timeSinceLastPrint = 0;
	}

	void FpsDisplay::update(float dt) {
		PastDeltaTime pastDT{};
		pastDT.timeOfSample = currentTime;
		pastDT.deltaTime = dt;
		pastDeltaTimes.push_back(pastDT);
		currentTime += dt;

		while (currentTime - pastDeltaTimes[0].timeOfSample > maxSampleAge) {
			pastDeltaTimes.erase(pastDeltaTimes.begin());
		}

		timeSinceLastPrint += dt;
		if (timeSinceLastPrint > printFrequency) {
			printFps();
		}
	}

	void FpsDisplay::printFps() {
		timeSinceLastPrint = 0;
		float totalFrameTime = 0;
		for (PastDeltaTime &pastDeltaTime : pastDeltaTimes) {
			totalFrameTime += pastDeltaTime.deltaTime;
		}
		float averageFrameTime = totalFrameTime / pastDeltaTimes.size();
		float fps = 1 / averageFrameTime;
		debugging::log(fps);
	}
}