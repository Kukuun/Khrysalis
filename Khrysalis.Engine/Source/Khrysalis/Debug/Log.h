#pragma once

#include "Khrysalis/Core/Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Khrysalis {
	class Log {
	public:
		static void Initialize();

		static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return _engineLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return _clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> _engineLogger;
		static std::shared_ptr<spdlog::logger> _clientLogger;
	};
}

// Engine log macros
#define KAL_ENGINE_TRACE(...)    ::Khrysalis::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define KAL_ENGINE_INFO(...)     ::Khrysalis::Log::GetEngineLogger()->info(__VA_ARGS__)
#define KAL_ENGINE_WARN(...)     ::Khrysalis::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define KAL_ENGINE_ERROR(...)    ::Khrysalis::Log::GetEngineLogger()->error(__VA_ARGS__)
#define KAL_ENGINE_CRITICAL(...) ::Khrysalis::Log::GetEngineLogger()->critical(__VA_ARGS__)

// Client log macros
#define KAL_TRACE(...)			 ::Khrysalis::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KAL_INFO(...)			 ::Khrysalis::Log::GetClientLogger()->info(__VA_ARGS__)
#define KAL_WARN(...)			 ::Khrysalis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KAL_ERROR(...)			 ::Khrysalis::Log::GetClientLogger()->error(__VA_ARGS__)
#define KAL_CRITICAL(...)		 ::Khrysalis::Log::GetClientLogger()->critical(__VA_ARGS__)