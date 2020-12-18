// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLTexture.h"

#include <glad/glad.h>

reality::GLTexture::GLTexture(GLTextureSettings settings) {
	m_Handle.Samples = settings.Samples;
	m_Handle.Target = settings.Type == GLTextureType::Texture1D ? GL_TEXTURE_1D :
		(unsigned)(settings.Type == GLTextureType::Texture2D ?
			(m_Handle.Samples ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D) : GL_TEXTURE_3D);

	constexpr GLenum internalFormats[]{ GL_RED, GL_RGB, GL_SRGB, GL_RGBA, GL_RGB16F, GL_DEPTH_COMPONENT, GL_DEPTH24_STENCIL8 };
	m_Handle.InternalFormat = internalFormats[(int)settings.InternalFormat];

	constexpr GLenum formats[]{ GL_RED, GL_RGB, GL_SRGB, GL_RGBA, GL_RGB16F, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL };
	m_Handle.Format = formats[(int)settings.Format];

	constexpr GLenum internalTypes[]{ GL_UNSIGNED_BYTE, GL_FLOAT, GL_UNSIGNED_INT_24_8 };
	m_Handle.Type = internalTypes[(int)settings.InternalType];

	glGenTextures(1, &m_Handle.Id);
	glBindTexture(m_Handle.Target, m_Handle.Id);

	if (m_Handle.Samples) {
		glTexImage2DMultisample(m_Handle.Target, (GLsizei)m_Handle.Samples, m_Handle.InternalFormat,
			settings.Width, settings.Height, GL_TRUE);
	}
	else {
		constexpr GLint wrappingModes[]{ GL_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER };
		const auto wrap{ wrappingModes[(int)settings.Wrap] };

		constexpr GLint filters[]{ GL_NEAREST, GL_LINEAR };
		const auto filtermag{ filters[(int)settings.Filter] };
		const auto filtermin{ settings.Filter == GLTextureFiltering::Nearest ? GL_NEAREST : settings.HasMipmap ?
			GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR };

		glTexImage2D(m_Handle.Target, 0, (GLint)m_Handle.InternalFormat, (GLsizei)settings.Width, (GLsizei)settings.Height, 
			0, m_Handle.Format, m_Handle.Type, settings.Image);
		glTexParameteri(m_Handle.Target, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(m_Handle.Target, GL_TEXTURE_WRAP_T, wrap);
		glTexParameteri(m_Handle.Target, GL_TEXTURE_MIN_FILTER, filtermin);
		glTexParameteri(m_Handle.Target, GL_TEXTURE_MAG_FILTER, filtermag);
		constexpr GLfloat borderColor[]{ 1.f, 1.f, 1.f, 1.f };
		glTexParameterfv(m_Handle.Target, GL_TEXTURE_BORDER_COLOR, borderColor);

		if (settings.HasMipmap) {
			glGenerateMipmap(m_Handle.Target);
		}
	}
}

reality::GLTexture::~GLTexture() {
	glDeleteTextures(1, &m_Handle.Id);
}

void reality::GLTexture::Bind(unsigned index) const {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(m_Handle.Target, m_Handle.Id);
}

void reality::GLTexture::Resize(const Viewport& viewport, const uint8* image) const {
	glBindTexture(m_Handle.Target, m_Handle.Id);
	if (m_Handle.Samples) {
		glTexImage2DMultisample(m_Handle.Target, (GLsizei)m_Handle.Samples, m_Handle.InternalFormat,
			(GLsizei)viewport.Width, (GLsizei)viewport.Height, GL_TRUE);
	}
	else {
		glTexImage2D(m_Handle.Target, 0, (GLsizei)m_Handle.InternalFormat, (GLsizei)viewport.Width,
			(GLsizei)viewport.Height, 0, m_Handle.Format, m_Handle.Type, image);
	}
}