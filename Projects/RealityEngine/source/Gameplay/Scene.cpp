// Copyright Reality Engine. All Rights Reserved.

#include "Gameplay/Scene.h"

reality::GameObject* reality::Scene::FindGameObject(std::string_view name) {
	if (auto object{ std::ranges::find_if(m_GameObjects,
		[&name](const auto& object) { return object->Name == name; }) }; object != m_GameObjects.cend())
	{
		if (auto removed{ std::ranges::find_if(m_ToBeRemoved,
			[object](auto& elem) { return elem.second == object->get(); }) }; removed == m_ToBeRemoved.cend())
		{
			return object->get();
		}
	}
	return nullptr;
}

void reality::Scene::Update() {
	if (!m_ToBeInstantiate.empty()) {
		for (const auto& instantiate : m_ToBeInstantiate) {
			instantiate();
		}
		m_ToBeInstantiate.clear();
	}

	for (auto removed{ m_ToBeRemoved.cbegin() }; removed != m_ToBeRemoved.cend(); ) {
		const auto& [time, object] { *removed };
		if (time - std::chrono::steady_clock::now() < std::chrono::milliseconds::zero()) {
			DestroyGameObjectUnsafe(*object);
			removed = m_ToBeRemoved.erase(removed);
		}
		else {
			++removed;
		}
	}
}

void reality::Scene::DestroyGameObjectUnsafe(GameObject& object) {
	std::function<void(GameObject&)> SetToBeDestroyed = [&SetToBeDestroyed](auto& root) {
		root.m_Id = (uint64)-1;
		for (auto child : root.Transform.GetChildren()) {
			SetToBeDestroyed(child->GetGameObject());
		}
	};
	SetToBeDestroyed(object);
	std::erase_if(m_GameObjects, [](auto& go) { return go->m_Id == -1; });
	std::erase(m_Roots, &object);
}