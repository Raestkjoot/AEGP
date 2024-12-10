#pragma once

#include <spdlog/spdlog.h>

#include <string>

namespace Logger {
	enum class Level : int {
		Trace = SPDLOG_LEVEL_TRACE,
		Debug = SPDLOG_LEVEL_DEBUG,
		Info = SPDLOG_LEVEL_INFO,
		Warning = SPDLOG_LEVEL_WARN,
		Error = SPDLOG_LEVEL_ERROR
	};

	template <typename... Args>
	inline void Print(Level level, std::string message, Args... args) {
		spdlog::log(static_cast<spdlog::level::level_enum>(level), message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void Print(std::string message, Args... args) {
		Print(Level::Info, message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void PrintTrace(std::string message, Args... args) {
		Print(Level::Trace, message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void PrintDebug(std::string message, Args... args) {
		Print(Level::Debug, message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void PrintWarning(std::string message, Args... args) {
		Print(Level::Warning, message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void PrintError(std::string message, Args... args) {
		Print(Level::Error, message, std::forward<Args>(args)...);
	}

	inline void SetLevel(Level level) {
		// Default log level is Info
		// Anything below the log level will be ignored, so you can control how much detail you want to log
		spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
	}
}