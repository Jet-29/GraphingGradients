#pragma once

#include <functional>

namespace Spyder {
	class Utilities {
	public:
		template<typename T, typename... Rest>
		static void hashCombine(std::size_t &seed, const T &v, const Rest &... rest);
	};
} // Spyder