// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <utility>

#include "Core/Platform.h"
#include "Rendering/Settings/GLMeshSettings.h"

namespace Reality {
	class RE_CORE GLMesh {
	public:
		const class GLMaterial* Material{};

		GLMesh() = default;
		explicit GLMesh(GLMeshSettings settings);
		GLMesh(GLMesh&&) noexcept;
		GLMesh& operator=(GLMesh&&) noexcept;
		~GLMesh();

		void Draw(unsigned instances = {}) const;

		struct Handle {
			unsigned Vao{}, Vbo{}, Ebo{}, VerticesSize{}, IndicesSize{}, DrawType{};
		};
		const Handle& GetHandle() const;

	private:
		Handle m_Handle;
	};
}

inline Reality::GLMesh::GLMesh(GLMesh&& other) noexcept :
	Material{ other.Material }, m_Handle{ std::exchange(other.m_Handle, {}) }
{}

inline Reality::GLMesh& Reality::GLMesh::operator=(GLMesh&& other) noexcept {
	Material = other.Material;
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline const Reality::GLMesh::Handle& Reality::GLMesh::GetHandle() const {
	return m_Handle;
}