// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <memory>
#include <string>
#include <array>

#include "Core/Platform.h"
#include "Core/Maths/Vector2.h"

namespace Reality {
	struct Character {
		std::unique_ptr<uint8[]> Buffer;
		Vector2 Size, Bearing;
		unsigned Advance{};
	};

	struct FontSettings {
		std::string Path;
		unsigned PixelSize{ 36 };
	};

	struct RE_CORE Font {
		std::array<Character, 128> Characters;

		Font() = default;
		explicit Font(FontSettings settings);

		static bool IsExtensionSupported(std::string_view extension);
	};
}