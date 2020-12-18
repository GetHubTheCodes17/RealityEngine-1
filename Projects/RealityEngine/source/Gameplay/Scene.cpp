// Copyright Reality Engine. All Rights Reserved.

#include "Gameplay/Scene.h"

void reality::Scene::DestroyGameObjectUnsafe(const GameObject& object) {
	for (auto it{ m_GameObjects.cbegin() }; it != m_GameObjects.cend(); ++it) {
		if (it->get() != &object) {
			continue;
		}

		if (auto parent{ object.Transform.GetParent() }) {
			if (auto parentOfParent{ parent->GetParent() }) {
				parent = parentOfParent;
			}
			for (const auto& child : object.Transform.GetChildren()) {
				child->SetParent(parent);
			}
		}

		(*it)->RemoveAllComponents();
		m_GameObjects.erase(it);
		break;
	}
	m_ToBeRemoved.erase(m_ToBeRemoved.cbegin());
}

void reality::Scene::UpdateDestroyed() {
	if (m_ToBeRemoved.empty()) {
		return;
	}

	const auto& [time, object] { *m_ToBeRemoved.cbegin() };
	if (time - Clock::now() < std::chrono::milliseconds::zero()) {
		DestroyGameObjectUnsafe(*object);
	}
}

reality::GameObject* reality::Scene::FindGameObject(std::string_view name) const {
	if (auto it{ std::find_if(m_GameObjects.cbegin(), m_GameObjects.cend(),
		[&name](const auto& object) { return object->Name == name; }) }; it != m_GameObjects.cend())
	{
		if (auto ite{ std::find_if(m_ToBeRemoved.cbegin(), m_ToBeRemoved.cend(),
			[it](auto& elem) { return elem.second == it->get(); }) }; ite == m_ToBeRemoved.cend())
		{
			return it->get();
		}
	}
	return nullptr;
}