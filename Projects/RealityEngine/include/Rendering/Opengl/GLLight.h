// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Maths/Vector4.h"
#include "Core/Maths/Vector3.h"

namespace Reality {
	struct alignas(16) GLLight {
		enum class Type { Directional, Point, Spot };
		enum class Shadow { None, Soft };

		Vector4 Color{ Vector4::One };
		Vector3 Position;
		int32 _Pad0{};
		Vector3 Direction{ Vector3::Forward };
		int32 _Pad1{};
		Type Type{ Type::Directional };
		Shadow Shadow{ Shadow::None };
		float Intensity{ 1.f }, Cutoff{ 10.f }, Outcutoff{ 30.f };
		int32 _Pad2[3]{};
	};
}