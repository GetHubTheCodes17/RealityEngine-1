// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <vector>

#include "GLTextureSettings.h"

namespace Reality {
	enum class GLRenderPassRasterization { Fill, Line, Point };

	enum GLRenderPassCapacity : uint8 {
		Culling = 1 << 0,
		Depth = 1 << 1,
		Stencil = 1 << 2,
		ClearColor = 1 << 3
	};

	enum GLRenderPassClearBuffer : uint8 {
		ColorBuffer = 1 << 0,
		DepthBuffer = 1 << 1,
		StencilBuffer = 1 << 2,
	};

	enum GLRenderPassFramebufferTexture : uint8 {
		ColorAttachment = 1 << 0,
		DepthAttachment = 1 << 1,
		StencilAttachment = 1 << 2
	};

	struct GLRenderPassSettings {
		uint8 FrameBufferTexture{ GLRenderPassFramebufferTexture::ColorAttachment };
		std::vector<GLTextureSettings> ColorAttachments;
		GLTextureSettings DepthStencilAttachment;
	};
}