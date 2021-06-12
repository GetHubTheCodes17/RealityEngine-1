// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>
#include <vector>
#include <span>

#include "EditorWindow.h"
#include "Gameplay/Scene.h"
#include "Gameplay/GameObject.h"
#include "Windowing/Key.h"

namespace Reality::Editor {
	class EditorHierarchy : public EditorWindow {
	public:
		void Draw();
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

inline void Reality::Editor::EditorHierarchy::Draw() {
	auto& scene{ *g_SceneManager->ActiveScene };

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

inline std::span<Reality::GameObject*> Reality::Editor::EditorHierarchy::GetSelected() {
	return m_Selected;
}

inline void Reality::Editor::EditorHierarchy::HandleShortcuts(Scene& scene) {
	if (!m_Selected.empty() && ImGui::IsKeyPressed((int)Key::Delete)) {
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

	if (ImGui::IsKeyDown((int)Key::LeftControl)) {
		if (ImGui::IsKeyPressed((int)Key::D)) {
			for (auto go : m_Selected) {
				scene.CreateGameObject(*go);
			}
		}
		else if (ImGui::IsKeyPressed((int)Key::Q)) {
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

inline void Reality::Editor::EditorHierarchy::DisplayTree(GameObject& root) {
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

inline void Reality::Editor::EditorHierarchy::Select(GameObject& root, bool isCurrent) {
	if (ImGui::IsItemClicked()) {
		if (ImGui::IsKeyDown((int)Key::LeftControl)) {
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

inline void Reality::Editor::EditorHierarchy::Drag(GameObject& hovered) {
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