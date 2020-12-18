// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <unordered_map>
#include <fstream>
#include <string>

#include "Core/Platform.h"

namespace reality {
	class PlayerPref {
	public:
		explicit PlayerPref(std::string_view fileName = "PlayerPref.txt");
		~PlayerPref();

		void DeleteAll();
		void DeleteKey(const char* key);
		void Save() const;
		bool HasKey(const char* key) const;
		float GetFloat(const char* key) const;
		int GetInt(const char* key) const;
		std::string GetString(const char* key) const;
		void SetFloat(const char* key, float value);
		void SetInt(const char* key, int value);
		void SetString(const char* key, std::string value);

	private:
		std::string m_FileName;
		std::unordered_map<std::string, std::string> m_Values;
		bool m_HasChanged{};
	};

	RE_CORE extern PlayerPref* g_PlayerPref;
}

inline reality::PlayerPref::PlayerPref(std::string_view fileName) :
	m_FileName{ fileName } 
{
	std::ifstream file{ m_FileName };
	std::string key, value;
	while (file >> key >> value) {
		m_Values.emplace(std::make_pair(key, value));
	}
}

inline reality::PlayerPref::~PlayerPref() {
	Save();
}

inline void reality::PlayerPref::DeleteAll() {
	std::ofstream{ m_FileName, std::ofstream::trunc };
	m_Values.clear();
	m_HasChanged = true;
}

inline void reality::PlayerPref::DeleteKey(const char* key) {
	if (auto it{ m_Values.find(key) }; it != m_Values.cend()) {
		m_Values.erase(it);
		m_HasChanged = true;
	}
}

inline void reality::PlayerPref::Save() const {
	if (!m_HasChanged) {
		return;
	}

	std::ofstream file{ m_FileName, std::ofstream::trunc };
	for (const auto& [key, value] : m_Values) {
		file << key << ' ' << value << '\n';
	}
}

inline bool reality::PlayerPref::HasKey(const char* key) const {
	return m_Values.find(key) != m_Values.cend();
}

inline float reality::PlayerPref::GetFloat(const char* key) const {
	return std::stof(m_Values.at(key));
}

inline int reality::PlayerPref::GetInt(const char* key) const {
	return std::stoi(m_Values.at(key));
}

inline std::string reality::PlayerPref::GetString(const char* key) const {
	return m_Values.at(key);
}

inline void reality::PlayerPref::SetFloat(const char* key, float value) {
	m_Values[key] = std::to_string(value);
	m_HasChanged = true;
}

inline void reality::PlayerPref::SetInt(const char* key, int value) {
	m_Values[key] = std::to_string(value);
	m_HasChanged = true;
}

inline void reality::PlayerPref::SetString(const char* key, std::string value) {
	m_Values[key] = std::move(value);
	m_HasChanged = true;
}