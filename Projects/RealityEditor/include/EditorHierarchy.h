// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>
#include <vector>
#include <span>

#include "Gameplay/Scene.h"
#include "Gameplay/GameObject.h"
#include "Windowing/KeyCodes.h"

namespace reality {
	class EditorHierarchy {
	public:
		void Draw(Scene& scene);
		std::span<GameObject*> GetSelected();

	private:
		std::vector<GameObject*> m_Selected;
		bool m_IsDragging{};

		void HandleShortcuts(Scene& scene);
		void DisplayTree(GameObject& root);
		void Select(GameObject& root, bool isCurrent);
		void Drag(GameObject& hovered);
	};
}

inline void reality::EditorHierarchy::Draw(Scene& scene) {
	ImGui::Begin("Hierarchy");
	{
		HandleShortcuts(scene);

		for (auto root : scene.GetRootsGameObjects()) {
			DisplayTree(*root);
		}

		if (!m_Selected.empty()) {
			std::erase(m_Selected, nullptr);
		}
	}
	ImGui::End();
}

inline std::span<reality::GameObject*> reality::EditorHierarchy::GetSelected() {
	return m_Selected;
}

inline void reality::EditorHierarchy::HandleShortcuts(Scene& scene) {
	if (!m_Selected.empty() && ImGui::IsKeyPressed(keycode::RE_KEY_DELETE)) {
		for (auto go : m_Selected) {
			scene.DestroyGameObject(*go);
		}
		m_Selected.clear();
	}

	if (ImGui::Button("Create Empty")) {
		auto& object{ scene.CreateGameObject("GameObject") };
		if (!m_Selected.empty()) {
			object.SetParent(*m_Selected.back());
		}
	}

	if (ImGui::IsKeyDown(keycode::RE_KEY_LEFT_CONTROL)) {
		if (ImGui::IsKeyPressed(keycode::RE_KEY_D)) {
			for (auto go : m_Selected) {
				scene.CreateGameObject(*go);
			}
		}
		else if (ImGui::IsKeyPressed(keycode::RE_KEY_Q)) {
			m_Selected.clear();
			for (auto& go : scene.GetRootsGameObjects()) {
				m_Selected.emplace_back(go);
				for (auto& child : go->Transform.GetChildren()) {
					m_Selected.emplace_back(&child->GetGameObject());
				}
			}
		}
	}
}

inline void reality::EditorHierarchy::DisplayTree(GameObject& root) {
	const auto isCurrent{ std::ranges::any_of(m_Selected, [&root](auto& elem) { return elem == &root; }) };
	const auto flags{ ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen 
		| ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth 
		| (!root.Transform.GetChildrenSize() ? ImGuiTreeNodeFlags_Leaf : 0) | (isCurrent ? ImGuiTreeNodeFlags_Selected : 0) };
	const auto isOpen{ ImGui::TreeNodeEx(reinterpret_cast<void*>(root.GetId()), flags, root.Name.c_str()) };

	Select(root, isCurrent);
	Drag(root);

	if (isOpen) {
		for (auto child : root.Transform.GetChildren()) {
			DisplayTree(child->GetGameObject());
		}

		if (!m_Selected.empty() && ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) 
			&& !ImGui::IsAnyItemHovered()) 
		{
			m_Selected.clear();
		}

		ImGui::TreePop();
	}
}

inline void reality::EditorHierarchy::Select(GameObject& root, bool isCurrent) {
	if (ImGui::IsItemClicked()) {
		if (ImGui::IsKeyDown(keycode::RE_KEY_LEFT_CONTROL)) {
			if (!isCurrent) {
				m_Selected.emplace_back(&root);
			}
			else {
				*std::find(m_Selected.begin(), m_Selected.end(), &root) = nullptr;
			}
		}
		else if (!isCurrent) {
			m_Selected.clear();
			m_Selected.emplace_back(&root);
		}
	}
}

inline void reality::EditorHierarchy::Drag(GameObject& hovered) {
	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload("Object_Hierarchy", &hovered, sizeof(&hovered));
		m_IsDragging = true;
		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget()) {
		if (ImGui::AcceptDragDropPayload("Object_Hierarchy")) {
			for (auto go : m_Selected) {
				go->SetParent(hovered);
			}
		}
		m_IsDragging = false;
		ImGui::EndDragDropTarget();
	}

	if (m_IsDragging && !m_Selected.empty() && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
		for (auto go : m_Selected) {
			go->Transform.SetParent(nullptr);
		}
		m_IsDragging = false;
	}
}