#include "TimeManagment.hpp"

#include <cassert>

namespace Spyder {
	TimeManagment::TimeManagment(float maxDeltaTime) : maxDeltaTime{maxDeltaTime} {
		savedTime = std::chrono::high_resolution_clock::now();
	}

	float TimeManagment::getDeltaTime() const {
		return currentDeltaTime;
	}

	void TimeManagment::stepDeltaTime() {
		auto newTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - savedTime).count();
		savedTime = newTime;
		currentDeltaTime = deltaTime;
		if (maxDeltaTime != 0) {
			currentDeltaTime = std::min(deltaTime, maxDeltaTime);
		}
	}
} // Spyder