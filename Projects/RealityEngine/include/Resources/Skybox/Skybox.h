// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <array>

#include "Resources/Texture/Texture.h"

namespace reality {
	struct SkyboxSettings {
		TextureSettings Left, Right, Up, Down, Front, Back;
	};

	struct Skybox {
		std::array<Texture, 6> Textures;

		Skybox() = default;
		explicit Skybox(SkyboxSettings settings);
	};
}

inline reality::Skybox::Skybox(SkyboxSettings settings) :
	Textures{ Texture{ settings.Left }, Texture{ settings.Right }, Texture{ settings.Up },
		Texture{ settings.Down }, Texture{ settings.Front }, Texture{ settings.Back } }
{}