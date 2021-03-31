// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <string>

#include "Core/Platform.h"

namespace Reality {
	struct ShaderSettings {
		std::string VertexPath, FragmentPath, GeometryPath;
	};

	struct RE_CORE Shader {
		std::string VertexSource, FragmentSource, GeometrySource;

		Shader() = default;
		explicit Shader(ShaderSettings settings);

		static std::string GetShaderFromFile(std::string_view path);
		static std::string GetShaderFromEngineFile(std::string_view filename);
	};
}