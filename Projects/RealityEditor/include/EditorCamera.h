// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Windowing/IO.h"
#include "Gameplay/GameObject.h"

namespace reality {
	class EditorCamera {
	public:
		Matrix4 Model, Projection{ Matrix4::Perspective((float)RE_WINDOW_WIDTH / (float)RE_WINDOW_HEIGHT) };
		Vector3 Position;
		float MovementSpeed{ 5.f }, RotationSpeed{ 4.f }, FocusSpeed{ 5.f };

		void Update();
		void UpdateFocus();
		void Focus(const GameObject* target);
		const Matrix4& GetViewMatrix() const;

	private:
		Matrix4 m_View{ Matrix4::LookAt(Vector3::Zero, Vector3::Forward) };
		Vector3 m_Euler, m_FocusDestination;
		const GameObject* m_Target{};
		float m_OldMovementMagnitude{};

		void HandleKeys();
		void UpdateModelView();
	};
}

inline void reality::EditorCamera::Update() {
	HandleKeys();

	auto relativeMousePos{ g_Io->Input->GetRelativeMousePos() };
	const auto magnitude{ relativeMousePos.GetSqrMagnitude() };

	// The glfw library causes lags when GLFW_CURSOR_DISABLED is set
	if (magnitude > m_OldMovementMagnitude * 5.f) {
		relativeMousePos.Set(0.f);
	}
	else if (magnitude != 0.f) {
		m_Euler = { m_Euler.X + relativeMousePos.Y * g_Io->Time->GetDeltaTime() * RotationSpeed,
			m_Euler.Y + relativeMousePos.X * g_Io->Time->GetDeltaTime() * RotationSpeed };
	}
	m_OldMovementMagnitude = magnitude;

	UpdateModelView();
}

inline void reality::EditorCamera::UpdateFocus() {
	if (m_Target) {
		Position = Vector3::Lerp(Position, m_FocusDestination, g_Io->Time->GetDeltaTime() * FocusSpeed);

		if (Vector3::Distance(Position, m_FocusDestination) < 0.01f) {
			m_Target = nullptr;
		}
		UpdateModelView();
	}
}

inline void reality::EditorCamera::Focus(const GameObject* target) {
	m_Target = target;
	if (m_Target) {
		m_FocusDestination = target->Transform.GetTrs().GetRow3(3) - Model.GetRow3(2) * 3.f;
	}
}

inline const reality::Matrix4& reality::EditorCamera::GetViewMatrix() const {
	return m_View;
}

inline void reality::EditorCamera::HandleKeys() {
	const auto deltaTime{ g_Io->Time->GetDeltaTime() };

	if (ImGui::IsKeyDown(keycode::RE_KEY_W)) {
		Position += Model.GetRow3(2) * deltaTime * MovementSpeed;
		m_Target = nullptr;
	}
	if (ImGui::IsKeyDown(keycode::RE_KEY_S)) {
		Position -= Model.GetRow3(2) * deltaTime * MovementSpeed;
		m_Target = nullptr;
	}
	if (ImGui::IsKeyDown(keycode::RE_KEY_D)) {
		Position -= Model.GetRow3(0) * deltaTime * MovementSpeed;
		m_Target = nullptr;
	}
	if (ImGui::IsKeyDown(keycode::RE_KEY_A)) {
		Position += Model.GetRow3(0) * deltaTime * MovementSpeed;
		m_Target = nullptr;
	}
	if (ImGui::IsKeyDown(keycode::RE_KEY_E)) {
		Position += Vector3::Up * deltaTime * MovementSpeed;
		m_Target = nullptr;
	}
	if (ImGui::IsKeyDown(keycode::RE_KEY_Q)) {
		Position -= Vector3::Up * deltaTime * MovementSpeed;
		m_Target = nullptr;
	}
}

inline void reality::EditorCamera::UpdateModelView() {
	Model = (Quaternion{ Mathf::Deg2Rad * m_Euler.X, Vector3::Left } 
	* Quaternion{ Mathf::Deg2Rad * m_Euler.Y, Vector3::Up }).GetMatrix() * Matrix4::Translate(Position);

	m_View = Matrix4::LookAt(Position, Position + Model.GetRow3(2), Model.GetRow3(1));
}