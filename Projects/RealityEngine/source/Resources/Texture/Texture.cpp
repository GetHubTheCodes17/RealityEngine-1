// Copyright Reality Engine. All Rights Reserved.

#define _CRT_SECURE_NO_WARNINGS

#include "Resources/Texture/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include "Core/Tools/Logger.h"

reality::Texture::Texture(TextureSettings settings) {
	const auto binaryPath{ settings.Path.substr(0, settings.Path.find_last_of('.')) + g_ResourcesExtension };

	stbi_set_flip_vertically_on_load_thread(Flipped);

	if (auto inputFile{ std::fopen(binaryPath.c_str(), "rb") }) {

		std::fread(&Width, sizeof(int), 3, inputFile);
		const auto textureSize{ (uint64)(Width * Height * Channels) };
		Image = std::make_unique<uint8[]>(textureSize);
		std::fread(Image.get(), sizeof(uint8), textureSize, inputFile);
		std::fclose(inputFile);
	}
	else {
		Image = std::unique_ptr<uint8[]>{ stbi_load(settings.Path.c_str(), &Width, &Height, &Channels, STBI_default) };
		if (!Image) {
			RE_LOG_WARNING("Cannot load the resource %s", settings.Path.c_str());
			return;
		}

		auto outputFile{ std::fopen(binaryPath.c_str(), "wb") };
		std::fwrite(&Width, sizeof(int), 3, outputFile);
		const auto textureSize{ (uint64)(Width * Height * Channels) };
		std::fwrite(Image.get(), sizeof(uint8), textureSize, outputFile);
		std::fclose(outputFile);
	}
}

bool reality::Texture::IsExtensionSupported(std::string_view filename) {
	return stbi_info(filename.data(), nullptr, nullptr, nullptr);
}