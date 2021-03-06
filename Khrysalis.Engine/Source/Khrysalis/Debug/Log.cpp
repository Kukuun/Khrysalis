#include "KalPch.h"
#include "Khrysalis/Debug/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Khrysalis {
	std::shared_ptr<spdlog::logger> Log::_engineLogger;
	std::shared_ptr<spdlog::logger> Log::_clientLogger;

	void Log::Initialize() {
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Khrysalis.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		_engineLogger = std::make_shared<spdlog::logger>("ENGINE", begin(logSinks), end(logSinks));
		spdlog::register_logger(_engineLogger);
		_engineLogger->set_level(spdlog::level::trace);
		_engineLogger->flush_on(spdlog::level::trace);

		_clientLogger = std::make_shared<spdlog::logger>("CLIENT", begin(logSinks), end(logSinks));
		spdlog::register_logger(_clientLogger);
		_clientLogger->set_level(spdlog::level::trace);
		_clientLogger->flush_on(spdlog::level::trace);
	}
}