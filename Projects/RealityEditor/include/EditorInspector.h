// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>

#include "Gameplay/GameObject.h"

namespace reality {
	class EditorInspector {
	public:
		void Draw(GameObject* object);

	private:
		void DrawComponents(GameObject& object);
		void DrawName(GameObject& object);
		void DrawTransform(GameObject& object);
	};
}

inline void reality::EditorInspector::Draw(GameObject* object) {
	ImGui::Begin("Inspector");
	{
		if (object) {
			DrawName(*object);
			DrawTransform(*object);
			DrawComponents(*object);
		}
	}
	ImGui::End();
}

inline void reality::EditorInspector::DrawComponents(GameObject& object) {
	for (auto& comp : object.GetAllComponents()) {
		
	}
}

inline void reality::EditorInspector::DrawName(GameObject& object) {
	ImGui::Checkbox("##label", &object.IsActive);

	char buf[128];
	std::memset(buf, 0, sizeof(buf));
	strcpy_s(buf, sizeof(buf), object.Name.c_str());

	ImGui::SameLine();
	if (ImGui::InputText("Name", buf, sizeof(buf))) {
		object.Name = buf;
	}
}

inline void reality::EditorInspector::DrawTransform(GameObject& object) {
	auto& transform{ object.Transform };
	auto p{ transform.GetPosition() }, r{ transform.GetRotation().GetEulerAngles() }, s{ transform.GetScale() };
	if (ImGui::DragFloat3("Position", &p.X, .02f)) {
		transform.SetPosition(p);
	}
	if (ImGui::DragFloat3("Rotation", &r.X, .5f)) {
		transform.SetRotation(r);
	}
	if (ImGui::DragFloat3("Scale", &s.X, .005f)) {
		transform.SetScale(s);
	}
}