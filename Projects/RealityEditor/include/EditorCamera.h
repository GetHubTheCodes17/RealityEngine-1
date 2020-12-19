// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Windowing/IO.h"
#include "Core/Maths/Quaternion.h"

namespace reality {
	class EditorCamera {
	public:
		Matrix4 Projection{ Matrix4::Perspective((float)RE_WINDOW_WIDTH / (float)RE_WINDOW_HEIGHT) };
		Matrix4 Model;
		Vector3 Position;
		float MovementSpeed{ 5.f }, RotationSpeed{ 4.f };

		void Update();
		const Matrix4& GetViewMatrix() const;

	private:
		Matrix4 m_View{ Matrix4::LookAt(Vector3::Zero, Vector3::Forward) };
		Vector3 m_Euler;
	};
}

inline void reality::EditorCamera::Update() {
	const auto deltaTime{ g_Io->Time->GetDeltaTime() };

	if ( g_Io->Input->GetKeyDown(keycode::RE_KEY_W)) {
		Position += Model.GetRow3(2) * deltaTime * MovementSpeed;
	}
	if ( g_Io->Input->GetKeyDown(keycode::RE_KEY_S)) {
		Position -= Model.GetRow3(2) * deltaTime * MovementSpeed;
	}
	if ( g_Io->Input->GetKeyDown(keycode::RE_KEY_D)) {
		Position -= Model.GetRow3(0) * deltaTime * MovementSpeed;
	}
	if ( g_Io->Input->GetKeyDown(keycode::RE_KEY_A)) {
		Position += Model.GetRow3(0) * deltaTime * MovementSpeed;
	}
	if ( g_Io->Input->GetKeyDown(keycode::RE_KEY_SPACE)) {
		Position += Vector3::Up * deltaTime * MovementSpeed;
	}
	if ( g_Io->Input->GetKeyDown(keycode::RE_KEY_LEFT_CONTROL)) {
		Position -= Vector3::Up * deltaTime * MovementSpeed;
	}

	m_Euler = { m_Euler.X +  g_Io->Input->GetRelativeMousePos().Y * deltaTime * RotationSpeed,
		m_Euler.Y +  g_Io->Input->GetRelativeMousePos().X * deltaTime * RotationSpeed };

	Model = (Quaternion{ Mathf::Deg2Rad * m_Euler.X, Vector3::Left }
		* Quaternion{ Mathf::Deg2Rad * m_Euler.Y, Vector3::Up }).GetMatrix() * Matrix4::Translate(Position);

	m_View = Matrix4::LookAt(Position, Position + Model.GetRow3(2), Model.GetRow3(1));
}

inline const reality::Matrix4& reality::EditorCamera::GetViewMatrix() const {
	return m_View;
}