#pragma once

#include <spdlog/spdlog.h>

#include <string>

class Logger {
public:
	enum Level {
		Trace = SPDLOG_LEVEL_TRACE,
		Debug = SPDLOG_LEVEL_DEBUG,
		Warning = SPDLOG_LEVEL_WARN,
		Error = SPDLOG_LEVEL_ERROR
	};

	template <typename... Args>
	inline static void Print(Level level, std::string message, Args... args) {
		spdlog::log(static_cast<spdlog::level::level_enum>(level), message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline static void Print(std::string message, Args... args) {
		Print(Level::Debug, message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline static void PrintTrace(std::string message, Args... args) {
		Print(Level::Trace, message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline static void PrintDebug(std::string message, Args... args) {
		Print(Level::Debug, message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline static void PrintWarning(std::string message, Args... args) {
		Print(Level::Warning, message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline static void PrintError(std::string message, Args... args) {
		Print(Level::Error, message, std::forward<Args>(args)...);
	}

	inline static void SetLogLevel(Level level) {
		spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
	}
};