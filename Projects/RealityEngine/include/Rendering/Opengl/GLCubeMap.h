// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Rendering/Settings/GLCubeMapSettings.h"

namespace Reality {
	class RE_CORE GLCubeMap {
	public:
		GLCubeMap() = default;
		explicit GLCubeMap(GLCubeMapSettings settings);
		GLCubeMap(GLCubeMap&&) noexcept;
		GLCubeMap& operator=(GLCubeMap&&) noexcept;
		~GLCubeMap();

		void Bind(unsigned index) const;

		struct Handle {
			unsigned Id{};
		};
		const Handle& GetHandle() const;

	private:
		Handle m_Handle;
	};
}

inline Reality::GLCubeMap::GLCubeMap(GLCubeMap&& other) noexcept :
	m_Handle{ std::exchange(other.m_Handle, {}) } 
{}

inline Reality::GLCubeMap& Reality::GLCubeMap::operator=(GLCubeMap&& other) noexcept {
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline const Reality::GLCubeMap::Handle& Reality::GLCubeMap::GetHandle() const {
	return m_Handle;
}