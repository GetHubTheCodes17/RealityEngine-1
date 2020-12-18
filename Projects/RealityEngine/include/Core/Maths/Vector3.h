// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Mathf.h"

namespace reality {
	struct Vector3 {
		float X{}, Y{}, Z{};

		RE_CORE static const Vector3 Zero, One, Right, Left, Up, Down, Forward, Back;

		constexpr Vector3() = default;
		explicit constexpr Vector3(const float* xyz);
		constexpr Vector3(float x, float y, float z = {});
		explicit constexpr Vector3(float xyz);
		constexpr Vector3& operator=(const float* xyz);

		constexpr bool operator==(const Vector3& rhs) const;
		constexpr bool operator!=(const Vector3& rhs) const;
		constexpr Vector3 operator+(const Vector3& rhs) const;
		constexpr Vector3 operator-(const Vector3& rhs) const;
		constexpr Vector3 operator-() const;
		constexpr Vector3 operator*(const Vector3& rhs) const;
		constexpr Vector3 operator*(float rhs) const;
		constexpr Vector3 operator/(float rhs) const;
		constexpr float operator|(const Vector3& rhs) const;
		constexpr Vector3 operator^(const Vector3& rhs) const;
		constexpr Vector3& operator+=(const Vector3& rhs);
		constexpr Vector3& operator-=(const Vector3& rhs);
		constexpr Vector3& operator*=(const Vector3& rhs);
		constexpr Vector3& operator*=(float rhs);
		constexpr Vector3& operator/=(float rhs);

		static float Angle(const Vector3& lhs, const Vector3& rhs);
		static float Distance(const Vector3& lhs, const Vector3& rhs);
		static float DistanceXZ(const Vector3& lhs, const Vector3& rhs);
		static Vector3 Normalize(const Vector3& u);
		static constexpr Vector3 Abs(const Vector3& lhs);
		static constexpr Vector3 ClampMagnitude(const Vector3& u, float k);
		static constexpr Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
		static constexpr float Dot(const Vector3& lhs, const Vector3& rhs);
		static constexpr bool Equals(const Vector3& lhs, const Vector3& rhs, float eps = Mathf::Epsilon);
		static constexpr Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
		static constexpr Vector3 Scale(const Vector3& lhs, const Vector3& rhs);
		static constexpr float SqrDistance(const Vector3& lhs, const Vector3& rhs);
		static constexpr float SqrDistanceXZ(const Vector3& lhs, const Vector3& rhs);
		float GetMagnitude() const;
		float GetMagnitudeXZ() const;
		constexpr bool IsNormalize() const;
		constexpr float GetSqrMagnitude() const;
		constexpr float GetSqrMagnitudeXZ() const;
		constexpr Vector3& Set(const float* xyz);
		constexpr Vector3& Set(float x, float y, float z);
		constexpr Vector3& Set(float xyz);
	};
}

constexpr reality::Vector3::Vector3(const float* xyz) :
	X{ xyz[0] }, Y{ xyz[1] }, Z{ xyz[2] } 
{}

constexpr reality::Vector3::Vector3(float x, float y, float z) :
	X{ x }, Y{ y }, Z{ z }
{}

constexpr reality::Vector3::Vector3(float xyz) :
	X{ xyz }, Y{ xyz }, Z{ xyz }
{}

constexpr reality::Vector3& reality::Vector3::operator=(const float* xyz) {
	X = xyz[0];
	Y = xyz[1];
	Z = xyz[2];
	return *this;
}

constexpr bool reality::Vector3::operator==(const Vector3& rhs) const {
	return Mathf::Approx(X, rhs.X) && Mathf::Approx(Y, rhs.Y) && Mathf::Approx(Z, rhs.Z);
}

constexpr bool reality::Vector3::operator!=(const Vector3& rhs) const {
	return !Mathf::Approx(X, rhs.X) || !Mathf::Approx(Y, rhs.Y) || !Mathf::Approx(Z, rhs.Z);
}

constexpr reality::Vector3 reality::Vector3::operator+(const Vector3& rhs) const {
	return { X + rhs.X, Y + rhs.Y, Z + rhs.Z };
}

constexpr reality::Vector3 reality::Vector3::operator-(const Vector3& rhs) const {
	return { X - rhs.X, Y - rhs.Y, Z - rhs.Z };
}

constexpr reality::Vector3 reality::Vector3::operator-() const {
	return { -X, -Y, -Z };
}

constexpr reality::Vector3 reality::Vector3::operator*(const Vector3& rhs) const {
	return { X * rhs.X, Y * rhs.Y, Z * rhs.Z };
}

constexpr reality::Vector3 reality::Vector3::operator*(float rhs) const {
	return { X * rhs, Y * rhs, Z * rhs };
}

constexpr reality::Vector3 reality::Vector3::operator/(float rhs) const {
	return { X / rhs, Y / rhs, Z / rhs };
}

constexpr float reality::Vector3::operator|(const Vector3& rhs) const {
	return X * rhs.X + Y * rhs.Y + Z * rhs.Z;
}

constexpr reality::Vector3 reality::Vector3::operator^(const Vector3& rhs) const {
	return { Y * rhs.Z - rhs.Y * Z, Z * rhs.X - rhs.Z * X, X * rhs.Y - rhs.X * Y };
}

constexpr reality::Vector3& reality::Vector3::operator+=(const Vector3& rhs) {
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	return *this;
}

constexpr reality::Vector3& reality::Vector3::operator-=(const Vector3& rhs) {
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	return *this;
}

constexpr reality::Vector3& reality::Vector3::operator*=(const Vector3& rhs) {
	X *= rhs.X;
	Y *= rhs.Y;
	Z *= rhs.Z;
	return *this;
}

constexpr reality::Vector3& reality::Vector3::operator*=(float rhs) {
	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	return *this;
}

constexpr reality::Vector3& reality::Vector3::operator/=(float rhs) {
	X /= rhs;
	Y /= rhs;
	Z /= rhs;
	return *this;
}

inline float reality::Vector3::Angle(const Vector3& lhs, const Vector3& rhs) {
	return Mathf::Acos((lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z) /
		Mathf::Sqrt((lhs.X * lhs.X + lhs.Y * lhs.Y + lhs.Z * lhs.Z) * (rhs.X * rhs.X + rhs.Y * rhs.Y + rhs.Z * rhs.Z)));
}

inline float reality::Vector3::Distance(const Vector3& lhs, const Vector3& rhs) {
	const auto X{ lhs.X - rhs.X }, Y{ lhs.Y - rhs.Y }, Z{ lhs.Z - rhs.Z };
	return Mathf::Sqrt(X * X + Y * Y + Z * Z);
}

inline float reality::Vector3::DistanceXZ(const Vector3& lhs, const Vector3& rhs) {
	const auto X{ lhs.X - rhs.X }, Z{ lhs.Z - rhs.Z };
	return Mathf::Sqrt(X * X + Z * Z);
}

inline reality::Vector3 reality::Vector3::Normalize(const Vector3& u) {
	const auto k{ Mathf::Sqrt(u.X * u.X + u.Y * u.Y + u.Z * u.Z) };
	return { u.X / k, u.Y / k, u.Z / k };
}

constexpr reality::Vector3 reality::Vector3::Abs(const Vector3& lhs) {
	return { Mathf::Abs(lhs.X), Mathf::Abs(lhs.Y), Mathf::Abs(lhs.Z) };
}

constexpr reality::Vector3 reality::Vector3::ClampMagnitude(const Vector3& u, float k) {
	const auto sqr{ u.X * u.X + u.Y * u.Y + u.Z * u.Z };
	if (sqr > k * k) {
		return u / Mathf::Sqrt(sqr) * k;
	}
	return u;
}

constexpr reality::Vector3 reality::Vector3::Cross(const Vector3& lhs, const Vector3& rhs) {
	return { lhs.Y * rhs.Z - lhs.Z * rhs.Y, lhs.Z * rhs.X - lhs.X * rhs.Z, lhs.X * rhs.Y - lhs.Y * rhs.X };
}

constexpr float reality::Vector3::Dot(const Vector3& lhs, const Vector3& rhs) {
	return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
}

constexpr bool reality::Vector3::Equals(const Vector3& lhs, const Vector3& rhs, float eps) {
	return Mathf::Approx(lhs.X, rhs.X, eps) && Mathf::Approx(lhs.Y, rhs.Y, eps) && Mathf::Approx(lhs.Z, rhs.Z, eps);
}

constexpr reality::Vector3 reality::Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {
	return a + (b - a) * t;
}

constexpr reality::Vector3 reality::Vector3::Scale(const Vector3& lhs, const Vector3& rhs) {
	return { lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z };
}

constexpr float reality::Vector3::SqrDistance(const Vector3& lhs, const Vector3& rhs) {
	const auto X{ lhs.X - rhs.X }, Y{ lhs.Y - rhs.Y }, Z{ lhs.Z - rhs.Z };
	return X * X + Y * Y + Z * Z;
}

constexpr float reality::Vector3::SqrDistanceXZ(const Vector3& lhs, const Vector3& rhs) {
	const auto X{ lhs.X - rhs.X }, Z{ lhs.Z - rhs.Z };
	return X * X + Z * Z;
}

inline float reality::Vector3::GetMagnitude() const {
	return Mathf::Sqrt(X * X + Y * Y + Z * Z);
}

inline float reality::Vector3::GetMagnitudeXZ() const {
	return Mathf::Sqrt(X * X + Z * Z);
}

constexpr bool reality::Vector3::IsNormalize() const {
	return Mathf::Approx(X * X + Y * Y + Z * Z, 1.f);
}

constexpr float reality::Vector3::GetSqrMagnitude() const {
	return X * X + Y * Y + Z * Z;
}

constexpr float reality::Vector3::GetSqrMagnitudeXZ() const {
	return X * X + Z * Z;
}

constexpr reality::Vector3& reality::Vector3::Set(const float* xyz) {
	X = xyz[0];
	Y = xyz[1];
	Z = xyz[2];
	return *this;
}

constexpr reality::Vector3& reality::Vector3::Set(float x, float y, float z) {
	X = x;
	Y = y;
	Z = z;
	return *this;
}

constexpr reality::Vector3& reality::Vector3::Set(float xyz) {
	X = Y = Z = xyz;
	return *this;
}