#pragma once

#ifdef BOTS_DEBUG
#define BOTS_ENABLE_ASSERTS
#define BOTS_DEBUGBREAK() __debugbreak()
#else
#define BOTS_DEBUGBREAK()
#endif

#define BOTS_STRINGIFY(m) #m

template<typename T>
using Unique = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Unique<T> MakeUnique(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Shared = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Shared<T> MakeShared(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

#include "Log.h"

#ifdef BOTS_ENABLE_ASSERTS
#define BOTS_ASSERT(check, ...) { if (!(check)) { BOTS_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); BOTS_DEBUGBREAK(); } }
#else
#define BOTS_ASSERT(check, ...)
#endif