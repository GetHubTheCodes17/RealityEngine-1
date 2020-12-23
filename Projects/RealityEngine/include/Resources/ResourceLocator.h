// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "ResourceManager.h"

namespace reality {
	struct RE_CORE ResourceLocator final {
		std::unordered_map<std::string, GLMesh> Meshes;
		std::unordered_map<std::string, GLMaterial> Materials;
		ResourceManager<GLModel, ModelSettings, GLMeshSettings, Model> Models;
		ResourceManager<GLCubeMap, SkyboxSettings, GLCubeMapSettings, Skybox> Skyboxes;
		ResourceManager<GLTexture, TextureSettings, GLTextureSettings, Texture> Textures;
		ResourceManager<GLShader, ShaderSettings, GLShaderSettings, Shader> Shaders;
		ResourceManager<GLFont, FontSettings, GLFontSettings, Font> Fonts;

		ResourceLocator();
		ResourceLocator(ResourceLocator&&) = delete;
		ResourceLocator& operator=(ResourceLocator&&) = delete;

		void Update();
	};

	RE_CORE extern ResourceLocator* g_ResourceLocator;
}

inline reality::ResourceLocator::ResourceLocator() :
	Textures{ "Resources/Textures.json" }, Models{ "Resources/Models.json" }, Skyboxes{ "Resources/Skyboxes.json" },
	Shaders{ "Resources/Shaders.json" }, Fonts{ "Resources/Fonts.json" }
{}

inline void reality::ResourceLocator::Update() {
	Models.Update();
	Textures.Update();
	Fonts.Update();
	Shaders.Update();
	Skyboxes.Update();
}