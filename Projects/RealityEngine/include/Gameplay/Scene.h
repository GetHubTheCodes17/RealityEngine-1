// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <chrono>
#include <map>

#include "Core/Platform.h"
#include "ComponentManager.h"
#include "GameObject.h"

namespace reality {
	namespace editor { class Editor; }

	class RE_CORE Scene final {
		friend GameObject;
		friend class ComponentSystem;
		friend class editor::Editor;

	public:
		std::string	Name;

		Scene(std::string_view name);
		Scene(Scene&&) noexcept = default;
		Scene& operator=(Scene&&) noexcept = default;

		GameObject& CreateGameObject(std::string_view name);
		GameObject& CreateGameObject(const GameObject& copy);
		GameObject* FindGameObject(std::string_view name);
		void DestroyGameObject(GameObject& object, std::chrono::milliseconds time = {});
		void AddCallback(std::function<void()> func);
		std::span<GameObject*> GetRootsGameObjects();

	private:
		ComponentManager m_Manager;
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;
		std::vector<GameObject*> m_Roots;
		std::vector<std::function<void()>> m_ToBeInstantiate;
		std::multimap<std::chrono::steady_clock::time_point, GameObject*> m_ToBeRemoved;

		void Update();
		void DestroyGameObjectUnsafe(GameObject& object);

	private:
		friend class cereal::access;
		template <class Archive>
		void load(Archive& archive);
		template <class Archive>
		void save(Archive& archive) const;
	};
}

inline reality::Scene::Scene(std::string_view name) :
	Name{ name }
{}

inline reality::GameObject& reality::Scene::CreateGameObject(std::string_view name) {
	return *m_Roots.emplace_back(m_GameObjects.emplace_back(std::make_unique<GameObject>(name)).get());
}

inline reality::GameObject& reality::Scene::CreateGameObject(const GameObject& copy) {
	auto go{ m_GameObjects.emplace_back(std::make_unique<GameObject>(copy)).get() };
	if (go->Transform.IsRoot()) {
		m_Roots.emplace_back(go);
	}
	return *go;
}

inline void reality::Scene::DestroyGameObject(GameObject& object, std::chrono::milliseconds time) {
	if (std::ranges::find_if(m_ToBeRemoved, [&](auto& elem) { return elem.second == &object; }) == m_ToBeRemoved.cend()) {
		m_ToBeRemoved.emplace(std::chrono::steady_clock::now() + time, &object);
	}
}

inline void reality::Scene::AddCallback(std::function<void()> func) {
	m_ToBeInstantiate.emplace_back(func);
}

inline std::span<reality::GameObject*> reality::Scene::GetRootsGameObjects() {
	return m_Roots;
}

template <class Archive>
void reality::Scene::load(Archive& archive) {
	archive(CEREAL_NVP(Name));
	archive(CEREAL_NVP(m_GameObjects));

	for (auto& object : m_GameObjects) {
		object->m_Scene = this;
		for (auto& comp : object->m_Components) {
			comp->m_GameObject = object.get();
			m_Manager.AddComponent(comp.get());
		}
		if (object->Transform.GetParentId()) {
			auto parent{ std::ranges::find_if(m_GameObjects,
				[&](auto& elem) { return elem->GetId() == object->Transform.GetParentId(); }) 
			};
			if (parent != m_GameObjects.cend()) {
				object->SetParent(**parent);
			}
		}
		else {
			m_Roots.emplace_back(object.get());
		}
	}
}

template <class Archive>
void reality::Scene::save(Archive& archive) const {
	archive(CEREAL_NVP(Name));
	archive(CEREAL_NVP(m_GameObjects));
}