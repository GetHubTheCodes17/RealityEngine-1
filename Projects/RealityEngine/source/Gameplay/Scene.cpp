// Copyright Reality Engine. All Rights Reserved.

#include "Gameplay/Scene.h"

void reality::Scene::DestroyGameObjectUnsafe(GameObject& object) {
	std::function<void(GameObject&)> SetToBeDestroyed = [&SetToBeDestroyed](auto& root) {
		root.m_Id = -1;
		for (auto child : root.Transform.GetChildren()) {
			SetToBeDestroyed(child->GetGameObject());
		}
	};
	SetToBeDestroyed(object);

	m_GameObjects.erase(std::remove_if(m_GameObjects.begin(), m_GameObjects.end(), 
		[](auto& elem) { return elem->m_Id == -1; }), m_GameObjects.end());
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