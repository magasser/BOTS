#include "botspch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>

Shared<spdlog::logger> Log::s_Logger;

void Log::Init()
{
	spdlog::set_pattern("[%T] %^[%l]%$: %v");

	auto duplicateFilter = MakeShared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(10));

	duplicateFilter->add_sink(MakeShared<spdlog::sinks::stdout_color_sink_mt>());
	duplicateFilter->add_sink(MakeShared<spdlog::sinks::basic_file_sink_mt>("logs/BOTS.log", true));

	s_Logger = MakeShared<spdlog::logger>("BOTS", duplicateFilter);
	s_Logger->set_level(spdlog::level::trace);

#if defined(BOTS_DEBUG)
	s_Logger->flush_on(spdlog::level::trace);
#elif defined(BOTS_RELEASE)
	s_Logger->flush_on(spdlog::level::warn);
#endif
}
