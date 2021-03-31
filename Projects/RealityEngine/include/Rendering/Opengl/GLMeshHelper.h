// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "GLPrimitiveHelper.h"
#include "GLMaterial.h"
#include "GLMesh.h"

namespace Reality {
	struct GLMeshHelper {
		GLMaterial Default;
		GLMesh Quad{ { primitiveHelper::g_Quad, (unsigned)std::size(primitiveHelper::g_Quad) / 8u, {}, 0,
			GLMeshUsage::Static, GLMeshDrawType::Triangles, VertexAttribute::Uv | VertexAttribute::Normal } };
		GLMesh Circle{ { primitiveHelper::g_Circle, (unsigned)std::size(primitiveHelper::g_Circle) / 3, {}, 0,
			GLMeshUsage::Static, GLMeshDrawType::LineLoop } };
		GLMesh Cube{ { primitiveHelper::g_Cube, (unsigned)std::size(primitiveHelper::g_Cube) / 8u, {}, 0,
			GLMeshUsage::Static, GLMeshDrawType::Triangles, VertexAttribute::Uv | VertexAttribute::Normal } };
		GLMesh Sphere{ { primitiveHelper::g_SphereVertices, (unsigned)std::size(primitiveHelper::g_SphereVertices) / 3u,
			primitiveHelper::g_SphereIndices, (unsigned)std::size(primitiveHelper::g_SphereIndices) } };
	};

	RE_CORE extern GLMeshHelper* g_MeshHelper;
}