#pragma once

#include <chrono>

namespace Spyder {

	class TimeManagment {
	public:
		explicit TimeManagment(float maxDeltaTime = 0);
		[[nodiscard]] float getDeltaTime() const;
		void stepDeltaTime();
	private:
		std::chrono::time_point<std::chrono::steady_clock> savedTime;
		float maxDeltaTime = 0;
		float currentDeltaTime = 0;
	};

} // Spyder