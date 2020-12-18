// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <utility>

#include "Rendering/Settings/GLShaderSettings.h"
#include "Core/Platform.h"

namespace reality {
	class RE_CORE GLShader {
	public:
		GLShader() = default;
		explicit GLShader(GLShaderSettings settings);
		GLShader(GLShader&&) noexcept;
		GLShader& operator=(GLShader&&) noexcept;
		~GLShader();

		void Bind() const;
		int GetLocation(const char* name) const;
		int GetInt(int location) const;
		float GetFloat(int location) const;
		int GetInt(const char* name) const;
		float GetFloat(const char* name) const;
		void Set(int location, int value) const;
		void Set(int location, bool value) const;
		void Set(int location, unsigned value) const;
		void Set(int location, float value) const;
		void Set(int location, const struct Matrix4& matrix) const;
		void Set(int location, const struct Vector2& vector) const;
		void Set(int location, const struct Vector3& vector) const;
		void Set(int location, const struct Vector4& vector) const;
		void Set(const char* name, int value) const;
		void Set(const char* name, bool value) const;
		void Set(const char* name, unsigned value) const;
		void Set(const char* name, float value) const;
		void Set(const char* name, const Matrix4& matrix) const;
		void Set(const char* name, const Vector2& vector) const;
		void Set(const char* name, const Vector3& vector) const;
		void Set(const char* name, const Vector4& vector) const;

		struct Handle {
			unsigned Id{};
		};
		const Handle& GetHandle() const;

	private:
		Handle m_Handle;
	};
}

inline reality::GLShader::GLShader(GLShader&& other) noexcept :
	m_Handle{ std::exchange(other.m_Handle, {}) } 
{}

inline reality::GLShader& reality::GLShader::operator=(GLShader&& other) noexcept {
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline const reality::GLShader::Handle& reality::GLShader::GetHandle() const {
	return m_Handle;
}