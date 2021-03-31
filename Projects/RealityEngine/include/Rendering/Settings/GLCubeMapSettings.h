// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <array>

#include "GLTextureSettings.h"

namespace Reality {
	struct GLCubeMapSettings {
		std::array<GLTextureSettings, 6> Textures;
	};
}