// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>

#include "Gameplay/Scene.h"

namespace reality {
	class EditorHierarchy {
	public:
		GameObject* Current{};

		void Draw(const Scene* scene);

	private:
		void DisplayTree(GameObject* root);
	};
}

inline void reality::EditorHierarchy::Draw(const Scene* scene) {
	ImGui::Begin("Hierarchy");
	{
		if (scene) {
			for (auto& root : scene->GetRootsGameObjects()) {
				DisplayTree(root);
			}
		}
	}
	ImGui::End();
}

inline void reality::EditorHierarchy::DisplayTree(GameObject* root) {
	const auto flags{ ImGuiTreeNodeFlags_FramePadding |
		ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanFullWidth | (!root->Transform.GetChildrenSize() ? ImGuiTreeNodeFlags_Leaf : 0) |
		(Current == root ? ImGuiTreeNodeFlags_Selected : 0) };

	const auto isOpen{ ImGui::TreeNodeEx(root->Name.c_str(), flags) };

	if (ImGui::IsItemClicked()) {
		Current = root;
	}

	if (isOpen) {
		for (auto& child : root->Transform.GetChildren()) {
			DisplayTree(&child->GetGameObject());
		}

		// Unselect
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered()) {
			Current = nullptr;
		}

		ImGui::TreePop();
	}
}