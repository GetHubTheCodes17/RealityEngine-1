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
		Vector3 m_SnapTranslation, m_SnapScale, m_CurrentSnap;
		float m_SnapAngle{ 15.f };
		bool m_UseSnap{};

		void DrawGuizmo(ImVec2 windowPos, ImVec2 windowSize, EditorCamera& camera, GameObject& object);  
		void UpdateGizmoMode();
		void UpdateSnap();
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
	UpdateGizmoMode();
	UpdateSnap();

	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(windowPos.x, windowPos.y, windowSize.x, windowSize.y);

	Matrix4 trs{ object.Transform.GetTrs() }, deltaMatrix;

	ImGuizmo::Manipulate(camera.GetViewMatrix().Array, camera.Projection.Array, m_CurrentGuizmoOperation, 
		m_CurrentGuizmoMode, trs.Array, deltaMatrix.Array, m_UseSnap ? &m_CurrentSnap.X : nullptr);

	if (!ImGuizmo::IsUsing()) {
		return;
	}

	if (m_CurrentGuizmoOperation == ImGuizmo::TRANSLATE) {
		object.Transform.Translate(deltaMatrix.GetRow3(3));
	}
	else if (m_CurrentGuizmoOperation == ImGuizmo::ROTATE) {
		object.Transform.Rotate(-Quaternion{ deltaMatrix }.GetEulerAngles());
	}
	else if (m_CurrentGuizmoOperation == ImGuizmo::SCALE) {
		object.Transform.SetScale(Matrix4::GetScale(trs));
	}
}

inline void reality::EditorScene::UpdateGizmoMode() {
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
}

inline void reality::EditorScene::UpdateSnap() {
	ImGui::Checkbox("Snap", &m_UseSnap);
	ImGui::SameLine();

	switch (m_CurrentGuizmoOperation) {
	case ImGuizmo::TRANSLATE:
		ImGui::InputFloat3("Translation Snap", &m_SnapTranslation.X);
		m_CurrentSnap = m_SnapTranslation;
		break;
	case ImGuizmo::ROTATE:
		ImGui::InputFloat("Angle Snap", &m_SnapAngle);
		m_CurrentSnap = Vector3{ m_SnapAngle };
		break;
	case ImGuizmo::SCALE:
		ImGui::InputFloat("Scale Snap", &m_SnapScale.X);
		m_CurrentSnap = m_SnapScale;
		break;
	}
}