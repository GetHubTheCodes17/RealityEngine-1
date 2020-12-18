// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <memory>
#include <string>

#include "Core/Platform.h"

namespace reality {
	struct TextureSettings {
		std::string Path;
	};

	struct RE_CORE Texture {
		std::unique_ptr<uint8[]> Image;
		int Width{}, Height{}, Channels{ 3 };
		bool Flipped{};

		Texture() = default;
		explicit Texture(TextureSettings settings);
	};
}