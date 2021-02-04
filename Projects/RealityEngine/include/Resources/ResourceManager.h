// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "ResourceHandler.h"

namespace reality {
	class RE_CORE ResourceManager final {
		friend class GameEngine;

	public:
		std::unordered_map<std::string, GLMesh> Meshes;
		std::unordered_map<std::string, GLMaterial> Materials;
		ResourceHandler<GLModel, ModelSettings, GLMeshSettings, Model> Models;
		ResourceHandler<GLCubeMap, SkyboxSettings, GLCubeMapSettings, Skybox> Skyboxes;
		ResourceHandler<GLTexture, TextureSettings, GLTextureSettings, Texture> Textures;
		ResourceHandler<GLShader, ShaderSettings, GLShaderSettings, Shader> Shaders;
		ResourceHandler<GLFont, FontSettings, GLFontSettings, Font> Fonts;

	private:
		ResourceManager();
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		void Update();
	};

	RE_CORE extern ResourceManager* g_ResourceManager;
}

inline reality::ResourceManager::ResourceManager() :
	Models{ "Resources/Models.json" }, Skyboxes{ "Resources/Skyboxes.json" }, Textures{ "Resources/Textures.json" },
	Shaders{ "Resources/Shaders.json" }, Fonts{ "Resources/Fonts.json" }
{}

inline void reality::ResourceManager::Update() {
	Models.Update();
	Textures.Update();
	Fonts.Update();
	Shaders.Update();
	Skyboxes.Update();
}