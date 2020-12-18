// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "ResourceManager.h"

namespace reality {
	RE_CORE extern std::unordered_map<std::string, GLMesh>* g_MeshManager;
	RE_CORE extern std::unordered_map<std::string, GLMaterial>* g_MaterialManager;

	RE_CORE extern ResourceManager<GLModel, ModelSettings, GLMeshSettings, Model>* g_ModelManager;
	RE_CORE extern ResourceManager<GLCubeMap, SkyboxSettings, GLCubeMapSettings, Skybox>* g_SkyboxManager;
	RE_CORE extern ResourceManager<GLTexture, TextureSettings, GLTextureSettings, Texture>* g_TextureManager;
	RE_CORE extern ResourceManager<GLShader, ShaderSettings, GLShaderSettings, Shader>* g_ShaderManager;
	RE_CORE extern ResourceManager<GLFont, FontSettings, GLFontSettings, Font>* g_FontManager;
}