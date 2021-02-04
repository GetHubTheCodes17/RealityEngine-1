// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Core/Maths/Vector3.h"

namespace reality {
	class RE_CORE GLMaterial {
	public:
		Vector3 Color{ Vector3::One }, SpecularStrength{ Vector3::One };
		float Shininess{ 32.f };
		const class GLTexture* Albedo{}, * Specular{}, * Normal{}, * Height{}, * Reflection{}, * Emissive{};

		void Bind() const;
	};
}