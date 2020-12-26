// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>

#include "Gameplay/Scene.h"
#include "Windowing/KeyCodes.h"

namespace reality {
	class EditorHierarchy {
	public:
		void Draw(Scene& scene);
		const std::vector<GameObject*>& GetCurrents() const;

	private:
		std::vector<GameObject*> m_Currents;
		bool m_IsDragging{};

		void DisplayTree(GameObject& root);
		void Selecting(GameObject& root, bool isCurrent);
		void Dragging(GameObject& hovered);
	};
}

inline void reality::EditorHierarchy::Draw(Scene& scene) {
	ImGui::Begin("Hierarchy");
	{
		if (!m_Currents.empty() && ImGui::IsKeyPressed(keycode::RE_KEY_DELETE)) {
			for (auto go : m_Currents) {
				scene.DestroyGameObject(*go);
			}
			m_Currents.clear();
		}

		if (ImGui::Button("Create Empty")) {
			auto& object{ scene.CreateGameObject("GameObject") };
			if (!m_Currents.empty()) {			
				object.SetParent(*m_Currents.back());
			}
		}

		if (ImGui::IsKeyDown(keycode::RE_KEY_LEFT_CONTROL)) {
			if (ImGui::IsKeyPressed(keycode::RE_KEY_D)) {
				for (auto go : m_Currents) {
					scene.CreateGameObject(*go);
				}
			}
			else if (ImGui::IsKeyPressed(keycode::RE_KEY_Q)) {
				m_Currents.clear();
				for (auto& elem : scene.GetGameObjects()) {
					m_Currents.emplace_back(elem.get());
				}
			}
		}

		for (auto root : scene.GetRootsGameObjects()) {
			DisplayTree(*root);
		}

		if (!m_Currents.empty()) {
			m_Currents.erase(std::remove(m_Currents.begin(), m_Currents.end(), nullptr), m_Currents.end());
		}
	}
	ImGui::End();
}

inline const std::vector<reality::GameObject*>& reality::EditorHierarchy::GetCurrents() const {
	return m_Currents;
}

inline void reality::EditorHierarchy::DisplayTree(GameObject& root) {
	const auto isCurrent{ std::any_of(m_Currents.begin(), m_Currents.end(), [&root](auto& elem) { return elem == &root; }) };
	const auto flags{ ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen 
		| ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth 
		| (!root.Transform.GetChildrenSize() ? ImGuiTreeNodeFlags_Leaf : 0) | (isCurrent ? ImGuiTreeNodeFlags_Selected : 0) };
	const auto isOpen{ ImGui::TreeNodeEx(reinterpret_cast<void*>(root.GetId()), flags, root.Name.c_str()) };

	Selecting(root, isCurrent);
	Dragging(root);

	if (isOpen) {
		for (auto child : root.Transform.GetChildren()) {
			DisplayTree(child->GetGameObject());
		}

		if (!m_Currents.empty() && ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) 
			&& !ImGui::IsAnyItemHovered()) 
		{
			m_Currents.clear();
		}

		ImGui::TreePop();
	}
}

inline void reality::EditorHierarchy::Selecting(GameObject& root, bool isCurrent) {
	if (ImGui::IsItemClicked()) {
		if (ImGui::IsKeyDown(keycode::RE_KEY_LEFT_CONTROL)) {
			if (!isCurrent) {
				m_Currents.emplace_back(&root);
			}
			else {
				*std::find(m_Currents.begin(), m_Currents.end(), &root) = nullptr;
			}
		}
		else if (!isCurrent) {
			m_Currents.clear();
			m_Currents.emplace_back(&root);
		}
	}
}

inline void reality::EditorHierarchy::Dragging(GameObject& hovered) {
	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload("Object_Hierarchy", &hovered, sizeof(&hovered));
		m_IsDragging = true;
		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget()) {
		if (ImGui::AcceptDragDropPayload("Object_Hierarchy")) {
			for (auto go : m_Currents) {
				go->SetParent(hovered);
			}
		}
		m_IsDragging = false;
		ImGui::EndDragDropTarget();
	}

	if (m_IsDragging && !m_Currents.empty() && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
		for (auto go : m_Currents) {
			go->Transform.SetParent(nullptr);
		}
		m_IsDragging = false;
	}
}