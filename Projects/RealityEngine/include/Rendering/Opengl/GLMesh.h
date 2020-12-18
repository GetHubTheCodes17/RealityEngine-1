// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <utility>

#include "Rendering/Settings/GLMeshSettings.h"

namespace reality {
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

inline reality::GLMesh::GLMesh(GLMesh&& other) noexcept :
	Material{ other.Material }, m_Handle{ std::exchange(other.m_Handle, {}) }
{}

inline reality::GLMesh& reality::GLMesh::operator=(GLMesh&& other) noexcept {
	Material = other.Material;
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline const reality::GLMesh::Handle& reality::GLMesh::GetHandle() const {
	return m_Handle;
}