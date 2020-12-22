// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>

namespace reality {
	class EditorAssets {
	public:
		void Draw();
	};
}

inline void reality::EditorAssets::Draw() {
	ImGui::Begin("Assets");
	{

	}
	ImGui::End();
}