// Copyright Reality Engine. All Rights Reserved.

#include "Gameplay/GameObject.h"

#include "Gameplay/SceneManager.h"
#include "Core/Tools/Randomizer.h"

reality::GameObject::GameObject(std::string_view name) :
	Name{ name }, m_Id{ g_Randomizer->GetInt(std::numeric_limits<uint64>::min(), std::numeric_limits<uint64>::max()) }
{
	RE_ASSERT(g_SceneManager->ActiveScene, "Cannot create GameObject without one active Scene");

	m_Scene = g_SceneManager->ActiveScene;
	Transform.m_GameObject = this;
}

reality::GameObject::GameObject(const GameObject& other) :
	Name{ other.Name }, Transform{ other.Transform }, IsActive{ other.IsActive }, m_Scene{ other.m_Scene },
	m_Id{ g_Randomizer->GetInt(std::numeric_limits<uint64>::min(), std::numeric_limits<uint64>::max()) }
{
	for (const auto& component : other.m_Components) {
		auto& comp{ m_Components.emplace_back(component->Clone()) };
		comp->m_GameObject = this;
		AddManagerComponent(comp.get());
	}
	Transform.m_GameObject = this;
}

reality::GameObject::~GameObject() {
	RemoveAllComponents();
}

void reality::GameObject::RemoveAllComponents() {
	for (const auto& component : m_Components) {
		m_Scene->m_Manager.RemoveComponent(component.get());
	}
	m_Components.clear();
}

reality::Scene& reality::GameObject::GetScene() const {
	return *m_Scene;
}

reality::uint64 reality::GameObject::GetId() const {
	return m_Id;
}

void reality::GameObject::SetParent(GameObject& parent) {
	auto wasRoot{ Transform.IsRoot() };
	Transform.SetParent(&parent.Transform);

	if (Transform.IsRoot() && !wasRoot) {
		m_Scene->m_Roots.emplace_back(this);
	}
	else if (!Transform.IsRoot() && wasRoot) {
		std::erase(m_Scene->m_Roots, this);
	}
}

void reality::GameObject::AddComponent(const Component& component) {
	if (std::ranges::any_of(m_Components,
		[&component](auto& comp) { return rttr::type::get(component) == rttr::type::get(*comp); }))
	{
		return;
	}

	auto comp{ m_Components.emplace_back(component.Clone()).get() };
	comp->m_GameObject = this;
	AddManagerComponent(comp);
}

void reality::GameObject::AddManagerComponent(Component* comp) {
	m_Scene->m_Manager.AddComponent(comp);
}

void reality::GameObject::RemoveManagerComponent(Component* comp) {
	m_Scene->m_Manager.RemoveComponent(comp);
}