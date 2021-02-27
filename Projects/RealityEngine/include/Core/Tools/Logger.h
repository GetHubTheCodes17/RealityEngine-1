// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <functional>
#include <iosfwd>
#include <mutex>

#include "Core/Platform.h"

namespace reality {
	enum class LogVerbosity { Info, Warning, Error };

	class RE_CORE Logger {
	public:
		unsigned Severity{};
		std::function<void(const char* message)> Callback;

		Logger();
		~Logger();

		void Log(const char* file, int line, const char* func, LogVerbosity verbosity, unsigned severity,
			const char* message, ...);

	private:
		std::unique_ptr<std::ofstream> m_File;
		std::mutex m_Lock;
	};

	RE_CORE extern Logger* g_Logger;
}

#ifdef RE_LOG_ENABLE
	#define RE_LOG_INFO(message, ...) \
		reality::g_Logger->Log(__FILE__, __LINE__, __func__, reality::LogVerbosity::Info, 0, "[INFO] " message "\n", ##__VA_ARGS__);
	#define RE_LOG_WARNING(message, ...) \
		reality::g_Logger->Log(__FILE__, __LINE__, __func__, reality::LogVerbosity::Warning, 1, "[WARN] " message "\n", ##__VA_ARGS__);
	#define RE_LOG_ERROR(message, ...) \
		reality::g_Logger->Log(__FILE__, __LINE__, __func__, reality::LogVerbosity::Error, 2, "[ERR] " message "\n", ##__VA_ARGS__);
#else
	#define RE_LOG_INFO(message, ...);
	#define RE_LOG_WARNING(message, ...);
	#define RE_LOG_ERROR(message, ...);
#endif