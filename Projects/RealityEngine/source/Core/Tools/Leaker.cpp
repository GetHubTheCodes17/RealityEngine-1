// Copyright Reality Engine. All Rights Reserved.

#include "Core/Tools/Leaker.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

reality::Leaker::Leaker(const char* filename) :
	m_FileName{ filename }, m_TempLeak{ new char[17] } 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	strcpy_s(m_TempLeak, 17, "--ExternalLeak--");
}

reality::Leaker::~Leaker() {
	auto logFile{ CreateFileA(static_cast<LPCSTR>(m_FileName), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, nullptr) };
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, logFile);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, logFile);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, logFile);
	_CrtDumpMemoryLeaks();

	CloseHandle(logFile);
	delete m_TempLeak;
}