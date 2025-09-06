#include "logger.h"

namespace ViSolEngine {
	Shared<spdlog::logger> Logger::sCoreLogger = nullptr;
	Shared<spdlog::logger> Logger::sClientLogger = nullptr;

// Pattern: [22:40:00] [ViSolEngine::Logger:Init:11] [ViSolEngine] [Thread:1000] Logger message
	void Logger::init() {
		spdlog::set_pattern("%^[%H:%M:%S] [%!:%#] [%n] [Thread:%t] %v%$");

		sCoreLogger = spdlog::stdout_color_mt("ViSolEngine");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt("Client");
		sClientLogger->set_level(spdlog::level::trace);
	}
}