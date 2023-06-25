#pragma once

#include <spdlog/spdlog.h>

#include "Core.h"

class Log
{
public:
	static void Init();

	inline static Shared<spdlog::logger>& GetLogger() { return s_Logger; }

private:
	static Shared<spdlog::logger> s_Logger;
};

#ifdef BOTS_DIST
#define BOTS_LOG_TRACE(...)
#define BOTS_LOG_DEBUG(...)
#else
#define BOTS_LOG_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
#define BOTS_LOG_DEBUG(...) ::Log::GetLogger()->debug(__VA_ARGS__)
#endif

#define BOTS_LOG_INFO(...) ::Log::GetLogger()->info(__VA_ARGS__)
#define BOTS_LOG_WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__)
#define BOTS_LOG_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
#define BOTS_LOG_FATAL(...) ::Log::GetLogger()->critical(__VA_ARGS__)
