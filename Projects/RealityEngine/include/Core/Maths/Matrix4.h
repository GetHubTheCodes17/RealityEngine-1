// Copyright Reality Engine. All Rights Reserved.

#pragma once

#ifdef RE_SIMD_ENABLE
#include <xmmintrin.h>
#endif

#include "Core/Platform.h"
#include "Mathf.h"
#include "Frustrum.h"
#include "Viewport.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"

namespace Reality {
	struct alignas(16) Matrix4 {
		union {
#ifdef RE_SIMD_ENABLE
			__m128 m_Simd[4];
#endif
			float Array[16]{};
			float Rows[4][4];
		};

		RE_CORE static const Matrix4 Zero, Identity;

		constexpr Matrix4() = default;
		explicit constexpr Matrix4(const float* array);
		constexpr Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
		constexpr Matrix4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);
		constexpr Matrix4& operator=(const float* array);

		constexpr bool operator==(const Matrix4& rhs) const;
		constexpr bool operator!=(const Matrix4& rhs) const;
		constexpr float& operator[](unsigned index);
		constexpr float operator[](unsigned index) const;
		constexpr float& operator()(unsigned row, unsigned col);
		constexpr float operator()(unsigned row, unsigned col) const;
		constexpr Matrix4 operator+(const Matrix4& rhs) const;
		constexpr Matrix4 operator-(const Matrix4& rhs) const;
		constexpr Matrix4 operator-() const;
		constexpr Matrix4 operator*(const Matrix4& rhs) const;
		constexpr Vector4 operator*(const Vector4& rhs) const;
		constexpr Matrix4 operator*(float rhs) const;
		constexpr Matrix4 operator/(float rhs) const;

#ifdef RE_SIMD_ENABLE
		Matrix4& operator+=(const Matrix4& rhs);
		Matrix4& operator-=(const Matrix4& rhs);
		Matrix4& operator*=(const Matrix4& rhs);
		Matrix4& operator*=(float rhs);
		Matrix4& operator/=(float rhs);
#else
		constexpr Matrix4& operator+=(const Matrix4& rhs);
		constexpr Matrix4& operator-=(const Matrix4& rhs);
		constexpr Matrix4& operator*=(const Matrix4& rhs);
		constexpr Matrix4& operator*=(float k);
		constexpr Matrix4& operator/=(float k);
#endif

		static Matrix4 AxisAngle(const Vector3& axis, float angle);
		static Matrix4 Euler(const Vector3& eulerAngles);
		static Matrix4 LookAt(const Vector3& position, const Vector3& target, const Vector3& up = Vector3::Up);
		static Matrix4 Perspective(float aspectRatio, float nearp = 0.01f, float farp = 1000.f, float fov = 45.f);
		static Matrix4 TRS(const Vector3& translation, const Vector3& euler, const Vector3& scale);
		static Matrix4 LightOrtho(const Vector3& position, const Vector3& direction, const Frustrum& frustrum);
		static Vector3 GetTranslation(const Matrix4& translation);
		static Vector3 GetEulerAngles(const Matrix4& rotation);
		static Vector3 GetScale(const Matrix4& scale);
		static Vector3 GetMouseRay(const Matrix4& view, const Matrix4& proj, const Viewport& viewport, Vector2 mousePos);
		static constexpr Matrix4 Inverse(const Matrix4& m);
		static constexpr Matrix4 Lerp(const Matrix4& a, const Matrix4& b, float t);
		static constexpr Matrix4 Ortho(const Frustrum& frustrum);
		static constexpr Matrix4 Scale(const Vector3& scale);
		static constexpr Matrix4 Translate(const Vector3& translation);
		static constexpr Matrix4 Transpose(const Matrix4& m);
		static constexpr bool Equals(const Matrix4& lhs, const Matrix4& rhs, float eps = Mathf::Epsilon);
		constexpr Vector3 GetRow3(unsigned index) const;
		constexpr Vector4 GetRow4(unsigned index) const;
		constexpr Vector3 GetCol3(unsigned index) const;
		constexpr Vector4 GetCol4(unsigned index) const;
		constexpr Matrix4& Set(const float* array);
		constexpr Matrix4& Set(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);
		constexpr Matrix4& SetRow3(unsigned index, const Vector3& row);
		constexpr Matrix4& SetRow4(unsigned index, const Vector4& row);
		constexpr Matrix4& SetCol3(unsigned index, const Vector3& col);
		constexpr Matrix4& SetCol4(unsigned index, const Vector4& col);
	};
}

constexpr Reality::Matrix4::Matrix4(const float* array) {
	for (auto i{ 0 }; i < 16; ++i) {
		Array[i] = array[i];
	}
}

constexpr Reality::Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, 
	float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) :
	Array{ m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 }
{}

constexpr Reality::Matrix4::Matrix4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3) : 
	Array{ row0.X, row0.Y, row0.Z, row0.W, row1.X, row1.Y, row1.Z, row1.W, row2.X, row2.Y, row2.Z, row2.W, 
		row3.X, row3.Y, row3.Z, row3.W }
{}

constexpr Reality::Matrix4& Reality::Matrix4::operator=(const float* array) {
	for (auto i{ 0 }; i < 16; ++i) {
		Array[i] = array[i];
	}
	return *this;
}

constexpr bool Reality::Matrix4::operator==(const Matrix4& rhs) const {
	for (auto i{ 0 }; i < 16; ++i) {
		if (!Mathf::Approx(Array[i], rhs.Array[i])) {
			return false;
		}
	}
	return true;
}

constexpr bool Reality::Matrix4::operator!=(const Matrix4& rhs) const {
	for (auto i{ 0 }; i < 16; ++i) {
		if (!Mathf::Approx(Array[i], rhs.Array[i])) {
			return true;
		}
	}
	return false;
}

constexpr float& Reality::Matrix4::operator[](unsigned index) {
	return Array[index];
}

constexpr float Reality::Matrix4::operator[](unsigned index) const {
	return Array[index];
}

constexpr float& Reality::Matrix4::operator()(unsigned row, unsigned col) {
	return Rows[row][col];
}

constexpr float Reality::Matrix4::operator()(unsigned row, unsigned col) const {
	return Rows[row][col];
}

constexpr Reality::Matrix4 Reality::Matrix4::operator+(const Matrix4& rhs) const {
	Matrix4 res;
	for (auto i{ 0 }; i < 16; ++i) {
		res.Array[i] = Array[i] + rhs.Array[i];
	}
	return res;
}

constexpr Reality::Matrix4 Reality::Matrix4::operator-(const Matrix4& rhs) const {
	Matrix4 res;
	for (auto i{ 0 }; i < 16; ++i) {
		res.Array[i] = Array[i] - rhs.Array[i];
	}
	return res;
}

constexpr Reality::Matrix4 Reality::Matrix4::operator-() const {
	Matrix4 res;
	for (auto i{ 0 }; i < 16; ++i) {
		res.Array[i] = -Array[i];
	}
	return res;
}

constexpr Reality::Matrix4 Reality::Matrix4::operator*(const Matrix4& rhs) const {
	return {
		Array[0] * rhs.Array[0] + Array[1] * rhs.Array[4] + Array[2] * rhs.Array[8] + Array[3] * rhs.Array[12],
		Array[0] * rhs.Array[1] + Array[1] * rhs.Array[5] + Array[2] * rhs.Array[9] + Array[3] * rhs.Array[13],
		Array[0] * rhs.Array[2] + Array[1] * rhs.Array[6] + Array[2] * rhs.Array[10] + Array[3] * rhs.Array[14],
		Array[0] * rhs.Array[3] + Array[1] * rhs.Array[7] + Array[2] * rhs.Array[11] + Array[3] * rhs.Array[15],
		Array[4] * rhs.Array[0] + Array[5] * rhs.Array[4] + Array[6] * rhs.Array[8] + Array[7] * rhs.Array[12],
		Array[4] * rhs.Array[1] + Array[5] * rhs.Array[5] + Array[6] * rhs.Array[9] + Array[7] * rhs.Array[13],
		Array[4] * rhs.Array[2] + Array[5] * rhs.Array[6] + Array[6] * rhs.Array[10] + Array[7] * rhs.Array[14],
		Array[4] * rhs.Array[3] + Array[5] * rhs.Array[7] + Array[6] * rhs.Array[11] + Array[7] * rhs.Array[15],
		Array[8] * rhs.Array[0] + Array[9] * rhs.Array[4] + Array[10] * rhs.Array[8] + Array[11] * rhs.Array[12],
		Array[8] * rhs.Array[1] + Array[9] * rhs.Array[5] + Array[10] * rhs.Array[9] + Array[11] * rhs.Array[13],
		Array[8] * rhs.Array[2] + Array[9] * rhs.Array[6] + Array[10] * rhs.Array[10] + Array[11] * rhs.Array[14],
		Array[8] * rhs.Array[3] + Array[9] * rhs.Array[7] + Array[10] * rhs.Array[11] + Array[11] * rhs.Array[15],
		Array[12] * rhs.Array[0] + Array[13] * rhs.Array[4] + Array[14] * rhs.Array[8] + Array[15] * rhs.Array[12],
		Array[12] * rhs.Array[1] + Array[13] * rhs.Array[5] + Array[14] * rhs.Array[9] + Array[15] * rhs.Array[13],
		Array[12] * rhs.Array[2] + Array[13] * rhs.Array[6] + Array[14] * rhs.Array[10] + Array[15] * rhs.Array[14],
		Array[12] * rhs.Array[3] + Array[13] * rhs.Array[7] + Array[14] * rhs.Array[11] + Array[15] * rhs.Array[15]
	};
}

constexpr Reality::Vector4 Reality::Matrix4::operator*(const Vector4& rhs) const {
	return {
		Array[0] * rhs.X + Array[1] * rhs.Y + Array[2] * rhs.Z + Array[3] * rhs.W,
		Array[4] * rhs.X + Array[5] * rhs.Y + Array[6] * rhs.Z + Array[7] * rhs.W,
		Array[8] * rhs.X + Array[9] * rhs.Y + Array[10] * rhs.Z + Array[11] * rhs.W,
		Array[12] * rhs.X + Array[13] * rhs.Y + Array[14] * rhs.Z + Array[15] * rhs.W
	};
}

constexpr Reality::Matrix4 Reality::Matrix4::operator*(float rhs) const {
	Matrix4 res;
	for (auto i{ 0 }; i < 16; ++i) {
		res.Array[i] = Array[i] * rhs;
	}
	return res;
}

constexpr Reality::Matrix4 Reality::Matrix4::operator/(float rhs) const {
	Matrix4 res;
	for (auto i{ 0 }; i < 16; ++i) {
		res.Array[i] = Array[i] / rhs;
	}
	return res;
}

#ifdef RE_SIMD_ENABLE
inline Reality::Matrix4& Reality::Matrix4::operator+=(const Matrix4& rhs) {
	m_Simd[0] = _mm_add_ps(m_Simd[0], rhs.m_Simd[0]);
	m_Simd[1] = _mm_add_ps(m_Simd[1], rhs.m_Simd[1]);
	m_Simd[2] = _mm_add_ps(m_Simd[2], rhs.m_Simd[2]);
	m_Simd[3] = _mm_add_ps(m_Simd[3], rhs.m_Simd[3]);
	return *this;
}

inline Reality::Matrix4& Reality::Matrix4::operator-=(const Matrix4& rhs) {
	m_Simd[0] = _mm_sub_ps(m_Simd[0], rhs.m_Simd[0]);
	m_Simd[1] = _mm_sub_ps(m_Simd[1], rhs.m_Simd[1]);
	m_Simd[2] = _mm_sub_ps(m_Simd[2], rhs.m_Simd[2]);
	m_Simd[3] = _mm_sub_ps(m_Simd[3], rhs.m_Simd[3]);
	return *this;
}

inline Reality::Matrix4& Reality::Matrix4::operator*=(const Matrix4& rhs) {
	__m128 row{ _mm_mul_ps(_mm_shuffle_ps(m_Simd[0], m_Simd[0], 0), rhs.m_Simd[0]) };
	row = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[1]), _mm_shuffle_ps(m_Simd[0], m_Simd[0], 85));
	row = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[2]), _mm_shuffle_ps(m_Simd[0], m_Simd[0], 170));
	m_Simd[0] = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[3]), _mm_shuffle_ps(m_Simd[0], m_Simd[0], 255));
	row = _mm_mul_ps(_mm_shuffle_ps(m_Simd[1], m_Simd[1], 0), rhs.m_Simd[0]);
	row = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[1]), _mm_shuffle_ps(m_Simd[1], m_Simd[1], 85));
	row = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[2]), _mm_shuffle_ps(m_Simd[1], m_Simd[1], 170));
	m_Simd[1] = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[3]), _mm_shuffle_ps(m_Simd[1], m_Simd[1], 255));
	row = _mm_mul_ps(_mm_shuffle_ps(m_Simd[2], m_Simd[2], 0), rhs.m_Simd[0]);
	row = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[1]), _mm_shuffle_ps(m_Simd[2], m_Simd[2], 85));
	row = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[2]), _mm_shuffle_ps(m_Simd[2], m_Simd[2], 170));
	m_Simd[2] = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[3]), _mm_shuffle_ps(m_Simd[2], m_Simd[2], 255));
	row = _mm_mul_ps(_mm_shuffle_ps(m_Simd[3], m_Simd[3], 0), rhs.m_Simd[0]);
	row = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[1]), _mm_shuffle_ps(m_Simd[3], m_Simd[3], 85));
	row = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[2]), _mm_shuffle_ps(m_Simd[3], m_Simd[3], 170));
	m_Simd[3] = _mm_add_ps(_mm_mul_ps(row, rhs.m_Simd[3]), _mm_shuffle_ps(m_Simd[3], m_Simd[3], 255));
	return *this;
}

inline Reality::Matrix4& Reality::Matrix4::operator*=(float rhs) {
	__m128 vk{ rhs, rhs, rhs, rhs };
	m_Simd[0] = _mm_mul_ps(m_Simd[0], vk);
	m_Simd[1] = _mm_mul_ps(m_Simd[1], vk);
	m_Simd[2] = _mm_mul_ps(m_Simd[2], vk);
	m_Simd[3] = _mm_mul_ps(m_Simd[3], vk);
	return *this;
}

inline Reality::Matrix4& Reality::Matrix4::operator/=(float rhs) {
	__m128 vk{ rhs, rhs, rhs, rhs };
	m_Simd[0] = _mm_div_ps(m_Simd[0], vk);
	m_Simd[1] = _mm_div_ps(m_Simd[1], vk);
	m_Simd[2] = _mm_div_ps(m_Simd[2], vk);
	m_Simd[3] = _mm_div_ps(m_Simd[3], vk);
	return *this;
}
#else
constexpr Reality::Matrix4& Reality::Matrix4::operator+=(const Matrix4& rhs) {
	for (auto i{ 0 }; i < 16; ++i) {
		Array[i] += rhs.Array[i];
	}
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::operator-=(const Matrix4& rhs) {
	for (auto i{ 0 }; i < 16; ++i) {
		Array[i] -= rhs.Array[i];
	}
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::operator*=(const Matrix4& rhs) {
	Array[0] = Array[0] * rhs.Array[0] + Array[1] * rhs.Array[4] + Array[2] * rhs.Array[8] + Array[3] * rhs.Array[12];
	Array[1] = Array[0] * rhs.Array[1] + Array[1] * rhs.Array[5] + Array[2] * rhs.Array[9] + Array[3] * rhs.Array[13];
	Array[2] = Array[0] * rhs.Array[2] + Array[1] * rhs.Array[6] + Array[2] * rhs.Array[10] + Array[3] * rhs.Array[14];
	Array[3] = Array[0] * rhs.Array[3] + Array[1] * rhs.Array[7] + Array[2] * rhs.Array[11] + Array[3] * rhs.Array[15];
	Array[4] = Array[4] * rhs.Array[0] + Array[5] * rhs.Array[4] + Array[6] * rhs.Array[8] + Array[7] * rhs.Array[12];
	Array[5] = Array[4] * rhs.Array[1] + Array[5] * rhs.Array[5] + Array[6] * rhs.Array[9] + Array[7] * rhs.Array[13];
	Array[6] = Array[4] * rhs.Array[2] + Array[5] * rhs.Array[6] + Array[6] * rhs.Array[10] + Array[7] * rhs.Array[14];
	Array[7] = Array[4] * rhs.Array[3] + Array[5] * rhs.Array[7] + Array[6] * rhs.Array[11] + Array[7] * rhs.Array[15];
	Array[8] = Array[8] * rhs.Array[0] + Array[9] * rhs.Array[4] + Array[10] * rhs.Array[8] + Array[11] * rhs.Array[12];
	Array[9] = Array[8] * rhs.Array[1] + Array[9] * rhs.Array[5] + Array[10] * rhs.Array[9] + Array[11] * rhs.Array[13];
	Array[10] = Array[8] * rhs.Array[2] + Array[9] * rhs.Array[6] + Array[10] * rhs.Array[10] + Array[11] * rhs.Array[14];
	Array[11] = Array[8] * rhs.Array[3] + Array[9] * rhs.Array[7] + Array[10] * rhs.Array[11] + Array[11] * rhs.Array[15];
	Array[12] = Array[12] * rhs.Array[0] + Array[13] * rhs.Array[4] + Array[14] * rhs.Array[8] + Array[15] * rhs.Array[12];
	Array[13] = Array[12] * rhs.Array[1] + Array[13] * rhs.Array[5] + Array[14] * rhs.Array[9] + Array[15] * rhs.Array[13];
	Array[14] = Array[12] * rhs.Array[2] + Array[13] * rhs.Array[6] + Array[14] * rhs.Array[10] + Array[15] * rhs.Array[14];
	Array[15] = Array[12] * rhs.Array[3] + Array[13] * rhs.Array[7] + Array[14] * rhs.Array[11] + Array[15] * rhs.Array[15];
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::operator*=(float k) {
	for (auto& elem : Array) {
		elem *= k;
	}
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::operator/=(float k) {
	for (auto& elem : Array) {
		elem /= k;
	}
	return *this;
}
#endif

inline Reality::Matrix4 Reality::Matrix4::AxisAngle(const Vector3& axis, float angle) {
	const auto c{ std::cos(angle) }, s{ std::sin(angle) };
	const auto invCos{ 1.f - c };
	return {
		axis.X * axis.X * invCos + c, axis.X * axis.Y * invCos - axis.Z * s, axis.X * axis.Z * invCos + axis.Y * s, 0.f,
		axis.X * axis.Y * invCos + axis.Z * s, axis.Y * axis.Y * invCos + c, axis.Y * axis.Z * invCos - axis.X * s, 0.f,
		axis.X * axis.Z * invCos - axis.Y * s, axis.Y * axis.Z * invCos + axis.X * s, axis.Z * axis.Z * invCos + c, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

inline Reality::Matrix4 Reality::Matrix4::Euler(const Vector3& eulerAngles) {
	const auto cp{ std::cos(eulerAngles.X) }, cy{ std::cos(eulerAngles.Y) }, cr{ std::cos(eulerAngles.Z) };
	const auto sp{ std::sin(eulerAngles.X) }, sy{ std::sin(eulerAngles.Y) }, sr{ std::sin(eulerAngles.Z) };
	return {
		cy * cr + sy * sp * sr, cp * sr, sr * cy * sp - sy * cr, 0.f,
		cr * sy * sp - sr * sy, cr * cp, sy * sr + cr * cy * sp, 0.f,
		cp * sy, -sp, cp * cy, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

inline Reality::Matrix4 Reality::Matrix4::LookAt(const Vector3& position, const Vector3& target, const Vector3& up) {
	const auto zaxis{ Vector3::Normalize(position - target) };
	const auto xaxis{ Vector3::Normalize(Vector3::Cross(up, zaxis)) };
	const auto yaxis{ Vector3::Cross(zaxis, xaxis) };
	return {
		xaxis.X, yaxis.X, zaxis.X, 0.f,
		xaxis.Y, yaxis.Y, zaxis.Y, 0.f,
		xaxis.Z, yaxis.Z, zaxis.Z, 0.f,
		-Vector3::Dot(position, xaxis), -Vector3::Dot(position, yaxis), -Vector3::Dot(position, zaxis), 1.f
	};
}

inline Reality::Matrix4 Reality::Matrix4::Perspective(float aspectRatio, float nearp, float farp, float fov) {
	const auto zRange{ nearp - farp };
	const auto tanHalfFOV{ std::tan(Mathf::Deg2Rad * (fov / 2.f)) };
	return {
		1.f / (tanHalfFOV * aspectRatio), 0.f, 0.f, 0.f,
		0.f, 1.f / tanHalfFOV, 0.f, 0.f,
		0.f, 0.f, (nearp + farp) / zRange, -1.f,
		0.f, 0.f, (2.f * farp * nearp) / zRange, 0.f
	};
}

inline Reality::Matrix4 Reality::Matrix4::TRS(const Vector3& translation, const Vector3& euler, const Vector3& scale) {
	return Scale(scale) * Euler(euler) * Translate(translation);
}

inline Reality::Matrix4 Reality::Matrix4::LightOrtho(const Vector3& position, const Vector3& direction, const Frustrum& frustrum) {
	const auto forward{ Vector3::Normalize(-direction) };
	const auto right{ Vector3::Normalize(Vector3::Cross(Vector3::Up, forward)) };
	const auto up{ Vector3::Cross(forward, right) };
	const auto rl{ frustrum.Right - frustrum.Left }, tb{ frustrum.Top - frustrum.Bottom }, fn{ frustrum.Front - frustrum.Back };
	const auto rl2{ 2.f / rl }, tb2{ 2.f / tb }, fn2{ -2.f / fn };
	const auto b{ -(frustrum.Top + frustrum.Bottom) / tb };
	const auto c{ -(frustrum.Front + frustrum.Back) / fn };
	const auto x{ -Vector3::Dot(position, right) * rl2 };
	const auto y{ -Vector3::Dot(position, up) * tb2 + b };
	const auto z{ -Vector3::Dot(position, forward) * fn2 + c };
	return {
		right.X * rl2, up.X * tb2, forward.X * fn2, 0.f,
		right.Y * rl2, up.Y * tb2, forward.Y * fn2, 0.f,
		right.Z * rl2, up.Z * tb2, forward.Z * fn2, 0.f,
		x, y, z, 1.f
	};
}

inline Reality::Vector3 Reality::Matrix4::GetTranslation(const Matrix4& translation) {
	return { translation.Array[12], translation.Array[13], translation.Array[14] };
}

inline Reality::Vector3 Reality::Matrix4::GetEulerAngles(const Matrix4& rotation) {
	const auto x{ std::asin(-rotation.Array[9]) };
	if (std::cos(x) > Mathf::Epsilon) {
		return { x, std::atan2(rotation.Array[8], rotation.Array[10]), std::atan2(rotation.Array[1], rotation.Array[5]) };
	}
	return { x, 0.f, std::atan2(-rotation.Array[4], rotation.Array[0]) };
}

inline Reality::Vector3 Reality::Matrix4::GetScale(const Matrix4& scale) {
	if (scale.Array[1] == 0.f && scale.Array[2] == 0.f && scale.Array[4] == 0.f && 
		scale.Array[6] == 0.f && scale.Array[8] == 0.f && scale.Array[9] == 0.f) 
	{
		return { scale.Array[0], scale.Array[5], scale.Array[10] };
	}
	return { 
		std::sqrt(scale.Array[0] * scale.Array[0] + scale.Array[1] * scale.Array[1] + scale.Array[2] * scale.Array[2]),
		std::sqrt(scale.Array[4] * scale.Array[4] + scale.Array[5] * scale.Array[5] + scale.Array[6] * scale.Array[6]),
		std::sqrt(scale.Array[8] * scale.Array[8] + scale.Array[9] * scale.Array[9] + scale.Array[10] * scale.Array[10])
	};
}

inline Reality::Vector3 Reality::Matrix4::GetMouseRay(const Matrix4& view, const Matrix4& proj, const Viewport& viewport, Vector2 mousePos) {
	Vector2 currentRay{ mousePos - viewport.Pos };

	auto GetNormalizedCoords = [&viewport](const Vector2& mousePos) {
		return Vector2{ (2.f * mousePos.X) / viewport.Size.X - 1.f, (2.f * mousePos.Y) / viewport.Size.Y - 1.f };
	};

	Vector2 normalizedCoords{ GetNormalizedCoords(currentRay) };
	Vector4 clipCoords{ normalizedCoords.X, normalizedCoords.Y, -1.f, 1.f };

	auto ToEyeSpace = [&proj](const Vector4& clipCoords) {
		Matrix4 invertedProj{ Matrix4::Inverse(proj) };
		Vector4 eyeCoords{ invertedProj * clipCoords };
		return Vector4{ eyeCoords.X, eyeCoords.Y, -1.f, 0.f };
	};

	auto ToWorldSpace = [&view](const Vector4& eyeCoords) {
		Matrix4 invertedView{ Matrix4::Inverse(view) };
		Vector4 ray{ invertedView * eyeCoords };
		return Vector3{ ray.X, ray.Y, ray.Z };
	};
	return Vector3::Normalize(ToWorldSpace(ToEyeSpace(clipCoords)));
}

constexpr Reality::Matrix4 Reality::Matrix4::Inverse(const Matrix4& m) {
	Matrix4 res{
	m.Array[5] * m.Array[10] * m.Array[15] - m.Array[5] * m.Array[11] * m.Array[14] - m.Array[9] * m.Array[6] * m.Array[15] + 
		m.Array[9] * m.Array[7] * m.Array[14] + m.Array[13] * m.Array[6] * m.Array[11] - m.Array[13] * m.Array[7] * m.Array[10],
	-m.Array[1] * m.Array[10] * m.Array[15] + m.Array[1] * m.Array[11] * m.Array[14] + m.Array[9] * m.Array[2] * m.Array[15] - 
		m.Array[9] * m.Array[3] * m.Array[14] - m.Array[13] * m.Array[2] * m.Array[11] + m.Array[13] * m.Array[3] * m.Array[10],
	m.Array[1] * m.Array[6] * m.Array[15] - m.Array[1] * m.Array[7] * m.Array[14] - m.Array[5] * m.Array[2] * m.Array[15] + 
		m.Array[5] * m.Array[3] * m.Array[14] + m.Array[13] * m.Array[2] * m.Array[7] - m.Array[13] * m.Array[3] * m.Array[6],
	-m.Array[1] * m.Array[6] * m.Array[11] + m.Array[1] * m.Array[7] * m.Array[10] + m.Array[5] * m.Array[2] * m.Array[11] - 
		m.Array[5] * m.Array[3] * m.Array[10] - m.Array[9] * m.Array[2] * m.Array[7] + m.Array[9] * m.Array[3] * m.Array[6],
	-m.Array[4] * m.Array[10] * m.Array[15] + m.Array[4] * m.Array[11] * m.Array[14] + m.Array[8] * m.Array[6] * m.Array[15] - 
		m.Array[8] * m.Array[7] * m.Array[14] - m.Array[12] * m.Array[6] * m.Array[11] + m.Array[12] * m.Array[7] * m.Array[10],
	m.Array[0] * m.Array[10] * m.Array[15] - m.Array[0] * m.Array[11] * m.Array[14] - m.Array[8] * m.Array[2] * m.Array[15] + 
		m.Array[8] * m.Array[3] * m.Array[14] + m.Array[12] * m.Array[2] * m.Array[11] - m.Array[12] * m.Array[3] * m.Array[10],
	-m.Array[0] * m.Array[6] * m.Array[15] + m.Array[0] * m.Array[7] * m.Array[14] + m.Array[4] * m.Array[2] * m.Array[15] - 
		m.Array[4] * m.Array[3] * m.Array[14] - m.Array[12] * m.Array[2] * m.Array[7] + m.Array[12] * m.Array[3] * m.Array[6],
	m.Array[0] * m.Array[6] * m.Array[11] - m.Array[0] * m.Array[7] * m.Array[10] - m.Array[4] * m.Array[2] * m.Array[11] + 
		m.Array[4] * m.Array[3] * m.Array[10] + m.Array[8] * m.Array[2] * m.Array[7] - m.Array[8] * m.Array[3] * m.Array[6],
	m.Array[4] * m.Array[9] * m.Array[15] - m.Array[4] * m.Array[11] * m.Array[13] - m.Array[8] * m.Array[5] * m.Array[15] + 
		m.Array[8] * m.Array[7] * m.Array[13] + m.Array[12] * m.Array[5] * m.Array[11] - m.Array[12] * m.Array[7] * m.Array[9],
	-m.Array[0] * m.Array[9] * m.Array[15] + m.Array[0] * m.Array[11] * m.Array[13] + m.Array[8] * m.Array[1] * m.Array[15] - 
		m.Array[8] * m.Array[3] * m.Array[13] - m.Array[12] * m.Array[1] * m.Array[11] + m.Array[12] * m.Array[3] * m.Array[9],
	m.Array[0] * m.Array[5] * m.Array[15] - m.Array[0] * m.Array[7] * m.Array[13] - m.Array[4] * m.Array[1] * m.Array[15] + 
		m.Array[4] * m.Array[3] * m.Array[13] + m.Array[12] * m.Array[1] * m.Array[7] - m.Array[12] * m.Array[3] * m.Array[5],
	-m.Array[0] * m.Array[5] * m.Array[11] + m.Array[0] * m.Array[7] * m.Array[9] + m.Array[4] * m.Array[1] * m.Array[11] - 
		m.Array[4] * m.Array[3] * m.Array[9] - m.Array[8] * m.Array[1] * m.Array[7] + m.Array[8] * m.Array[3] * m.Array[5],
	-m.Array[4] * m.Array[9] * m.Array[14] + m.Array[4] * m.Array[10] * m.Array[13] + m.Array[8] * m.Array[5] * m.Array[14] - 
		m.Array[8] * m.Array[6] * m.Array[13] - m.Array[12] * m.Array[5] * m.Array[10] + m.Array[12] * m.Array[6] * m.Array[9],
	m.Array[0] * m.Array[9] * m.Array[14] - m.Array[0] * m.Array[10] * m.Array[13] - m.Array[8] * m.Array[1] * m.Array[14] + 
		m.Array[8] * m.Array[2] * m.Array[13] + m.Array[12] * m.Array[1] * m.Array[10] - m.Array[12] * m.Array[2] * m.Array[9],
	-m.Array[0] * m.Array[5] * m.Array[14] + m.Array[0] * m.Array[6] * m.Array[13] + m.Array[4] * m.Array[1] * m.Array[14] - 
		m.Array[4] * m.Array[2] * m.Array[13] - m.Array[12] * m.Array[1] * m.Array[6] + m.Array[12] * m.Array[2] * m.Array[5],
	m.Array[0] * m.Array[5] * m.Array[10] - m.Array[0] * m.Array[6] * m.Array[9] - m.Array[4] * m.Array[1] * m.Array[10] + 
		m.Array[4] * m.Array[2] * m.Array[9] + m.Array[8] * m.Array[1] * m.Array[6] - m.Array[8] * m.Array[2] * m.Array[5]
	};

	const auto determinant{ 1.f / (m.Array[0] * res.Array[0] + m.Array[1] * res.Array[4] + m.Array[2] * res.Array[8] + 
		m.Array[3] * res.Array[12]) };

	for (auto& elem : res.Array) {
		elem *= determinant;
	}
	return res;
}

constexpr Reality::Matrix4 Reality::Matrix4::Lerp(const Matrix4& a, const Matrix4& b, float t) {
	Matrix4 matrix;
	for (auto i{ 0 }; i < 16; ++i) {
		matrix.Array[i] = a.Array[i] + (b.Array[i] - a.Array[i]) * t;
	}
	return matrix;
}

constexpr Reality::Matrix4 Reality::Matrix4::Ortho(const Frustrum& frustrum) {
	return {
		2.f / (frustrum.Right - frustrum.Left), 0.f, 0.f, 0.f,
		0.f, 2.f / (frustrum.Top - frustrum.Bottom), 0.f, 0.f,
		0.f, 0.f, 2.f / (frustrum.Front - frustrum.Back), 0.f,
		-(frustrum.Right + frustrum.Left) / (frustrum.Right - frustrum.Left),
		-(frustrum.Top + frustrum.Bottom) / (frustrum.Top - frustrum.Bottom),
		-(frustrum.Front + frustrum.Back) / (frustrum.Front - frustrum.Back),
		1.f
	};
}

constexpr Reality::Matrix4 Reality::Matrix4::Scale(const Vector3& scale) {
	return {
		scale.X, 0.f, 0.f, 0.f,
		0.f, scale.Y, 0.f, 0.f,
		0.f, 0.f, scale.Z, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

constexpr Reality::Matrix4 Reality::Matrix4::Translate(const Vector3& translation) {
	return {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		translation.X, translation.Y, translation.Z, 1.f
	};
}

constexpr Reality::Matrix4 Reality::Matrix4::Transpose(const Matrix4& m) {
	return {
		m.Array[0], m.Array[4], m.Array[8], m.Array[12],
		m.Array[1], m.Array[5], m.Array[9], m.Array[13],
		m.Array[2], m.Array[6], m.Array[10], m.Array[14],
		m.Array[3], m.Array[7], m.Array[11], m.Array[15],
	};
}

constexpr bool Reality::Matrix4::Equals(const Matrix4& lhs, const Matrix4& rhs, float eps) {
	for (auto i{ 0 }; i < 16; ++i) {
		if (!Mathf::Approx(lhs.Array[i], rhs.Array[i], eps)) {
			return false;
		}
	}
	return true;
}

constexpr Reality::Vector3 Reality::Matrix4::GetRow3(unsigned index) const {
	return { Rows[index][0], Rows[index][1], Rows[index][2] };
}

constexpr Reality::Vector4 Reality::Matrix4::GetRow4(unsigned index) const {
	return { Rows[index][0], Rows[index][1], Rows[index][2], Rows[index][3] };
}

constexpr Reality::Vector3 Reality::Matrix4::GetCol3(unsigned index) const {
	return { Rows[0][index], Rows[1][index], Rows[2][index] };
}

constexpr Reality::Vector4 Reality::Matrix4::GetCol4(unsigned index) const {
	return { Rows[0][index], Rows[1][index], Rows[2][index], Rows[3][index] };
}

constexpr Reality::Matrix4& Reality::Matrix4::Set(const float* array) {
	for (auto i{ 0 }; i < 16; ++i) {
		Array[i] = array[i];
	}
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::Set(const Vector4& row0, const Vector4& row1, const Vector4& row2,
	const Vector4& row3)
{
	Array[0] = row0.X;
	Array[1] = row0.Y;
	Array[2] = row0.Z;
	Array[3] = row0.W;
	Array[4] = row1.X;
	Array[5] = row1.Y;
	Array[6] = row1.Z;
	Array[7] = row1.W;
	Array[8] = row2.X;
	Array[9] = row2.Y;
	Array[10] = row2.Z;
	Array[11] = row2.W;
	Array[12] = row3.X;
	Array[13] = row3.Y;
	Array[14] = row3.Z;
	Array[15] = row3.W;
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::SetRow3(unsigned index, const Vector3& row) {
	Rows[index][0] = row.X;
	Rows[index][1] = row.Y;
	Rows[index][2] = row.Z;
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::SetRow4(unsigned index, const Vector4& row) {
	Rows[index][0] = row.X;
	Rows[index][1] = row.Y;
	Rows[index][2] = row.Z;
	Rows[index][3] = row.W;
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::SetCol3(unsigned index, const Vector3& col) {
	Rows[0][index] = col.X;
	Rows[1][index] = col.Y;
	Rows[2][index] = col.Z;
	return *this;
}

constexpr Reality::Matrix4& Reality::Matrix4::SetCol4(unsigned index, const Vector4& col) {
	Rows[0][index] = col.X;
	Rows[1][index] = col.Y;
	Rows[2][index] = col.Z;
	Rows[3][index] = col.W;
	return *this;
}