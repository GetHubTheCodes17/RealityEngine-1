// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLShader.h"

#include <glad/glad.h>

#include "Core/Maths/Matrix4.h"
#include "Core/Maths/Vector4.h"
#include "Core/Maths/Vector3.h"
#include "Core/Maths/Vector2.h"
#include "Core/Tools/Logger.h"

Reality::GLShader::GLShader(GLShaderSettings settings) {
	if (settings.VertexSource.empty()) {
		RE_LOG_ERROR("Try to create Shader without at least one Vertex shader");
	}
	static constexpr auto s_InfoLogBufSize{ 512u };

	auto CreateShaderFromSource = [](GLuint type, std::string_view source) {
		const auto shader{ glCreateShader(type) };
		const auto sourceData{ source.data() };
		glShaderSource(shader, 1, &sourceData, nullptr);
		glCompileShader(shader);

		GLint success{};
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar info[s_InfoLogBufSize];
			glGetShaderInfoLog(shader, s_InfoLogBufSize, nullptr, info);
			RE_LOG_WARNING("Shader compilation failed. Details : %s", info);
		}
		return shader;
	};

	const auto vertexShader{ CreateShaderFromSource(GL_VERTEX_SHADER, settings.VertexSource) };
	GLuint fragmentShader{}, geometryShader{};

	m_Handle.Id = glCreateProgram();
	glAttachShader(m_Handle.Id, vertexShader);

	if (!settings.FragmentSource.empty()) {
		fragmentShader = CreateShaderFromSource(GL_FRAGMENT_SHADER, settings.FragmentSource);
		glAttachShader(m_Handle.Id, fragmentShader);
	}
	if (!settings.GeometrySource.empty()) {
		geometryShader = CreateShaderFromSource(GL_GEOMETRY_SHADER, settings.GeometrySource);
		glAttachShader(m_Handle.Id, geometryShader);
	}

	glLinkProgram(m_Handle.Id);

	GLint success{};
	glGetProgramiv(m_Handle.Id, GL_LINK_STATUS, &success);

	if (!success) {
		GLchar info[s_InfoLogBufSize];
		glGetProgramInfoLog(m_Handle.Id, s_InfoLogBufSize, nullptr, info);
		RE_LOG_WARNING("Program shader compilation failed. Details : %s", info);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}

Reality::GLShader::~GLShader() {
	glDeleteProgram(m_Handle.Id);
}

void Reality::GLShader::Bind() const {
	glUseProgram(m_Handle.Id);
}

int Reality::GLShader::GetLocation(const char* name) const {
	return glGetUniformLocation(m_Handle.Id, name);
}

int Reality::GLShader::GetInt(int location) const {
	GLint value{};
	glGetUniformiv(m_Handle.Id, location, &value);
	return value;
}

float Reality::GLShader::GetFloat(int location) const {
	GLfloat value{};
	glGetUniformfv(m_Handle.Id, location, &value);
	return value;
}

int Reality::GLShader::GetInt(const char* name) const {
	GLint value{};
	glGetUniformiv(m_Handle.Id, glGetUniformLocation(m_Handle.Id, name), &value);
	return value;
}

float Reality::GLShader::GetFloat(const char* name) const {
	GLfloat value{};
	glGetUniformfv(m_Handle.Id, glGetUniformLocation(m_Handle.Id, name), &value);
	return value;
}

void Reality::GLShader::Set(int location, int value) const {
	glUniform1i(location, value);
}

void Reality::GLShader::Set(int location, bool value) const {
	glUniform1i(location, (GLint)value);
}

void Reality::GLShader::Set(int location, unsigned value) const {
	glUniform1ui(location, value);
}

void Reality::GLShader::Set(int location, float value) const {
	glUniform1f(location, value);
}

void Reality::GLShader::Set(int location, const Matrix4& matrix) const {
	glUniformMatrix4fv(location, 1, false, matrix.Array);
}

void Reality::GLShader::Set(int location, const Vector2& vector) const {
	glUniform2fv(location, 1, &vector.X);
}

void Reality::GLShader::Set(int location, const Vector3& vector) const {
	glUniform3fv(location, 1, &vector.X);
}

void Reality::GLShader::Set(int location, const Vector4& vector) const {
	glUniform4fv(location, 1, &vector.X);
}

void Reality::GLShader::Set(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(m_Handle.Id, name), value);
}

void Reality::GLShader::Set(const char* name, bool value) const {
	glUniform1i(glGetUniformLocation(m_Handle.Id, name), (int)value);
}

void Reality::GLShader::Set(const char* name, unsigned value) const {
	glUniform1ui(glGetUniformLocation(m_Handle.Id, name), value);
}

void Reality::GLShader::Set(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(m_Handle.Id, name), value);
}

void Reality::GLShader::Set(const char* name, const Matrix4& matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(m_Handle.Id, name), 1, false, matrix.Array);
}

void Reality::GLShader::Set(const char* name, const Vector2& vector) const {
	glUniform2fv(glGetUniformLocation(m_Handle.Id, name), 1, &vector.X);
}

void Reality::GLShader::Set(const char* name, const Vector3& vector) const {
	glUniform3fv(glGetUniformLocation(m_Handle.Id, name), 1, &vector.X);
}

void Reality::GLShader::Set(const char* name, const Vector4& vector) const {
	glUniform4fv(glGetUniformLocation(m_Handle.Id, name), 1, &vector.X);
}