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
		bool IsHovered() const;


	private:
		ImGuizmo::OPERATION m_CurrentGuizmoOperation{ ImGuizmo::OPERATION::TRANSLATE };
		ImGuizmo::MODE m_CurrentGuizmoMode{ ImGuizmo::MODE::WORLD };
		Vector3 m_SnapTranslation, m_SnapScale, m_CurrentSnap;
		ImVec2 m_WindowPos, m_WindowSize;
		float m_SnapAngle{ 15.f };
		bool m_UseSnap{};
		bool m_IsHovered{};

		void DrawGuizmo(EditorCamera& camera, GameObject& object);  
		void UpdateGizmoMode();
		void UpdateSnap();
	};
}

inline void reality::EditorScene::Draw(GLPipeline& pipeline, EditorCamera& camera, Vector2& viewportSize, GameObject* object) {
	ImGui::Begin("Scene"); 
	{
		m_IsHovered = ImGui::IsWindowHovered();

		m_WindowPos = ImGui::GetWindowPos();
		m_WindowSize = ImGui::GetWindowSize();
		const Viewport viewport{ 0, 0, m_WindowSize.x, m_WindowSize.y };

		if ((std::memcmp(&pipeline.GetFinalPass().Viewport, &viewport, 16) != 0)) {
			camera.Projection = Matrix4::Perspective(viewport.Width / viewport.Height);
			GLContext::SetProjectionMatrix(camera.Projection);	
			pipeline.ResizePasses(viewport);
			viewportSize = { m_WindowSize.x, m_WindowSize.y };
		}

		ImGui::GetWindowDrawList()->AddImage(
			(ImTextureID)(uint64)pipeline.GetFinalPass().GetHandle().ColorAttachments[0].GetHandle().Id,
			m_WindowPos, { m_WindowSize.x + m_WindowPos.x, m_WindowSize.y + m_WindowPos.y }, { 0, 1 }, { 1, 0 });

		if (object) {
			DrawGuizmo(camera, *object);
		}
	}
	ImGui::End();
}

inline bool reality::EditorScene::IsHovered() const {
	return m_IsHovered;
}

inline void reality::EditorScene::DrawGuizmo(EditorCamera& camera, GameObject& object) {
	UpdateGizmoMode();
	UpdateSnap();

	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(m_WindowPos.x, m_WindowPos.y, m_WindowSize.x, m_WindowSize.y);

	Matrix4 world{ object.Transform.GetTrs() }, deltaMatrix;
	Matrix4 local{ Matrix4::Scale(object.Transform.GetScale()) * object.Transform.GetRotation().GetMatrix() *
			Matrix4::Translate(object.Transform.GetPosition()) };

	ImGuizmo::Manipulate(camera.GetViewMatrix().Array, camera.Projection.Array, m_CurrentGuizmoOperation, 
		m_CurrentGuizmoMode, world.Array, deltaMatrix.Array, m_UseSnap ? &m_CurrentSnap.X : nullptr);

	if (!ImGuizmo::IsUsing()) {
		return;
	}

	if (m_CurrentGuizmoOperation == ImGuizmo::TRANSLATE) {
		object.Transform.SetPosition((world * Matrix4::Inverse(object.Transform.GetTrs()) * local).GetRow3(3));
	}
	else if (m_CurrentGuizmoOperation == ImGuizmo::ROTATE) {
		object.Transform.Rotate(-Quaternion{ deltaMatrix }.GetEulerAngles()); // TODO : FIX for children and try to remove deltaMatrix
	}
	else if (m_CurrentGuizmoOperation == ImGuizmo::SCALE) {
		object.Transform.SetScale(Matrix4::GetScale(world * Matrix4::Inverse(object.Transform.GetTrs()) * local));
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