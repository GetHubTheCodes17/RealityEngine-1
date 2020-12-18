// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Rendering/Opengl/GLTexture.h"
#include "Resources/Font/Font.h"

namespace reality {
	struct GLCharacter {
		GLTexture Texture;
		Vector2	Size, Bearing;
		unsigned Advance{};
	};

	struct GLCharacterSettings {
		uint8* Buffer{};
		Vector2 Size, Bearing;
		unsigned Advance{};
	};

	struct GLFontSettings {
		std::array<GLCharacterSettings, 128> Characters;
	};
}