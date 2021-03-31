// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Rendering/Settings/GLFontSettings.h"
#include "Core/Maths/Vector4.h"

namespace Reality {
	class RE_CORE GLFont {
	public:
		Vector4 Color{ Vector4::One };

		GLFont() = default;
		explicit GLFont(GLFontSettings settings);
		GLFont(GLFont&&) noexcept;
		GLFont& operator=(GLFont&&) noexcept;

		void Draw(std::string_view text, const Viewport& viewport, Vector2 windowSize) const;

		struct Handle {
			unsigned Vao{}, Vbo{};
			std::array<GLCharacter, 128> Characters;
		};
		const Handle& GetHandle() const;

	private:
		Handle m_Handle;
	};
}

inline Reality::GLFont::GLFont(GLFont&& other) noexcept :
	Color{ std::move(other.Color) }, m_Handle{ std::exchange(other.m_Handle, {}) }
{}

inline Reality::GLFont& Reality::GLFont::operator=(GLFont&& other) noexcept {
	Color = std::move(other.Color);
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline const Reality::GLFont::Handle& Reality::GLFont::GetHandle() const {
	return m_Handle;
}