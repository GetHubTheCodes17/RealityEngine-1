// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"
#include "Core/Maths/Matrix4.h"

namespace reality {
	struct CCamera : CBehaviour {
		RE_COMPONENT(CCamera, CBehaviour)
		enum class Projection { Perspective, Orthographic };
		enum class Clear { Skybox, SolidColor, DepthOnly, DontClear };

		inline static CCamera* s_Main{};

		int Depth{};
		float Fov{ 60.f }, Near{ 0.003f }, Far{ 1000.f }, OrthoSize{ 10.f };
		Clear Flag{ Clear::Skybox };
		Projection ProjectionType{ Projection::Perspective };
		Matrix4 Projection{ Matrix4::Perspective((float)RE_WINDOW_WIDTH / (float)RE_WINDOW_HEIGHT, Near, Far, Fov) };
		Matrix4 View{ Matrix4::LookAt(Vector3::Zero, Vector3::Forward) };
	};
}