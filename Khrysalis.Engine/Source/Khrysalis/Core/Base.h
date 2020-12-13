#pragma once

#include "Khrysalis/Core/PlatformDetection.h"

#ifdef KAL_DEBUG
	#if defined(KAL_PLATFORM_WINDOWS)
		#define KAL_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define KAL_ENABLE_ASSERTS
#else
	#define KAL_DEBUGBREAK()
#endif

#define KAL_EXPAND_MACRO(x) x
#define KAL_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define KAL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include "Khrysalis/Debug/Log.h"
#include "Khrysalis/Debug/Assert.h"