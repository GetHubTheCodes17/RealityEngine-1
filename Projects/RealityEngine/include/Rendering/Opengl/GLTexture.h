// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <utility>

#include "Core/Platform.h"
#include "Rendering/Settings/GLTextureSettings.h"
#include "Core/Maths/Viewport.h"

namespace reality {
	class RE_CORE GLTexture {
	public:
		GLTexture() = default;
		explicit GLTexture(GLTextureSettings settings);
		GLTexture(GLTexture&&) noexcept;
		GLTexture& operator=(GLTexture&&) noexcept;
		~GLTexture();

		void Bind(unsigned index) const;
		void Resize(const Viewport& viewport, const uint8* image = {}) const;

		struct Handle {
			unsigned Id{}, Target{ 3553u }, InternalFormat{}, Format{}, Type{}, Samples{};
		};
		const Handle& GetHandle() const;

	private:
		Handle m_Handle;
	};
}

inline reality::GLTexture::GLTexture(GLTexture&& other) noexcept :
	m_Handle{ std::exchange(other.m_Handle, {}) }
{}

inline reality::GLTexture& reality::GLTexture::operator=(GLTexture&& other) noexcept {
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline const reality::GLTexture::Handle& reality::GLTexture::GetHandle() const {
	return m_Handle;
}