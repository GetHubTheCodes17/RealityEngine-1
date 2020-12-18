// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Rendering/Settings/GLRenderPassSettings.h"
#include "Core/Maths/Vector4.h"
#include "GLTexture.h"

namespace reality {
	class RE_CORE GLRenderPass {
	public:
		uint8 Capacity{};
		uint8 ClearBuffer{ GLRenderPassClearBuffer::ColorBuffer };
		GLRenderPassRasterization Rasterization{ GLRenderPassRasterization::Fill };
		Vector4 ClearColor;
		Viewport Viewport;

		GLRenderPass() = default;
		explicit GLRenderPass(GLRenderPassSettings settings);
		GLRenderPass(GLRenderPass&&) noexcept;
		GLRenderPass& operator=(GLRenderPass&&) noexcept;
		~GLRenderPass();

		void Bind() const;
		void Clear() const;
		void Blit(const GLRenderPass& dest) const;
		void Resize(const struct Viewport& viewport);

		struct Handle {
			unsigned Id{};
			GLTexture DepthStencilAttachment;
			std::vector<GLTexture> ColorAttachments;
		};
		const Handle& GetHandle() const;

	private:
		Handle m_Handle;
	};
}

inline reality::GLRenderPass::GLRenderPass(GLRenderPass&& other) noexcept : 
	Capacity{ std::move(other.Capacity) }, ClearBuffer{ std::move(other.ClearBuffer) }, 
	Rasterization{ std::move(other.Rasterization) }, ClearColor{ std::move(other.ClearColor) },
	Viewport{ std::move(other.Viewport) }, m_Handle{ std::exchange(other.m_Handle, {}) } 
{}

inline reality::GLRenderPass& reality::GLRenderPass::operator=(GLRenderPass&& other) noexcept {
	Capacity = std::move(other.Capacity);
	ClearBuffer = std::move(other.ClearBuffer);
	Rasterization = std::move(other.Rasterization);
	ClearColor = std::move(other.ClearColor);
	Viewport = std::move(other.Viewport);
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline const reality::GLRenderPass::Handle& reality::GLRenderPass::GetHandle() const {
	return m_Handle;
}