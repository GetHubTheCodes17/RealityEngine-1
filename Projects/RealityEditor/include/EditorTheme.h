// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>

namespace reality::editorTheme {
	void RealityStyle();
}

inline void reality::editorTheme::RealityStyle() {
	auto colors{ ImGui::GetStyle().Colors };
	colors[ImGuiCol_Text] = { 1.00f, 1.00f, 1.00f, 1.00f };
	colors[ImGuiCol_TextDisabled] = { 0.50f, 0.50f, 0.50f, 1.00f };
	colors[ImGuiCol_WindowBg] = { 0.06f, 0.06f, 0.06f, 0.94f };
	colors[ImGuiCol_ChildBg] = { 1.00f, 1.00f, 1.00f, 0.00f };
	colors[ImGuiCol_PopupBg] = { 0.08f, 0.08f, 0.08f, 0.94f };
	colors[ImGuiCol_Border] = { 0.43f, 0.43f, 0.50f, 0.50f };
	colors[ImGuiCol_BorderShadow] = { 0.00f, 0.00f, 0.00f, 0.00f };
	colors[ImGuiCol_FrameBg] = { 0.20f, 0.21f, 0.22f, 0.54f };
	colors[ImGuiCol_FrameBgHovered] = { 0.40f, 0.40f, 0.40f, 0.40f };
	colors[ImGuiCol_FrameBgActive] = { 0.18f, 0.18f, 0.18f, 0.67f };
	colors[ImGuiCol_TitleBg] = { 0.04f, 0.04f, 0.04f, 1.00f };
	colors[ImGuiCol_TitleBgActive] = { 0.29f, 0.29f, 0.29f, 1.00f };
	colors[ImGuiCol_TitleBgCollapsed] = { 0.00f, 0.00f, 0.00f, 0.51f };
	colors[ImGuiCol_MenuBarBg] = { 0.14f, 0.14f, 0.14f, 1.00f };
	colors[ImGuiCol_ScrollbarBg] = { 0.02f, 0.02f, 0.02f, 0.53f };
	colors[ImGuiCol_ScrollbarGrab] = { 0.31f, 0.31f, 0.31f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabHovered] = { 0.41f, 0.41f, 0.41f, 1.00f };
	colors[ImGuiCol_ScrollbarGrabActive] = { 0.51f, 0.51f, 0.51f, 1.00f };
	colors[ImGuiCol_CheckMark] = { 0.94f, 0.94f, 0.94f, 1.00f };
	colors[ImGuiCol_SliderGrab] = { 0.51f, 0.51f, 0.51f, 1.00f };
	colors[ImGuiCol_SliderGrabActive] = { 0.86f, 0.86f, 0.86f, 1.00f };
	colors[ImGuiCol_Button] = { 0.44f, 0.44f, 0.44f, 0.40f };
	colors[ImGuiCol_ButtonHovered] = { 0.46f, 0.47f, 0.48f, 1.00f };
	colors[ImGuiCol_ButtonActive] = { 0.42f, 0.42f, 0.42f, 1.00f };
	colors[ImGuiCol_Header] = { 0.70f, 0.70f, 0.70f, 0.31f };
	colors[ImGuiCol_HeaderHovered] = { 0.70f, 0.70f, 0.70f, 0.80f };
	colors[ImGuiCol_HeaderActive] = { 0.48f, 0.50f, 0.52f, 1.00f };
	colors[ImGuiCol_Separator] = { 0.43f, 0.43f, 0.50f, 0.50f };
	colors[ImGuiCol_SeparatorHovered] = { 0.72f, 0.72f, 0.72f, 0.78f };
	colors[ImGuiCol_SeparatorActive] = { 0.51f, 0.51f, 0.51f, 1.00f };
	colors[ImGuiCol_ResizeGrip] = { 0.91f, 0.91f, 0.91f, 0.25f };
	colors[ImGuiCol_ResizeGripHovered] = { 0.81f, 0.81f, 0.81f, 0.67f };
	colors[ImGuiCol_ResizeGripActive] = { 0.46f, 0.46f, 0.46f, 0.95f };
	colors[ImGuiCol_PlotLines] = { 0.61f, 0.61f, 0.61f, 1.00f };
	colors[ImGuiCol_PlotLinesHovered] = { 1.00f, 0.43f, 0.35f, 1.00f };
	colors[ImGuiCol_PlotHistogram] = { 0.73f, 0.60f, 0.15f, 1.00f };
	colors[ImGuiCol_PlotHistogramHovered] = { 1.00f, 0.60f, 0.00f, 1.00f };
	colors[ImGuiCol_TextSelectedBg] = { 0.87f, 0.87f, 0.87f, 0.35f };
	colors[ImGuiCol_ModalWindowDarkening] = { 0.80f, 0.80f, 0.80f, 0.35f };
	colors[ImGuiCol_DragDropTarget] = { 1.00f, 1.00f, 0.00f, 0.90f };
	colors[ImGuiCol_NavHighlight] = { 0.60f, 0.60f, 0.60f, 1.00f };
	colors[ImGuiCol_NavWindowingHighlight] = { 1.00f, 1.00f, 1.00f, 0.70f };
}