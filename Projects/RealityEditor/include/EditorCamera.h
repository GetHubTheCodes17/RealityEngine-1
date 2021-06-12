// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "EditorWindow.h"
#include "Windowing/IO.h"
#include "Gameplay/GameObject.h"
#include "Core/Maths/Quaternion.h"
#include "Core/Maths/Matrix4.h"
#include "Core/Maths/Vector3.h"

namespace Reality::Editor {
	class EditorCamera : public EditorWindow {
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

inline void Reality::Editor::EditorCamera::Update() {
	HandleKeys();

	auto relativeMousePos{ g_Io->Input->GetRelativeMousePos() };
	const auto magnitude{ relativeMousePos.GetSqrMagnitude() };

	// The glfw library causes lags when GLFW_CURSOR_DISABLED is activated
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

inline void Reality::Editor::EditorCamera::UpdateFocus() {
	if (m_Target) {
		Position = Vector3::Lerp(Position, m_FocusDestination, g_Io->Time->GetDeltaTime() * FocusSpeed);

		if (Vector3::Distance(Position, m_FocusDestination) < 0.01f) {
			m_Target = nullptr;
		}
		UpdateModelView();
	}
}

inline void Reality::Editor::EditorCamera::Focus(const GameObject* target) {
	m_Target = target;
	if (m_Target) {
		m_FocusDestination = target->Transform.GetTrs().GetRow3(3) - Model.GetRow3(2) * 3.f;
	}
}

inline const Reality::Matrix4& Reality::Editor::EditorCamera::GetViewMatrix() const {
	return m_View;
}

inline void Reality::Editor::EditorCamera::HandleKeys() {
	const auto moveForward{ ImGui::IsKeyDown((int)Key::W) }, moveBackward{ ImGui::IsKeyDown((int)Key::S) };
	const auto moveRight{ ImGui::IsKeyDown((int)Key::D) }, moveLeft{ ImGui::IsKeyDown((int)Key::A) };
	const auto moveUp{ ImGui::IsKeyDown((int)Key::E) }, moveDown{ ImGui::IsKeyDown((int)Key::Q) };

	auto Move{ 
		[this](const auto& translation) {
			Position += translation * g_Io->Time->GetDeltaTime() * MovementSpeed;
			m_Target = nullptr;
		} 
	};

	if (moveForward) {
		Move(Model.GetRow3(2));
	}
	if (moveBackward) {
		Move(-Model.GetRow3(2));
	}
	if (moveRight) {
		Move(-Model.GetRow3(0));
	}
	if (moveLeft) {
		Move(Model.GetRow3(0));
	}
	if (moveUp) {
		Move(Vector3::Up);
	}
	if (moveDown) {
		Move(Vector3::Down);
	}
}

inline void Reality::Editor::EditorCamera::UpdateModelView() {
	Model = (Quaternion{ Mathf::Deg2Rad * m_Euler.X, Vector3::Left }
		*Quaternion{ Mathf::Deg2Rad * m_Euler.Y, Vector3::Up }).GetMatrix() * Matrix4::Translate(Position);

	m_View = Matrix4::LookAt(Position, Position + Model.GetRow3(2), Model.GetRow3(1));
}