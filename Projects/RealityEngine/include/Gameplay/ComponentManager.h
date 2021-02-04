// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <unordered_map>
#include <vector>
#include <span>

#include "Gameplay/Component/Component.h"

namespace reality {
	class ComponentManager {
	public:
		ComponentManager();

		template <class T>
		std::span<const Component*> GetComponents() requires std::derived_from<T, Component>;

		void AddComponent(const Component* comp);
		void RemoveComponent(const Component* comp);

	private:
		std::unordered_map<rttr::type, std::vector<const Component*>> m_Components;
	};
}

inline reality::ComponentManager::ComponentManager() {
	for (const auto& type : rttr::type::get<Component>().get_derived_classes()) {
		m_Components[type];
	}
}

inline void reality::ComponentManager::AddComponent(const Component* comp) {
	m_Components.at(rttr::type::get(*comp)).emplace_back(comp);
}

inline void reality::ComponentManager::RemoveComponent(const Component* comp) {
	std::erase(m_Components.at(rttr::type::get(*comp)), comp);
}

template <class T>
std::span<const reality::Component*> reality::ComponentManager::GetComponents() requires std::derived_from<T, Component> {
	return m_Components.at(rttr::type::get<T>());
}