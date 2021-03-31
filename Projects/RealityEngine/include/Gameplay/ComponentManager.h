// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <unordered_map>
#include <vector>
#include <span>

#include "Gameplay/Component/MonoBehaviour.h"
#include "Gameplay/Component/Component.h"

namespace Reality {
	class ComponentManager {
	public:
		ComponentManager();

		template <class T>
		std::span<Component*> GetComponents() requires std::derived_from<T, Component>;

		void AddComponent(Component* comp);
		void RemoveComponent(Component* comp);

	private:
		std::unordered_map<rttr::type, std::vector<Component*>> m_Components;
	};
}

inline Reality::ComponentManager::ComponentManager() {
	for (const auto& type : rttr::type::get<Component>().get_derived_classes()) {
		m_Components[type];
	}
	m_Components[rttr::type::get<CMonoBehaviour>()];
}

inline void Reality::ComponentManager::AddComponent(Component* comp) {
	if (rttr::type::get(*comp).is_derived_from<CMonoBehaviour>()) {
		m_Components.at(rttr::type::get<CMonoBehaviour>()).emplace_back(comp);
	}
	else {
		m_Components.at(rttr::type::get(*comp)).emplace_back(comp);
	}
}

inline void Reality::ComponentManager::RemoveComponent(Component* comp) {
	std::erase(m_Components.at(rttr::type::get(*comp)), comp);
}

template <class T>
std::span<Reality::Component*> Reality::ComponentManager::GetComponents() requires std::derived_from<T, Component> {
	return m_Components.at(rttr::type::get<T>());
}