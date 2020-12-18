// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLMesh.h"

#include <glad/glad.h>

reality::GLMesh::GLMesh(GLMeshSettings settings) {
	constexpr GLenum drawTypes[]{ GL_POINTS, GL_LINES, GL_LINE_LOOP, GL_LINE_STRIP, GL_TRIANGLES,
		GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN };
	m_Handle.DrawType = drawTypes[(int)settings.DrawType];
	m_Handle.VerticesSize = settings.VerticesSize;

	glGenVertexArrays(1, &m_Handle.Vao);
	glBindVertexArray(m_Handle.Vao);
	glGenBuffers(1, &m_Handle.Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Handle.Vbo);

	GLsizei vertexSize{ sizeof(GLfloat) * 3 };
	vertexSize += uint8(settings.Attribute & VertexAttribute::Normal) ? sizeof(GLfloat) * 3 : 0;
	vertexSize += uint8(settings.Attribute & VertexAttribute::Uv) ? sizeof(GLfloat) * 2 : 0;
	vertexSize += uint8(settings.Attribute & VertexAttribute::Tangents) ? sizeof(GLfloat) * 6 : 0;

	constexpr GLenum usages[]{ GL_STREAM_DRAW, GL_STATIC_DRAW, GL_DYNAMIC_DRAW };
	const auto usage{ usages[(int)settings.Usage] };
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(settings.VerticesSize * vertexSize), settings.Vertices, usage);

	if (settings.Indices) {
		m_Handle.IndicesSize = settings.IndicesSize;
		glGenBuffers(1, &m_Handle.Ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle.Ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(settings.IndicesSize * sizeof(unsigned)), settings.Indices, usage);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, nullptr);

	if (settings.Attribute & VertexAttribute::Normal) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::Normal)));
	}
	if (settings.Attribute & VertexAttribute::Uv) {
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::Uv)));
	}
	if (settings.Attribute & VertexAttribute::Tangents) {
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::Tangent)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::Bitangent)));
	}
}

reality::GLMesh::~GLMesh() {
	glDeleteBuffers(1, &m_Handle.Ebo);
	glDeleteBuffers(1, &m_Handle.Vbo);
	glDeleteVertexArrays(1, &m_Handle.Vao);
}

void reality::GLMesh::Draw(unsigned instances) const {
	glBindVertexArray(m_Handle.Vao);

	if (m_Handle.IndicesSize) {
		if (!instances) {
			glDrawElements(m_Handle.DrawType, (GLsizei)m_Handle.IndicesSize, GL_UNSIGNED_INT, nullptr);
		}
		else {
			glDrawElementsInstanced(m_Handle.DrawType, (GLsizei)m_Handle.IndicesSize, GL_UNSIGNED_INT, nullptr,
				(GLsizei)instances);
		}
	}
	else {
		if (!instances) {
			glDrawArrays(m_Handle.DrawType, 0, (GLsizei)m_Handle.VerticesSize);
		}
		else {
			glDrawArraysInstanced(m_Handle.DrawType, 0, (GLsizei)m_Handle.VerticesSize, (GLsizei)instances);
		}
	}
}