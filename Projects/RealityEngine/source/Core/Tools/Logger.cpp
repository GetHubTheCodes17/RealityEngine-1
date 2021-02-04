// Copyright Reality Engine. All Rights Reserved.

#include "Core/Tools/Logger.h"

#include <cstdarg>
#include <fstream>

reality::Logger::Logger() :
	m_File{ std::make_unique<std::ofstream>(L"Logs/Logs.txt", std::ios::out | std::ios::trunc) }
{}

reality::Logger::~Logger() = default;

void reality::Logger::Log(const char*, int line, const char* func, LogVerbosity, unsigned severity, 
	const char* message, ...) 
{
	if (severity < Severity) {
		return;
	}

	std::lock_guard guard{ m_Lock };

	static constexpr auto s_BufferSize{ 512ull };
	char buffer[s_BufferSize];

	const auto charSize{ std::snprintf(buffer, s_BufferSize, "Function %s line %d at %s.\n", func, line, __TIME__) };
	m_File->write(buffer, charSize);

	std::va_list args{};
	va_start(args, message);
	const auto messageSize{ std::vsnprintf(buffer, s_BufferSize, message, args) };
	va_end(args);

	m_File->write(buffer, messageSize);

	if (Callback) {
		Callback(buffer);
	}
	else {
		std::puts(buffer);
	}
}