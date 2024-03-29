#pragma once

#include"Core.h"
#include"spdlog/spdlog.h"
#include"spdlog/fmt/ostr.h"

namespace Reptile {

class REPTILE_API Log
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

// core log macros
#define RP_CORE_ERROR(...)      ::Reptile::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RP_CORE_WARN(...)       ::Reptile::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RP_CORE_INFO(...)       ::Reptile::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RP_CORE_TRACE(...)      ::Reptile::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RP_CORE_CRITICAL(...)   ::Reptile::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macros
#define RP_ERROR(...)      ::Reptile::Log::GetClientLogger()->error(__VA_ARGS__)
#define RP_WARN(...)       ::Reptile::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RP_INFO(...)       ::Reptile::Log::GetClientLogger()->info(__VA_ARGS__)
#define RP_TRACE(...)      ::Reptile::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RP_CRITICAL(...)   ::Reptile::Log::GetClientLogger()->critical(__VA_ARGS__)
