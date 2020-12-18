// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"
#include "Core/Maths/Vector4.h"

namespace reality {
	struct CLight : Component {
		RE_COMPONENT(CLight, Component)
		enum class Type { Directional, Point, Spot };
		enum class Shadow { None, Soft };

		float Range{ 20.f }, SpotAngle{ 30.f }, Intensity{ 1.f };
		Vector4 Color{ Vector4::One };
		Type Type{ Type::Directional };
		Shadow Shadow{ Shadow::None };
	};
}