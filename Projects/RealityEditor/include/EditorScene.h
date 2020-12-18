// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/ImGuizmo.h>

#include "EditorCamera.h"
#include "Rendering/Opengl/GLPipeline.h"
#include "Rendering/Opengl/GLContext.h"
#include "Gameplay/GameObject.h"

namespace reality {
	class EditorScene {
	public:
		void Draw(GLPipeline& pipeline, EditorCamera& camera, Vector2& viewportSize, GameObject* object = {});

	private:
		ImGuizmo::OPERATION m_CurrentGuizmoOperation{ ImGuizmo::OPERATION::TRANSLATE };
		ImGuizmo::MODE m_CurrentGuizmoMode{ ImGuizmo::MODE::WORLD };

		void DrawGuizmo(ImVec2 windowPos, ImVec2 windowSize, EditorCamera& camera, GameObject& object);  
	};
}

inline void reality::EditorScene::Draw(GLPipeline& pipeline, EditorCamera& camera, Vector2& viewportSize, GameObject* object) {
	ImGui::Begin("Scene"); 
	{
		const auto windowPos{ ImGui::GetWindowPos() };
		const auto windowSize{ ImGui::GetWindowSize() };
		const Viewport viewport{ 0, 0, windowSize.x, windowSize.y };

		if ((std::memcmp(&pipeline.GetFinalPass().Viewport, &viewport, 16) != 0)) {
			camera.Projection = Matrix4::Perspective(viewport.Width / viewport.Height);
			GLContext::SetProjectionMatrix(camera.Projection);	
			pipeline.ResizePasses(viewport);
			viewportSize = { windowSize.x, windowSize.y };
		}

		ImGui::GetWindowDrawList()->AddImage(
			(ImTextureID)(uint64)pipeline.GetFinalPass().GetHandle().ColorAttachments[0].GetHandle().Id,
			windowPos, { windowSize.x + windowPos.x, windowSize.y + windowPos.y }, { 0, 1 }, { 1, 0 });

		if (object) {
			DrawGuizmo(windowPos, windowSize, camera, *object);
		}
	}
	ImGui::End();
}

inline void reality::EditorScene::DrawGuizmo(ImVec2 windowPos, ImVec2 windowSize, EditorCamera& camera, GameObject& object) {
	if (m_CurrentGuizmoOperation != ImGuizmo::SCALE) {
		if (ImGui::RadioButton("Local", m_CurrentGuizmoMode == ImGuizmo::LOCAL)) {
			m_CurrentGuizmoMode = ImGuizmo::LOCAL;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("World", m_CurrentGuizmoMode == ImGuizmo::WORLD)) {
			m_CurrentGuizmoMode = ImGuizmo::WORLD;
		}
	}
	if (ImGui::IsKeyPressed(keycode::RE_KEY_E)) {
		m_CurrentGuizmoOperation = ImGuizmo::TRANSLATE;
	}
	if (ImGui::IsKeyPressed(keycode::RE_KEY_R)) {
		m_CurrentGuizmoOperation = ImGuizmo::ROTATE;
	}
	if (ImGui::IsKeyPressed(keycode::RE_KEY_T)) {
		m_CurrentGuizmoOperation = ImGuizmo::SCALE;
	}
	if (ImGui::RadioButton("Translate", m_CurrentGuizmoOperation == ImGuizmo::TRANSLATE)) {
		m_CurrentGuizmoOperation = ImGuizmo::TRANSLATE;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", m_CurrentGuizmoOperation == ImGuizmo::ROTATE)) {
		m_CurrentGuizmoOperation = ImGuizmo::ROTATE;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", m_CurrentGuizmoOperation == ImGuizmo::SCALE)) {
		m_CurrentGuizmoOperation = ImGuizmo::SCALE;
	}
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(windowPos.x, windowPos.y, windowSize.x, windowSize.y);

	auto trs{ object.Transform.GetTrs() };
	ImGuizmo::Manipulate(camera.GetViewMatrix().Array, camera.Projection.Array, m_CurrentGuizmoOperation, 
		m_CurrentGuizmoMode, trs.Array);

	object.Transform.SetPosition(Matrix4::GetTranslation(trs));
	object.Transform.SetScale(Matrix4::GetScale(trs));
}