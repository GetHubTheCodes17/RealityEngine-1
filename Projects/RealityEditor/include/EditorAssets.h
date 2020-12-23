// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>
#include <filesystem>

#include "Resources/ResourceLocator.h"

namespace reality {
	class EditorAssets {
	public:
		void Draw();

		void DropResource(std::string_view path);

	private:
		bool m_IsDropping{};
	};
}

inline void reality::EditorAssets::Draw() {
	ImGui::Begin("Assets");
	{

	}
	ImGui::End();
}

inline void reality::EditorAssets::DropResource(std::string_view filename) {
	if (std::filesystem::path path{ filename }; Model::IsExtensionSupported(path.extension().string())) {
		auto parent{ path.parent_path().stem().string() }, child{ path.filename().string() };
		g_ModelManager->Load(path.stem().string().c_str(), { "Models/" + parent + '/' + child });
	}
}