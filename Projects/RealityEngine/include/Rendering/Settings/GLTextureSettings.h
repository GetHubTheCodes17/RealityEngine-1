// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"

namespace Reality {
	enum class GLTextureType { Texture1D, Texture2D, Texture3D };
	enum class GLTextureFormat { Red, Rgb, Srgb, Rgba, Rgbf16, Depth, DepthStencil };
	enum class GLTextureInternalType { Ubyte, Float, Uint24_8 };
	enum class GLTextureWrapping { Repeat, ClampToEdge, ClampToBorder };
	enum class GLTextureFiltering { Nearest, Linear };

	enum GLTextureMask : uint8 {
		AlbedoMap = 1 << 0,
		SpecularMap = 1 << 1,
		NormalMap = 1 << 2,
		HeightMap = 1 << 3,
		ReflectionMap = 1 << 4,
		EmissiveMap = 1 << 5
	};

	struct GLTextureSettings {
		uint8* Image{};
		int Width{ 1 }, Height{ 1 };
		bool HasMipmap{};
		GLTextureFormat InternalFormat{ GLTextureFormat::Rgb };
		GLTextureFormat Format{ GLTextureFormat::Rgb };
		GLTextureInternalType InternalType{ GLTextureInternalType::Ubyte };
		GLTextureType Type{ GLTextureType::Texture2D };
		GLTextureWrapping Wrap{ GLTextureWrapping::Repeat };
		GLTextureFiltering Filter{ GLTextureFiltering::Linear };
		unsigned Samples{};
	};
}