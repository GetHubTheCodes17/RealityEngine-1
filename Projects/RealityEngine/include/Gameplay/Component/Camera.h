// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/cereal.hpp>

#include "Core/Platform.h"
#include "Core/Maths/MathsSerializer.h"
#include "Component.h"

namespace Reality {
	struct CCamera : Component {
		RE_COMPONENT(CCamera, Component)
		enum class Projection { Perspective, Orthographic };
		enum class Clear { Skybox, SolidColor, DepthOnly, DontClear };

		inline static const CCamera* s_Main{};

		int Depth{};
		float Fov{ 60.f }, Near{ 0.003f }, Far{ 1000.f }, OrthoSize{ 10.f };
		Clear Flag{ Clear::Skybox };
		Projection ProjectionType{ Projection::Perspective };
		Matrix4 Projection{ Matrix4::Perspective((float)RE_WINDOW_WIDTH / (float)RE_WINDOW_HEIGHT, Near, Far, Fov) };
		Matrix4 View{ Matrix4::LookAt(Vector3::Zero, Vector3::Forward) };

	private:
		template <class Archive>
		void serialize(Archive& archive) {
			archive(CEREAL_NVP(Depth));
			archive(CEREAL_NVP(Fov));
			archive(CEREAL_NVP(Near));
			archive(CEREAL_NVP(Far));
			archive(CEREAL_NVP(OrthoSize));
			archive(CEREAL_NVP(Flag));
			archive(CEREAL_NVP(ProjectionType));
			archive(CEREAL_NVP(Projection));
			archive(CEREAL_NVP(View));
		}
	};
}

CEREAL_REGISTER_TYPE_WITH_NAME(Reality::CCamera, "Camera");
CEREAL_REGISTER_POLYMORPHIC_RELATION(Reality::Component, Reality::CCamera)