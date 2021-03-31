// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Maths/Vector3.h"
#include "Core/Maths/Vector2.h"

namespace Reality {
	enum VertexAttribute : uint8 {
		Position,
		Normal = 1 << 0,
		Uv = 1 << 1,
		Tangents = 1 << 2
	};

	struct Vertex {
		Vector3 Position, Normal;
		Vector2 Uv;
		Vector3 Tangent, Bitangent;
	};
}