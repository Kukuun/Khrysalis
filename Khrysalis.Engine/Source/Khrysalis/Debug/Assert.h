#pragma once

#include "Khrysalis/Core/Base.h"
#include "Khrysalis/Debug/Log.h"

#include <filesystem>

#ifdef KAL_ENABLE_ASSERTS
	#define KAL_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { KAL##type##ERROR(msg, __VA_ARGS__); KAL_DEBUGBREAK(); } }
	#define KAL_INTERNAL_ASSERT_WITH_MSG(type, check, ...) KAL_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define KAL_INTERNAL_ASSERT_NO_MSG(type, check) KAL_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", KAL_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
	
	#define KAL_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define KAL_INTERNAL_ASSERT_GET_MACRO(...) KAL_EXPAND_MACRO( KAL_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, KAL_INTERNAL_ASSERT_WITH_MSG, KAL_INTERNAL_ASSERT_NO_MSG) )
	
	#define KAL_ENGINE_ASSERT(...) KAL_EXPAND_MACRO( KAL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_ENGINE_, __VA_ARGS__) )
	#define KAL_ASSERT(...) KAL_EXPAND_MACRO( KAL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#else
	#define KAL_ENGINE_ASSERT(...)
	#define KAL_ASSERT(...)
#endif