// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <string>

#include "Core/Platform.h"

namespace reality {
	struct ShaderSettings {
		std::string VertexPath, FragmentPath, GeometryPath;
	};

	struct RE_CORE Shader {
		std::string VertexSource, FragmentSource, GeometrySource;

		Shader() = default;
		explicit Shader(ShaderSettings settings);
	};
}