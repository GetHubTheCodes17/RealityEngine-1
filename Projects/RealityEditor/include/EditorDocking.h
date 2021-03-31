// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui_internal.h>
#include <imgui/imgui.h>

namespace Reality::Editor {
	class EditorDocking {
	public:
		void Begin();
		void End() const;

	private:
		ImGuiID m_DockspaceId{};
	};
}

inline void Reality::Editor::EditorDocking::Begin() {
	if (!m_DockspaceId) {
		m_DockspaceId = ImGui::GetID("DockSpace");
		ImGui::DockBuilderRemoveNode(m_DockspaceId);
		ImGui::DockBuilderAddNode(m_DockspaceId, ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui::DockBuilderSetNodeSize(m_DockspaceId, ImGui::GetWindowSize());
		auto mainId{ m_DockspaceId };
		ImGui::DockBuilderDockWindow("Hierarchy", ImGui::DockBuilderSplitNode(mainId, ImGuiDir_Left, 0.2f, nullptr, &mainId));
		ImGui::DockBuilderDockWindow("Inspector", ImGui::DockBuilderSplitNode(mainId, ImGuiDir_Right, 0.25f, nullptr, &mainId));
		const auto logId{ ImGui::DockBuilderSplitNode(mainId, ImGuiDir_Down, 0.3f, nullptr, &mainId) };
		ImGui::DockBuilderDockWindow("Console", logId);
		ImGui::DockBuilderDockWindow("Assets", logId);
		ImGui::DockBuilderDockWindow("Scene", ImGui::DockBuilderSplitNode(mainId, ImGuiDir_Up, 1.f, nullptr, &mainId));
		ImGui::DockBuilderFinish(m_DockspaceId);
	}

	const auto mainViewport{ ImGui::GetMainViewport() };
	ImGui::SetNextWindowPos(mainViewport->Pos);
	ImGui::SetNextWindowSize(mainViewport->Size);
	ImGui::SetNextWindowViewport(mainViewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.f, 0.f });
	ImGui::Begin("RealityEngine", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
		| ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNavFocus
		| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground);
	ImGui::PopStyleVar();
	ImGui::DockSpace(m_DockspaceId);
}

inline void Reality::Editor::EditorDocking::End() const {
	ImGui::End();
}