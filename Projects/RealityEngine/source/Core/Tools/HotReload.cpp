// Copyright Reality Engine. All Rights Reserved.

#include "Core/Tools/HotReload.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <chrono>

Reality::HotReload::HotReload(std::string_view dllPath, std::span<std::string> procs) :
	m_Path{ std::string{ dllPath } + "Game.dll" }, m_TempName{ m_Path + ".re.dll" }
{
	for (const auto& proc : procs) {
		m_Procs[proc];
	}
	Poll();
}

void Reality::HotReload::Poll() {
	auto file{ CreateFileA(m_Path.c_str(),
		GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) };

	if (file == INVALID_HANDLE_VALUE) {
		return;
	}

	auto lastWriteTime{ std::filesystem::last_write_time(m_Path) };
	if (m_LastWriteTime < lastWriteTime) {
		if (m_Module) {
			FreeLibrary((HMODULE)m_Module);
			m_Module = nullptr;
		}

		if (std::filesystem::copy_file(m_Path, m_TempName, std::filesystem::copy_options::overwrite_existing)) {
			m_Module = LoadLibraryA(m_TempName.c_str());
			if (m_Module) {
				for (auto& [name, proc] : m_Procs) {
					proc = GetProcAddress((HMODULE)m_Module, name.c_str());
					m_LastWriteTime = lastWriteTime;
				}
			}
		}
	}
	CloseHandle(file);
}

void Reality::HotReload::Reload() {
	auto file{ CreateFileA(m_Path.c_str(),
		GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) };

	if (file == INVALID_HANDLE_VALUE) {
		return;
	}

	auto lastWriteTime{ std::filesystem::last_write_time(m_Path) };
	if (m_Module) {
		FreeLibrary((HMODULE)m_Module);
		m_Module = nullptr;
	}

	if (std::filesystem::copy_file(m_Path, m_TempName, std::filesystem::copy_options::overwrite_existing)) {
		m_Module = LoadLibraryA(m_TempName.c_str());
	}
	CloseHandle(file);
}

void* Reality::HotReload::GetProc(std::string_view name) {
	return m_Procs.at(name.data());
}