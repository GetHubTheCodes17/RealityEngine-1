// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>

#include "Gameplay/Scene.h"
#include "Windowing/KeyCodes.h"

namespace reality {
	class EditorHierarchy {
	public:
		GameObject* Current{};

		void Draw(Scene& scene);

	private:
		void DisplayTree(GameObject& root);
	};
}

inline void reality::EditorHierarchy::Draw(Scene& scene) {
	ImGui::Begin("Hierarchy");
	{
		if (Current && ImGui::IsKeyPressed(keycode::RE_KEY_DELETE)) {
			scene.DestroyGameObject(*Current);
			Current = nullptr;
		}

		if (ImGui::Button("Create Empty")) {
			auto& object{ scene.CreateGameObject("GameObject") };
			if (Current) {
				object.SetParent(*Current);
			}
		}

		for (auto root : scene.GetRootsGameObjects()) {
			DisplayTree(*root);
		}
	}
	ImGui::End();
}

inline void reality::EditorHierarchy::DisplayTree(GameObject& root) {
	const auto flags{ ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen |
		ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanFullWidth | (!root.Transform.GetChildrenSize() ? ImGuiTreeNodeFlags_Leaf : 0) |
		(Current == &root ? ImGuiTreeNodeFlags_Selected : 0) };

	const auto isOpen{ ImGui::TreeNodeEx(root.Name.c_str(), flags) };
	const auto current{ &root };

	if (ImGui::IsItemClicked() || ImGui::IsItemFocused()) {
		Current = &root;
	}

	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload("Object_Hierarchy", &root, sizeof(&root));
		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget()) {
		if (ImGui::AcceptDragDropPayload("Object_Hierarchy")) {
			if (Current) {
				Current->SetParent(*current);
			}
		}
		ImGui::EndDragDropTarget();
	}

	if (isOpen) {
		for (auto child : root.Transform.GetChildren()) {
			DisplayTree(child->GetGameObject());
		}

		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered()) {
			Current = nullptr;
		}

		ImGui::TreePop();
	}
}