// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>

#include "Core/Platform.h"
#include "Gameplay/Component/Component.h"

namespace reality {
	class ComponentManager {
	public:
		void AddComponent(Component* comp);
		void RemoveComponent(Component* comp);
		template <class T>
		const std::vector<Component*>* GetComponents() const;

	private:
		std::unordered_map<std::type_index, std::vector<Component*>> m_Components;
	};
}

inline void reality::ComponentManager::AddComponent(Component* comp) {
	m_Components[typeid(*comp)].emplace_back(comp);
}

inline void reality::ComponentManager::RemoveComponent(Component* comp) {
	auto it{ m_Components.find(typeid(*comp)) };
	if (it == m_Components.cend()) {
		return;
	}
	it->second.erase(std::remove(std::begin(it->second), std::end(it->second), comp), std::end(it->second));

	if (it->second.empty()) {
		m_Components.erase(it);
	}
}

template <class T>
const std::vector<reality::Component*>* reality::ComponentManager::GetComponents() const {
	static_assert(std::is_base_of_v<Component, T>);

	const auto it{ m_Components.find(typeid(T)) };
	return it != m_Components.cend() ? &it->second : nullptr;
}