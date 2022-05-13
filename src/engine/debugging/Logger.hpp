#pragma once

#include <iostream>

namespace debugging {
	template<class printType>
	static void log(printType msg) {
		std::cout << msg << "\n";
	}
}