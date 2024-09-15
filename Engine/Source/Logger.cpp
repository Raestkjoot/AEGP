#include "Logger.h"

#include <spdlog/spdlog.h>

namespace Logger {
	void Print(const std::string& str) {
		spdlog::info(str);
	}
}