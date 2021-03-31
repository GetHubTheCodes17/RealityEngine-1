// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <string_view>
#include <concepts>
#include <ranges>
#include <span>

#include "Core/Platform.h"
#include "Component/Transform.h"

namespace Reality {
	class Scene;

	class RE_CORE GameObject final {
		friend Scene;

	public:
		std::string	Name;
		CTransform Transform;
		bool IsActive{ true };

		GameObject(std::string_view name = {});
		GameObject(const GameObject&);
		GameObject& operator=(const GameObject&) = delete;
		GameObject(GameObject&&) noexcept = default;
		GameObject& operator=(GameObject&&) noexcept = default;
		~GameObject();

		template <class T>
		T* AddComponent() requires std::derived_from<T, Component>;
		template <class T>
		bool HasComponent() const requires std::derived_from<T, Component>;
		template <class T>
		T* GetComponent() const requires std::derived_from<T, Component>;
		template <class T>
		T* GetComponentInParent() const requires std::derived_from<T, Component>;
		template <class T>
		T* GetComponentInChildren() const requires std::derived_from<T, Component>;
		template <class T>
		std::vector<T*> GetComponents() const requires std::derived_from<T, Component>;
		template <class T>
		std::vector<T*> GetComponentsInParent() const requires std::derived_from<T, Component>;
		template <class T>
		std::vector<T*> GetComponentsInChildren() const requires std::derived_from<T, Component>;
		template <class T>
		void RemoveComponent() requires std::derived_from<T, Component>;
		template <class T>
		void RemoveComponents() requires std::derived_from<T, Component>;

		void AddComponent(const Component& component);
		void RemoveAllComponents();
		Scene& GetScene() const;
		uint64 GetId() const;
		void SetParent(GameObject& parent);

	private:
		std::vector<std::unique_ptr<Component>> m_Components;
		Scene* m_Scene{};
		uint64 m_Id{};

		void AddManagerComponent(Component* comp);
		void RemoveManagerComponent(Component* comp);

	private:
		friend class cereal::access;
		template <class Archive>
		void load(Archive& archive);
		template <class Archive>
		void save(Archive& archive) const;
	};
}

template <class T>
T* Reality::GameObject::AddComponent() requires std::derived_from<T, Component> {
	if (HasComponent<T>()) {
		return nullptr;
	}

	auto component{ m_Components.emplace_back(std::make_unique<T>()).get() };
	component->m_GameObject = this;

	AddManagerComponent(component);
	return static_cast<T*>(component);
}

template <class T>
bool Reality::GameObject::HasComponent() const requires std::derived_from<T, Component> {
	return std::ranges::any_of(m_Components, [](auto& comp) { return rttr::type::get<T>() == rttr::type::get(*comp); });
}

template <class T>
T* Reality::GameObject::GetComponent() const requires std::derived_from<T, Component> {
	for (const auto& component : m_Components) {
		if (auto comp{ rttr::rttr_cast<T*>(component.get()) }) {
			return comp;
		}
	}
	return nullptr;
}

template <class T>
T* Reality::GameObject::GetComponentInParent() const requires std::derived_from<T, Component> {
	return !Transform.GetParent() ? GetComponent() : Transform.GetParent()->GetGameObject().GetComponent();
}

template <class T>
T* Reality::GameObject::GetComponentInChildren() const requires std::derived_from<T, Component> {
	for (const auto& child : Transform.GetChildren()) {
		if (auto component{ child->GetGameObject().GetComponent() }) {
			return component;
		}
	}
	return GetComponent();
}

template <class T>
std::vector<T*> Reality::GameObject::GetComponents() const requires std::derived_from<T, Component> {
	std::vector<T*> components;
	for (const auto& component : m_Components) {
		if (auto comp{ rttr::rttr_cast<T*>(component.get()) }) {
			components.emplace_back(comp);
		}
	}
	return components;
}

template <class T>
std::vector<T*> Reality::GameObject::GetComponentsInParent() const requires std::derived_from<T, Component> {
	return !Transform.GetParent() ? GetComponents() : Transform.GetParent()->GetGameObject().GetComponents();
}

template <class T>
std::vector<T*> Reality::GameObject::GetComponentsInChildren() const requires std::derived_from<T, Component> {
	if (!Transform.GetChildrenSize()) {
		return GetComponents();
	}

	std::vector<T*> components;
	for (const auto& child : Transform.GetChildren()) {
		for (const auto& component : child->GetGameObject().m_Components) {
			if (auto comp{ rttr::rttr_cast<T*>(component.get()) }) {
				components.emplace_back(comp);
			}
		}
	}
	return components;
}

template <class T>
void Reality::GameObject::RemoveComponent() requires std::derived_from<T, Component> {
	for (auto it{ m_Components.cbegin() }; it != m_Components.cend(); ++it) {
		if (auto comp{ rttr::rttr_cast<T*>(it->get()) }) {
			RemoveManagerComponent(comp);
			m_Components.erase(it);
			return;
		}
	}
}

template <class T>
void Reality::GameObject::RemoveComponents() requires std::derived_from<T, Component> {
	for (auto it{ m_Components.cbegin() }; it != m_Components.cend(); ) {
		if (auto comp{ rttr::rttr_cast<T*>(it->get()) }) {
			RemoveManagerComponent(comp);
			it = m_Components.erase(it);
		}
		else {
			++it;
		}
	}
}

template <class Archive>
void Reality::GameObject::load(Archive& archive) {
	archive(CEREAL_NVP(Name));
	archive(CEREAL_NVP(m_Id));
	archive(CEREAL_NVP(IsActive));
	archive(CEREAL_NVP(Transform));
	Transform.m_GameObject = this;
	archive(CEREAL_NVP(m_Components));
}

template <class Archive>
void Reality::GameObject::save(Archive& archive) const {
	archive(CEREAL_NVP(Name));
	archive(CEREAL_NVP(m_Id));
	archive(CEREAL_NVP(IsActive));
	archive(CEREAL_NVP(Transform));
	archive(CEREAL_NVP(m_Components));
}