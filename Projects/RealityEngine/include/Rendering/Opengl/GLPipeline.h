// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "GLRenderPass.h"

namespace reality {
	class RE_CORE GLPipeline {
	public:
		explicit GLPipeline(const Viewport& viewport = {});

		void ResizePasses(const Viewport& viewport);
		void BeginShadowPass() const;
		void BeginScenePass(const class GLCubeMap* skybox = {}) const;
		void BeginPostProcess() const;
		const GLRenderPass& GetDefaultPass() const;
		const GLRenderPass& GetFinalPass() const;

	private:
		GLRenderPass m_ShadowPass, m_ScenePass, m_MidPass, m_BlurPasses[2], m_DownPass, m_LensPass, m_FinalPass, m_DefaultPass;
	};
}

inline void reality::GLPipeline::ResizePasses(const Viewport& viewport) {
	m_ScenePass.Resize(viewport);
	m_MidPass.Resize(viewport);
	m_BlurPasses[0].Resize(viewport);
	m_BlurPasses[1].Resize(viewport);
	m_DownPass.Resize(viewport);
	m_LensPass.Resize(viewport);
	m_FinalPass.Resize(viewport);
	m_DefaultPass.Resize(viewport);
}

inline const reality::GLRenderPass& reality::GLPipeline::GetDefaultPass() const {
	return m_DefaultPass;
}

inline const reality::GLRenderPass& reality::GLPipeline::GetFinalPass() const {
	return m_FinalPass;
}