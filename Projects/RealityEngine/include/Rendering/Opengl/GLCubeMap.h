// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Rendering/Settings/GLCubeMapSettings.h"

namespace reality {
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

inline reality::GLCubeMap::GLCubeMap(GLCubeMap&& other) noexcept :
	m_Handle{ std::exchange(other.m_Handle, {}) } 
{}

inline reality::GLCubeMap& reality::GLCubeMap::operator=(GLCubeMap&& other) noexcept {
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline const reality::GLCubeMap::Handle& reality::GLCubeMap::GetHandle() const {
	return m_Handle;
}