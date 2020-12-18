// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Maths/Vector3.h"

namespace reality {
	enum class GLDebugDrawingRasterization { Fill, Line, Point };

	enum GLDebugDrawingCapacity : uint8 {
		CullingTest = 1 << 0,
		DepthTest = 1 << 1
	};

	struct GLDebugDrawingSettings {
		uint8 Capacity{ GLDebugDrawingCapacity::DepthTest | GLDebugDrawingCapacity::CullingTest };
		GLDebugDrawingRasterization Rasterization{ GLDebugDrawingRasterization::Line };
		Vector3 Color{ 1.f, 0.f, 1.f };
		float Thickness{ 1.f };
	};
}