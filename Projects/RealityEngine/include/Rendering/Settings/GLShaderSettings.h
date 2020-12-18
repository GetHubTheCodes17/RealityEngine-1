// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <string_view>

namespace reality {
	struct GLShaderSettings {
		std::string_view VertexSource, FragmentSource, GeometrySource;
	};
}