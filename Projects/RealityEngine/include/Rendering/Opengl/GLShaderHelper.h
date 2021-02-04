// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "GLShader.h"
#include "Resources/Shader/Shader.h"

namespace reality {
	struct RE_CORE GLShaderHelper {
		const GLShader Default{ { Shader::GetShaderFromEngineFile("Default.vert"), Shader::GetShaderFromEngineFile("Default.frag") } };
		const GLShader Skybox{ { Shader::GetShaderFromEngineFile("CubeMap.vert"), Shader::GetShaderFromEngineFile("CubeMap.frag") } };
		const GLShader Shadow{ { Shader::GetShaderFromEngineFile("Shadow.vert") } };
		const GLShader Blur{ { Shader::GetShaderFromEngineFile("Texture.vert"), Shader::GetShaderFromEngineFile("Blur.frag") } };
		const GLShader DownSample{ { Shader::GetShaderFromEngineFile("Texture.vert"), Shader::GetShaderFromEngineFile("DownSample.frag") } };
		const GLShader LensFlare{ { Shader::GetShaderFromEngineFile("Texture.vert"), Shader::GetShaderFromEngineFile("LensFlare.frag") } };
		const GLShader Additive{ { Shader::GetShaderFromEngineFile("Texture.vert"), Shader::GetShaderFromEngineFile("Additive.frag") } };
		const GLShader Particle{ { Shader::GetShaderFromEngineFile("Particle.vert"), Shader::GetShaderFromEngineFile("Particle.frag") } };
		const GLShader Text{ { Shader::GetShaderFromEngineFile("Text.vert"), Shader::GetShaderFromEngineFile("Text.frag") } };
	};

	RE_CORE extern GLShaderHelper* g_ShaderHelper;
}