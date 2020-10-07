#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Quantum {

	class QUANTUM_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log marcos :D
#define QU_CORE_TRACE(...)    ::Quantum::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QU_CORE_INFO(...)     ::Quantum::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QU_CORE_WARN(...)     ::Quantum::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QU_CORE_ERROR(...)    ::Quantum::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QU_CORE_CRITICAL(...) ::Quantum::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log marcos :D
#define QU_TRACE(...)    ::Quantum::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QU_INFO(...)     ::Quantum::Log::GetClientLogger()->info(__VA_ARGS__)
#define QU_WARN(...)     ::Quantum::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QU_ERROR(...)    ::Quantum::Log::GetClientLogger()->error(__VA_ARGS__)
#define QU_CRITICAL(...) ::Quantum::Log::GetClientLogger()->critical(__VA_ARGS__)