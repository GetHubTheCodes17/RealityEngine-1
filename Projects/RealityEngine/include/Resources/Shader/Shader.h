// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <string>

namespace reality {
	struct ShaderSettings {
		std::string VertexPath, FragmentPath, GeometryPath;
	};

	struct Shader {
		std::string VertexSource, FragmentSource, GeometrySource;

		Shader() = default;
		explicit Shader(ShaderSettings settings);
	};
}