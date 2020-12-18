// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Scene.h"

namespace reality {
	class SceneManager {
	public:
		Scene* ActiveScene{};

		Scene& CreateScene(std::string_view name);
		Scene* GetScene(std::string name) const;

	private:
		std::unordered_map<std::string, std::unique_ptr<Scene>>	m_Scenes;
	};

	RE_CORE extern SceneManager* g_SceneManager;
}

inline reality::Scene& reality::SceneManager::CreateScene(std::string_view name) {
	return *(ActiveScene = m_Scenes.emplace(std::make_pair(name, std::make_unique<Scene>(name))).first->second.get());
}

inline reality::Scene* reality::SceneManager::GetScene(std::string name) const {
	const auto it{ m_Scenes.find(name) };
	return it != m_Scenes.cend() ? it->second.get() : nullptr;
}