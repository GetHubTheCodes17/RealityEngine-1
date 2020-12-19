// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <chrono>
#include <map>

#include "Gameplay/GameObject.h"

namespace reality {
	class RE_CORE Scene {
		using Clock = std::chrono::steady_clock;
	public:
		std::string	Name;

		explicit Scene(std::string_view name);
		Scene(Scene&&) noexcept = default;
		Scene& operator=(Scene&&) noexcept = default;

		void Update();
		GameObject& CreateGameObject(std::string_view name);
		GameObject& CreateGameObject(const GameObject& copy);
		GameObject* FindGameObject(std::string_view name) const;
		void DestroyGameObject(GameObject& object, std::chrono::milliseconds time = {});
		void Instantiate(std::function<void()> func);
		std::vector<GameObject*> GetRootsGameObjects() const;
		const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;
		const ComponentManager& GetComponentManager() const;

	private:
		ComponentManager m_Manager;
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;
		std::vector<std::function<void()>> m_ToBeInstantiate;
		std::multimap<Clock::time_point, GameObject*> m_ToBeRemoved;

		void DestroyGameObjectUnsafe(const GameObject& object);
		void UpdateDestroyed();
		void UpdateInstantiated();
	};
}

inline reality::Scene::Scene(std::string_view name) :
	Name{ name }
{}

inline void reality::Scene::Update() {
	UpdateDestroyed();
	UpdateInstantiated();
}

inline reality::GameObject& reality::Scene::CreateGameObject(std::string_view name) {
	return *m_GameObjects.emplace_back(std::make_unique<GameObject>(name, this, &m_Manager));
}

inline reality::GameObject& reality::Scene::CreateGameObject(const GameObject& copy) {
	return *m_GameObjects.emplace_back(std::make_unique<GameObject>(copy));
}

inline void reality::Scene::DestroyGameObject(GameObject& object, std::chrono::milliseconds time) {
	if (std::find_if(m_ToBeRemoved.cbegin(), m_ToBeRemoved.cend(),
		[&object](const auto& element) { return element.second == &object; }) == m_ToBeRemoved.cend()) 
	{
		m_ToBeRemoved.emplace(Clock::now() + time, &object);
	}
}

inline void reality::Scene::Instantiate(std::function<void()> func) {
	m_ToBeInstantiate.emplace_back(func);
}

inline std::vector<reality::GameObject*> reality::Scene::GetRootsGameObjects() const {
	std::vector<GameObject*> roots;
	for (const auto& object : m_GameObjects) {
		if (object->Transform.IsRoot()) {
			roots.emplace_back(object.get());
		}
	}
	return roots;
}

inline const std::vector<std::unique_ptr<reality::GameObject>>& reality::Scene::GetGameObjects() const {
	return m_GameObjects;
}

inline const reality::ComponentManager& reality::Scene::GetComponentManager() const {
	return m_Manager;
}

inline void reality::Scene::UpdateInstantiated() {
	if (m_ToBeInstantiate.empty()) {
		return;
	}

	for (const auto& instantiate : m_ToBeInstantiate) {
		instantiate();
	}
	m_ToBeInstantiate.clear();
}