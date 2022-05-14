#pragma once

#include <vector>

namespace Spyder {
	class FpsDisplay {
	public:
		FpsDisplay(float printFreq, float maxAge);
		void update(float dt);
	private:

		void printFps();
		struct PastDeltaTime {
			float timeOfSample;
			float deltaTime;
		};

		float printFrequency;
		float currentTime;
		float maxSampleAge;
		float timeSinceLastPrint;
		std::vector<PastDeltaTime> pastDeltaTimes;
	};
}

