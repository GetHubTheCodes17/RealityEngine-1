// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Rendering/Settings/GLDebugDrawingSettings.h"
#include "Core/Maths/Line.h"
#include "GLSLShader.h"
#include "GLShader.h"
#include "GLMesh.h"

namespace reality {
	class RE_CORE GLDebugDrawing {
	public:
		static constexpr auto s_MaxLinesSize{ 1000u };

		void DrawShape(const GLMesh& shape, const Matrix4& transform, GLDebugDrawingSettings settings = {}) const;
		void DrawLines(const Line* lines, unsigned size, GLDebugDrawingSettings settings = {}) const;

	private:
		const GLShader m_DebugDraw{ { shadersHelpers::g_BasicVertexShader, shadersHelpers::g_OnlyColorFragmentShader } };
		const GLMesh m_Lines{ { {}, s_MaxLinesSize * 2, {}, 0, GLMeshUsage::Dynamic, GLMeshDrawType::Lines } };
		const int m_DebugDrawColorLocation{ m_DebugDraw.GetLocation("uColor") };
	};

	RE_CORE extern GLDebugDrawing* g_DebugDrawing;
}