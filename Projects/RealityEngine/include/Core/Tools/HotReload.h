// Copyright Reality Engine. All Rights Reserved.

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <unordered_map>
#include <filesystem>
#include <chrono>
#include <string>
#include <span>

#include "Core/Platform.h"

namespace reality {
	class RE_CORE HotReload final {
	public:
		explicit HotReload(std::string_view dllPath, std::span<std::string> procs = {});
		void Poll();
		void Reload();
		FARPROC GetProc(std::string_view name);

	private:
		std::string m_Path, m_TempName;
		std::filesystem::file_time_type m_LastWriteTime;
		HMODULE m_Module{};
		std::unordered_map<std::string, FARPROC> m_Procs;
	};
}