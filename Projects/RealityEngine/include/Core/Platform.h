// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cstdint>

#ifndef __cplusplus
#error The Engine requires C++ compiler to be used.
#endif

#if defined(_WIN64)
	#define RE_WINDOWS_PLATFORM 1
#elif __APPLE__
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE
		#define RE_IPHONE_PLATFORM 1
	#elif TARGET_OS_MAC
		#define RE_MAC_PLATFORM 1
	#else
		#error "Unknown Apple platform"
	#endif
#elif __linux__
	#if __ANDROID__ 
		#define RE_ANDROID_PLATFORM 1
	#else
		#define RE_LINUX_PLATFORM 1
	#endif
#elif __unix__
	#define RE_UNIX_PLATFORM 1
#elif defined(_POSIX_VERSION)
	#error "Cannot compile on Posix platform"
#else
	#error "Unknown compiler"
#endif

#ifndef RE_WINDOWS_PLATFORM
#define RE_WINDOWS_PLATFORM 0
#endif
#ifndef RE_MAC_PLATFORM
#define RE_MAC_PLATFORM 0
#endif
#ifndef RE_IPHONE_PLATFORM
#define RE_IPHONE_PLATFORM 0
#endif
#ifndef RE_ANDROID_PLATFORM
#define RE_ANDROID_PLATFORM 0
#endif
#ifndef RE_LINUX_PLATFORM
#define RE_LINUX_PLATFORM 0
#endif
#ifndef RE_UNIX_PLATFORM
#define RE_UNIX_PLATFORM 0
#endif

#define RE_LIB_GLFW 1
#define RE_LIB_OPENGL 1

#define RE_WINDOW_WIDTH 1200
#define RE_WINDOW_HEIGHT 800

#define RE_LOG_ENABLE 1
#define RE_PROFILE_ENABLE 1
#define RE_SIMD_ENABLE 1
#define RE_ASSERTIONS_ENABLE 1

namespace reality {
	using int8 = std::int8_t;
	using int16 = std::int16_t;
	using int32 = std::int32_t;
	using int64 = std::int64_t;
	using uint8 = std::uint8_t;
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	using uint64 = std::uint64_t;

	inline constexpr const char* g_ResourcesPath{ "../../Resources/" };
	inline constexpr const char* g_ResourcesExtension{ ".binary" };
}

#if RE_EXPORT
#define RE_CORE __declspec(dllexport)
#else
#define RE_CORE __declspec(dllimport)
#endif

#ifndef NDEBUG
#define RE_DEBUG 1
#else
#define RE_DEBUG 0
#endif

#if RE_ASSERTIONS_ENABLE
#include <cstdio>
#ifdef _MSC_VER
#define RE_ASSERT(expr, message)														\
		if (!(expr)) {																	\
			std::printf("Assertion failed : (%s), %s\nFunction %s, file %s, line %d.\n",\
				#expr, message, __func__, __FILE__, unsigned(__LINE__));				\
			__debugbreak();																\
		}
#else
#include <cassert>
#define RE_ASSERT(expr) assert(expr);
#endif
#else
#define RE_ASSERT(expr);
#endif