// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>

#include "EditorWindow.h"
#include "EditorTheme.h"
#include "Core/Tools/Logger.h"

namespace Reality::Editor {
	class EditorMenu : public EditorWindow {
	public:
		void Draw() const;
	};
}

inline void Reality::Editor::EditorMenu::Draw() const {
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
				RE_LOG_INFO("New Scene");
			}
			if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {
				RE_LOG_INFO("Open Scene");
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				RE_LOG_INFO("Save");
			}
			if (ImGui::MenuItem("Save As..", "Ctrl+Shift+S")) {
				RE_LOG_INFO("Save As...");
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", "Alt+F4")) {
				RE_LOG_INFO("Exit");
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {
			if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
				RE_LOG_INFO("Undo");
			}
			if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
				RE_LOG_INFO("Redo");
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Select All", "Ctrl+A")) {
				RE_LOG_INFO("Select All");
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "Ctrl+X")) {
				RE_LOG_INFO("Cut");
			}
			if (ImGui::MenuItem("Copy", "Ctrl+C")) {
				RE_LOG_INFO("Copy");
			}
			if (ImGui::MenuItem("Paste", "Ctrl+V")) {
				RE_LOG_INFO("Paste");
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window")) {
			if (ImGui::BeginMenu("Style")) {
				if (ImGui::MenuItem("Classic")) {
					ImGui::StyleColorsClassic();
					RE_LOG_INFO("StyleColorsClassic");
				}
				if (ImGui::MenuItem("Dark")) {
					ImGui::StyleColorsDark();
					RE_LOG_INFO("StyleColorsDark");
				}
				if (ImGui::MenuItem("Light")) {
					ImGui::StyleColorsLight();
					RE_LOG_INFO("StyleColorsLight");
				}
				if (ImGui::MenuItem("Reality")) {
					EditorTheme::RealityStyle();
					RE_LOG_INFO("StyleColorsReality");
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}