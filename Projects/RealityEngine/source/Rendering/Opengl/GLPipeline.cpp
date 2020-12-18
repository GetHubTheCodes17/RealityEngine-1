// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLPipeline.h"

#include "Rendering/Opengl/GLShaderHelper.h"
#include "Rendering/Opengl/GLMeshHelper.h"
#include "Rendering/Opengl/GLContext.h"
#include "Rendering/Opengl/GLCubeMap.h"

reality::GLPipeline::GLPipeline(const Viewport& viewport) {
	m_ScenePass = GLRenderPass{ { GLRenderPassFramebufferTexture::ColorAttachment |
		GLRenderPassFramebufferTexture::DepthAttachment, { 2, { nullptr, (int)viewport.Width, (int)viewport.Height,
		false, GLTextureFormat::Rgbf16, GLTextureFormat::Rgb, GLTextureInternalType::Float, GLTextureType::Texture2D,
		GLTextureWrapping::ClampToEdge, GLTextureFiltering::Linear, 4 } }, { nullptr, (int)viewport.Width,
		(int)viewport.Height, false, GLTextureFormat::Depth, GLTextureFormat::Depth, GLTextureInternalType::Ubyte,
		GLTextureType::Texture2D, GLTextureWrapping::Repeat, GLTextureFiltering::Linear, 4 } } };
	m_ScenePass.ClearBuffer |= GLRenderPassClearBuffer::DepthBuffer;
	m_ScenePass.Capacity = GLRenderPassCapacity::Culling | GLRenderPassCapacity::Depth;

	GLRenderPassSettings pingpongRenderPassSettings{ GLRenderPassFramebufferTexture::ColorAttachment,
		{ { nullptr, (int)viewport.Width, (int)viewport.Height, false, GLTextureFormat::Rgbf16,
		GLTextureFormat::Rgb, GLTextureInternalType::Float, GLTextureType::Texture2D, GLTextureWrapping::ClampToEdge } } };
	m_BlurPasses[0] = GLRenderPass{ pingpongRenderPassSettings };
	m_BlurPasses[1] = GLRenderPass{ pingpongRenderPassSettings };

	m_MidPass = GLRenderPass{ { GLRenderPassFramebufferTexture::ColorAttachment,
		{ 2, { nullptr, (int)viewport.Width, (int)viewport.Height, false, GLTextureFormat::Rgb, GLTextureFormat::Rgb,
		GLTextureInternalType::Float, GLTextureType::Texture2D, GLTextureWrapping::ClampToEdge } } } };

	GLRenderPassSettings finalRenderPassSettings{ GLRenderPassFramebufferTexture::ColorAttachment,
		{ { nullptr, (int)viewport.Width, (int)viewport.Height } } };
	m_FinalPass = GLRenderPass{ finalRenderPassSettings };
	m_DownPass = GLRenderPass{ finalRenderPassSettings };
	m_LensPass = GLRenderPass{ finalRenderPassSettings };

	static constexpr auto s_ShadowMapSize{ 2048 };
	m_ShadowPass = GLRenderPass{ { GLRenderPassFramebufferTexture::DepthAttachment, {},
		{ nullptr, s_ShadowMapSize, s_ShadowMapSize, false, GLTextureFormat::Depth, GLTextureFormat::Depth,
		GLTextureInternalType::Float, GLTextureType::Texture2D, GLTextureWrapping::ClampToBorder } } };
	m_ShadowPass.ClearBuffer = GLRenderPassClearBuffer::DepthBuffer;
	m_ShadowPass.Capacity |= GLRenderPassCapacity::Depth;
	m_ShadowPass.Viewport = { 0, 0, s_ShadowMapSize, s_ShadowMapSize };

	m_DefaultPass.Viewport = m_ScenePass.Viewport = m_BlurPasses[0].Viewport = m_BlurPasses[1].Viewport =
		m_MidPass.Viewport = m_DownPass.Viewport = m_LensPass.Viewport =
		m_FinalPass.Viewport = viewport;
}

void reality::GLPipeline::BeginShadowPass() const {
	m_ShadowPass.Clear();
	g_ShaderHelper->Shadow.Bind();
}

void reality::GLPipeline::BeginScenePass(const GLCubeMap* skybox) const {
	m_ScenePass.Clear();
	g_ShaderHelper->Default.Bind();
	m_ShadowPass.GetHandle().DepthStencilAttachment.Bind(7);

	if (skybox) {
		GLContext::DrawSkybox(*skybox);
		skybox->Bind(6);
	}
}

void reality::GLPipeline::BeginPostProcess() const {
	static constexpr auto s_BlurAmount{ 8u };
	m_ScenePass.Blit(m_MidPass);

	// Bloom
	g_ShaderHelper->Blur.Bind();
	g_ShaderHelper->Blur.Set(1, false);
	m_BlurPasses[1].Clear();
	m_MidPass.GetHandle().ColorAttachments[1].Bind(0);
	g_MeshHelper->Quad.Draw();
	for (auto i{ 0 }; i < s_BlurAmount; ++i) {
		g_ShaderHelper->Blur.Set(1, (bool)(i % 2));
		i % 2 ? m_BlurPasses[1].Bind() : m_BlurPasses[0].Bind();
		i % 2 ? m_BlurPasses[0].GetHandle().ColorAttachments[0].Bind(0) :
			m_BlurPasses[1].GetHandle().ColorAttachments[0].Bind(0);
		g_MeshHelper->Quad.Draw();
	}

	// Additive Blending
	m_FinalPass.Bind();
	g_ShaderHelper->Additive.Bind();
	m_MidPass.GetHandle().ColorAttachments[0].Bind(0);
	m_BlurPasses[1].GetHandle().ColorAttachments[0].Bind(1);
	g_MeshHelper->Quad.Draw();

	// DownSampled
	m_DownPass.Bind();
	g_ShaderHelper->DownSample.Bind();
	m_MidPass.GetHandle().ColorAttachments[1].Bind(0);
	g_MeshHelper->Quad.Draw();

	// LensFlare
	m_LensPass.Bind();
	g_ShaderHelper->LensFlare.Bind();
	m_DownPass.GetHandle().ColorAttachments[0].Bind(0);
	g_MeshHelper->Quad.Draw();

	// Blur LensFlare
	g_ShaderHelper->Blur.Bind();
	g_ShaderHelper->Blur.Set(1, false);
	m_BlurPasses[1].Bind();
	m_LensPass.GetHandle().ColorAttachments[0].Bind(0);
	g_MeshHelper->Quad.Draw();
	for (auto i{ 0 }; i < s_BlurAmount; ++i) {
		g_ShaderHelper->Blur.Set(1, (bool)(i % 2));
		i % 2 ? m_BlurPasses[1].Bind() : m_BlurPasses[0].Bind();
		i % 2 ? m_BlurPasses[0].GetHandle().ColorAttachments[0].Bind(0) :
			m_BlurPasses[1].GetHandle().ColorAttachments[0].Bind(0);
		g_MeshHelper->Quad.Draw();
	}

	// Combine LensFlare and FinalPass
	m_FinalPass.Bind();
	g_ShaderHelper->Additive.Bind();
	m_BlurPasses[1].GetHandle().ColorAttachments[0].Bind(0);
	m_FinalPass.GetHandle().ColorAttachments[0].Bind(1);
	g_MeshHelper->Quad.Draw();
}