// Copyright Reality Engine. All Rights Reserved.

#pragma once

namespace reality::shadersHelpers {
	constexpr const char* g_DefaultVertexShader{
#include "Rendering/GLSLShaders/Default.vs"
	};
	constexpr const char* g_DefaultFragmentShader{
#include "Rendering/GLSLShaders/Default.fs"
	};

	constexpr const char* g_CubeMapVertexShader{
#include "Rendering/GLSLShaders/CubeMap.vs"
	};
	constexpr const char* g_CubeMapFragmentShader{
#include "Rendering/GLSLShaders/CubeMap.fs"
	};

	constexpr const char* g_ParticleVertexShader{
#include "Rendering/GLSLShaders/Particle.vs"
	};
	constexpr const char* g_ParticleFragmentShader{
#include "Rendering/GLSLShaders/Particle.fs"
	};

	constexpr const char* g_TextVertexShader{
#include "Rendering/GLSLShaders/Text.vs"
	};
	constexpr const char* g_TextFragmentShader{
#include "Rendering/GLSLShaders/Text.fs"
	};

	constexpr const char* g_BasicVertexShader{
#include "Rendering/GLSLShaders/Basic.vs"
	};
	constexpr const char* g_SimpleTextureVertexShader{
#include "Rendering/GLSLShaders/Texture.vs"
	};
	constexpr const char* g_ShadowVertexShader{
#include "Rendering/GLSLShaders/Shadow.vs"
	};
	constexpr const char* g_OnlyColorFragmentShader{
#include "Rendering/GLSLShaders/Color.fs"
	};
	constexpr const char* g_BlurFragmentShader{
#include "Rendering/GLSLShaders/Blur.fs"
	};
	constexpr const char* g_DownSampleFragmentShader{
#include "Rendering/GLSLShaders/DownSample.fs"
	};
	constexpr const char* g_LensFlareFragmentShader{
#include "Rendering/GLSLShaders/LensFlare.fs"
	};
	constexpr const char* g_AdditiveFragmentShader{
#include "Rendering/GLSLShaders/Additive.fs"
	};
}