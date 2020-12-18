// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>

#include "Core/Maths/Vector3.h"

namespace reality::editorTheme {
	void StyleColorCyan();
}

inline void reality::editorTheme::StyleColorCyan() {
	auto& style{ ImGui::GetStyle() };

	const Vector3 colorText{ 236.f / 255.f, 240.f / 255.f, 241.f / 255.f };
	const Vector3 colorHead{ 41.f / 255.f, 128.f / 255.f, 185.f / 255.f };
	const Vector3 colorArea{ 57.f / 255.f, 79.f / 255.f, 105.f / 255.f };
	const Vector3 colorBody{ 44.f / 255.f, 62.f / 255.f, 80.f / 255.f };
	const Vector3 colorPops{ 33.f / 255.f, 46.f / 255.f, 60.f / 255.f };

	style.Colors[ImGuiCol_Text] = { colorText.X, colorText.Y, colorText.Z, 1.f };
	style.Colors[ImGuiCol_TextDisabled] = { colorText.X, colorText.Y, colorText.Z, 0.58f };
	style.Colors[ImGuiCol_WindowBg] = { colorBody.X, colorBody.Y, colorBody.Z, 0.95f };
	style.Colors[ImGuiCol_Border] = { colorBody.X, colorBody.Y, colorBody.Z, 0.f };
	style.Colors[ImGuiCol_BorderShadow] = { colorBody.X, colorBody.Y, colorBody.Z, 0.f };
	style.Colors[ImGuiCol_FrameBg] = { colorArea.X, colorArea.Y, colorArea.Z, 1.f };
	style.Colors[ImGuiCol_FrameBgHovered] = { colorHead.X, colorHead.Y, colorHead.Z, 0.78f };
	style.Colors[ImGuiCol_FrameBgActive] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_TitleBg] = { colorArea.X, colorArea.Y, colorArea.Z, 1.f };
	style.Colors[ImGuiCol_TitleBgCollapsed] = { colorArea.X, colorArea.Y, colorArea.Z, 0.75f };
	style.Colors[ImGuiCol_TitleBgActive] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_MenuBarBg] = { colorArea.X, colorArea.Y, colorArea.Z, 0.47f };
	style.Colors[ImGuiCol_ScrollbarBg] = { colorArea.X, colorArea.Y, colorArea.Z, 1.f };
	style.Colors[ImGuiCol_ScrollbarGrab] = { colorHead.X, colorHead.Y, colorHead.Z, 0.21f };
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = { colorHead.X, colorHead.Y, colorHead.Z, 0.78f };
	style.Colors[ImGuiCol_ScrollbarGrabActive] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_CheckMark] = { colorHead.X, colorHead.Y, colorHead.Z, 0.8f };
	style.Colors[ImGuiCol_SliderGrab] = { colorHead.X, colorHead.Y, colorHead.Z, 0.5f };
	style.Colors[ImGuiCol_SliderGrabActive] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_Button] = { colorHead.X, colorHead.Y, colorHead.Z, 0.5f };
	style.Colors[ImGuiCol_ButtonHovered] = { colorHead.X, colorHead.Y, colorHead.Z, 0.86f };
	style.Colors[ImGuiCol_ButtonActive] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_Header] = { colorHead.X, colorHead.Y, colorHead.Z, 0.76f };
	style.Colors[ImGuiCol_HeaderHovered] = { colorHead.X, colorHead.Y, colorHead.Z, 0.86f };
	style.Colors[ImGuiCol_HeaderActive] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_ResizeGrip] = { colorHead.X, colorHead.Y, colorHead.Z, 0.15f };
	style.Colors[ImGuiCol_ResizeGripHovered] = { colorHead.X, colorHead.Y, colorHead.Z, 0.78f };
	style.Colors[ImGuiCol_ResizeGripActive] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_PlotLines] = { colorText.X, colorText.Y, colorText.Z, 0.63f };
	style.Colors[ImGuiCol_PlotLinesHovered] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_PlotHistogram] = { colorText.X, colorText.Y, colorText.Z, 0.63f };
	style.Colors[ImGuiCol_PlotHistogramHovered] = { colorHead.X, colorHead.Y, colorHead.Z, 1.f };
	style.Colors[ImGuiCol_TextSelectedBg] = { colorHead.X, colorHead.Y, colorHead.Z, 0.43f };
	style.Colors[ImGuiCol_PopupBg] = { colorPops.X, colorPops.Y, colorPops.Z, 0.92f };
	style.Colors[ImGuiCol_ModalWindowDarkening] = { colorArea.X, colorArea.Y, colorArea.Z, 0.73f };
}