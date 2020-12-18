// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "GLSLShader.h"
#include "GLShader.h"

namespace reality {
	struct RE_CORE GLShaderHelper {
		const GLShader Default{ { shadersHelpers::g_DefaultVertexShader, shadersHelpers::g_DefaultFragmentShader } };
		const GLShader Skybox{ { shadersHelpers::g_CubeMapVertexShader, shadersHelpers::g_CubeMapFragmentShader } };
		const GLShader Shadow{ { shadersHelpers::g_ShadowVertexShader } };
		const GLShader Blur{ { shadersHelpers::g_SimpleTextureVertexShader, shadersHelpers::g_BlurFragmentShader } };
		const GLShader DownSample{ { shadersHelpers::g_SimpleTextureVertexShader, shadersHelpers::g_DownSampleFragmentShader } };
		const GLShader LensFlare{ { shadersHelpers::g_SimpleTextureVertexShader, shadersHelpers::g_LensFlareFragmentShader } };
		const GLShader Additive{ { shadersHelpers::g_SimpleTextureVertexShader, shadersHelpers::g_AdditiveFragmentShader } };
		const GLShader Particle{ { shadersHelpers::g_ParticleVertexShader, shadersHelpers::g_ParticleFragmentShader } };
		const GLShader Text{ { shadersHelpers::g_TextVertexShader, shadersHelpers::g_TextFragmentShader } };
	};

	RE_CORE extern GLShaderHelper* g_ShaderHelper;
}