// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Resources/Model/Vertex.h"

namespace Reality {
	enum class GLMeshUsage { Stream, Static, Dynamic };
	enum class GLMeshDrawType { Points, Lines, LineLoop, LineStrip, Triangles, TriangleStrip, TriangleFan };

	struct GLMeshSettings {
		const float* Vertices{};
		unsigned VerticesSize{};
		const unsigned* Indices{};
		unsigned IndicesSize{};
		GLMeshUsage Usage{ GLMeshUsage::Static };
		GLMeshDrawType DrawType{ GLMeshDrawType::Triangles };
		uint8 Attribute{ VertexAttribute::Position };
	};
}