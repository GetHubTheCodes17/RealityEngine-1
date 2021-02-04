// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLContext.h"

#include <glad/glad.h>

#include "Rendering/Opengl/GLShaderHelper.h"
#include "Rendering/Opengl/GLMeshHelper.h"
#include "Rendering/Opengl/GLCubeMap.h"
#include "Rendering/Opengl/GLLight.h"
#include "Core/Maths/Matrix4.h"
#include "Core/Tools/Logger.h"

void reality::GLContext::Init(ProcAddr proc) {
	const auto success{ gladLoadGLLoader(reinterpret_cast<GLADloadproc>(proc)) };
	RE_ASSERT(success, "Cannot find the loader for Opengl");

#ifdef RE_DEBUG
	GLint flags{};
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT && GLAD_GL_KHR_debug) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(reality::GLContext::DebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
#endif

	// The five matrices at the location are : Model, View, InverseView, Projection, LightViewProjection
	glGenBuffers(1, &m_MatricesLocation);
	glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesLocation);
	glBufferData(GL_UNIFORM_BUFFER, 5 * sizeof(Matrix4), nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_MatricesLocation);

	glGenBuffers(1, &m_LightsLocation);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_LightsLocation);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLuint) + s_MaxLightsSize * sizeof(GLLight), nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_LightsLocation);
}

void reality::GLContext::DrawSkybox(const GLCubeMap& skybox) {
	GLint previousShaderProgram{};
	glGetIntegerv(GL_CURRENT_PROGRAM, &previousShaderProgram);
	GLboolean previousCullState{};
	glGetBooleanv(GL_CULL_FACE, &previousCullState);
	GLboolean previousDepthState{};
	glGetBooleanv(GL_DEPTH_TEST, &previousDepthState);

	if (previousCullState) {
		glDisable(GL_CULL_FACE);
	}
	if (previousDepthState) {
		glDisable(GL_DEPTH_TEST);
	}

	g_ShaderHelper->Skybox.Bind();
	skybox.Bind(0);
	g_MeshHelper->Cube.Draw();

	glUseProgram((GLuint)previousShaderProgram);

	if (previousCullState) {
		glEnable(GL_CULL_FACE);
	}
	if (previousDepthState) {
		glEnable(GL_DEPTH_TEST);
	}
}

void reality::GLContext::SetLights(std::span<GLLight> lights) {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_LightsLocation);
	auto size{ lights.size() };
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(GLuint) * 4, &size);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(GLuint) * 4, (GLsizeiptr)(sizeof(GLLight) * size), lights.data());
}

void reality::GLContext::SetModelMatrix(const Matrix4& model) {
	glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesLocation);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix4), model.Array);
}

void reality::GLContext::SetViewMatrix(const Matrix4& view) {
	const auto invView{ Matrix4::Inverse(view) };
	glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesLocation);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4), sizeof(Matrix4), view.Array);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4) * 2, sizeof(Matrix4), invView.Array);
}

void reality::GLContext::SetProjectionMatrix(const Matrix4& projection) {
	glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesLocation);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4) * 3, sizeof(Matrix4), projection.Array);
}

void reality::GLContext::SetShadowMatrix(Vector3 lightDirection, Vector3 viewPosition, const Frustrum& frustrum) {
	glBindBuffer(GL_UNIFORM_BUFFER, m_MatricesLocation);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4) * 4, sizeof(Matrix4),
		Matrix4::LightOrtho(viewPosition, lightDirection, frustrum).Array);
}

void reality::GLContext::DebugOutput(unsigned source, unsigned type, unsigned id, unsigned severity,
	int, const char* message, const void*)
{
	// Ignore useless error or warnings
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) {
		return;
	}

	auto errorMsg{ "Opengl Error: " + std::string{ message } +'\n' };

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		errorMsg += "Source: API, ";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		errorMsg += "Source: Window System, ";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		errorMsg += "Source: Shader Compiler, ";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		errorMsg += "Source: Third Party, ";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		errorMsg += "Source: Application, ";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		errorMsg += "Source: Other, ";
		break;
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		errorMsg += "Type: Error, ";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		errorMsg += "Type: Deprecated Behaviour, ";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		errorMsg += "Type: Undefined Behaviour, ";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		errorMsg += "Type: Portability, ";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		errorMsg += "Type: Performance, ";
		break;
	case GL_DEBUG_TYPE_MARKER:
		errorMsg += "Type: Marker, ";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		errorMsg += "Type: Push Group, ";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		errorMsg += "Type: Pop Group, ";
		break;
	case GL_DEBUG_TYPE_OTHER:
		errorMsg += "Type: Other, ";
		break;
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		errorMsg += "Severity: high";
		RE_LOG_ERROR("%s", errorMsg.c_str());
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		errorMsg += "Severity: medium";
		RE_LOG_ERROR("%s", errorMsg.c_str());
		break;
	case GL_DEBUG_SEVERITY_LOW:
		errorMsg += "Severity: low";
		RE_LOG_WARNING("%s", errorMsg.c_str());
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		errorMsg += "Severity: notification";
		RE_LOG_INFO("%s", errorMsg.c_str());
		break;
	}
}