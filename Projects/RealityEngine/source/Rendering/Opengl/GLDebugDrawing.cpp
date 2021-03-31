// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLDebugDrawing.h"

#include <glad/glad.h>

#include "Rendering/Opengl/GLContext.h"
#include "Core/Maths/Matrix4.h"

void Reality::GLDebugDrawing::DrawShape(const GLMesh& shape, const Matrix4& globalTransform,
	GLDebugDrawingSettings settings) const 
{
	m_DebugDraw.Bind();
	glLineWidth(settings.Thickness);
	glPointSize(settings.Thickness);

	(settings.Capacity & GLDebugDrawingCapacity::CullingTest ? glEnable : glDisable)(GL_CULL_FACE);
	(settings.Capacity & GLDebugDrawingCapacity::DepthTest ? glEnable : glDisable)(GL_DEPTH_TEST);

	constexpr GLenum modes[]{ GL_FILL, GL_LINE, GL_POINT };
	glPolygonMode(GL_FRONT_AND_BACK, modes[(int)settings.Rasterization]);

	GLContext::SetModelMatrix(globalTransform);
	glUniform3fv(m_DebugDrawColorLocation, 1, &settings.Color.X);
	shape.Draw();
}

void Reality::GLDebugDrawing::DrawLines(const Line* lines, unsigned size, GLDebugDrawingSettings settings) const {
	m_DebugDraw.Bind();
	glLineWidth(settings.Thickness);
	glPointSize(settings.Thickness);

	GLContext::SetModelMatrix(Matrix4::Identity);
	glUniform3fv(m_DebugDrawColorLocation, 1, &settings.Color.X);

	glBindVertexArray(m_Lines.GetHandle().Vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_Lines.GetHandle().Vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, (GLintptr)(sizeof(Vector3) * 2 * size), lines);
	glDrawArrays((GLenum)(settings.Rasterization == GLDebugDrawingRasterization::Line ? GL_LINES : GL_POINTS), 0, 
		(GLsizei)size * 2);
}