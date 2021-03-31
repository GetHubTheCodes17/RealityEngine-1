// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Mathf.h"

namespace Reality {
	struct Vector2 {
		float X{}, Y{};

		RE_CORE static const Vector2 Zero, One, Right, Left, Up, Down;

		constexpr Vector2() = default;
		explicit constexpr Vector2(const float* xy);
		constexpr Vector2(float x, float y);
		explicit constexpr Vector2(float xy);
		constexpr Vector2& operator=(const float* xy);

		constexpr bool operator==(const Vector2& rhs) const;
		constexpr bool operator!=(const Vector2& rhs) const;
		constexpr Vector2 operator+(const Vector2& rhs) const;
		constexpr Vector2 operator-(const Vector2& rhs) const;
		constexpr Vector2 operator-() const;
		constexpr Vector2 operator*(const Vector2& rhs) const;
		constexpr Vector2 operator*(float rhs) const;
		constexpr Vector2 operator/(float rhs) const;
		constexpr float operator|(const Vector2& rhs) const;
		constexpr float operator^(const Vector2& rhs) const;
		constexpr Vector2& operator+=(const Vector2& rhs);
		constexpr Vector2& operator-=(const Vector2& rhs);
		constexpr Vector2& operator*=(const Vector2& rhs);
		constexpr Vector2& operator*=(float rhs);
		constexpr Vector2& operator/=(float rhs);

		static float Angle(const Vector2& lhs, const Vector2& rhs);
		static float Distance(const Vector2& lhs, const Vector2& rhs);
		static Vector2 Normalize(const Vector2& u);
		static constexpr Vector2 ClampMagnitude(const Vector2& u, float k);
		static constexpr float Cross(const Vector2& lhs, const Vector2& rhs);
		static constexpr float Dot(const Vector2& lhs, const Vector2& rhs);
		static constexpr bool Equals(const Vector2& lhs, const Vector2& rhs, float eps = Mathf::Epsilon);
		static constexpr Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
		static constexpr Vector2 Scale(const Vector2& lhs, const Vector2& rhs);
		static constexpr float SqrDistance(const Vector2& lhs, const Vector2& rhs);
		float GetMagnitude() const;
		constexpr bool IsNormalize() const;
		constexpr float GetSqrMagnitude() const;
		constexpr Vector2& Set(const float* xy);
		constexpr Vector2& Set(float x, float y);
		constexpr Vector2& Set(float xy);
	};
}

constexpr Reality::Vector2::Vector2(const float* xy) :
	X{ xy[0] }, Y{ xy[1] } 
{}

constexpr Reality::Vector2::Vector2(float x, float y) : 
	X{ x }, Y{ y }
{}

constexpr Reality::Vector2::Vector2(float xy) : 
	X{ xy }, Y{ xy }
{}

constexpr Reality::Vector2& Reality::Vector2::operator=(const float* xy) {
	X = xy[0];
	Y = xy[1];
	return *this;
}

constexpr bool Reality::Vector2::operator==(const Vector2& rhs) const {
	return Mathf::Approx(X, rhs.X) && Mathf::Approx(Y, rhs.Y);
}

constexpr bool Reality::Vector2::operator!=(const Vector2& rhs) const {
	return !Mathf::Approx(X, rhs.X) || !Mathf::Approx(Y, rhs.Y);
}

constexpr Reality::Vector2 Reality::Vector2::operator+(const Vector2& rhs) const {
	return { X + rhs.X, Y + rhs.Y };
}

constexpr Reality::Vector2 Reality::Vector2::operator-(const Vector2& rhs) const {
	return { X - rhs.X, Y - rhs.Y };
}

constexpr Reality::Vector2 Reality::Vector2::operator-() const {
	return { -X, -Y };
}

constexpr Reality::Vector2 Reality::Vector2::operator*(const Vector2& rhs) const {
	return { X * rhs.X, Y * rhs.Y };
}

constexpr Reality::Vector2 Reality::Vector2::operator*(float rhs) const {
	return { X * rhs, Y * rhs };
}

constexpr Reality::Vector2 Reality::Vector2::operator/(float rhs) const {
	return { X / rhs, Y / rhs };
}

constexpr float Reality::Vector2::operator|(const Vector2& rhs) const {
	return X * rhs.X + Y * rhs.Y;
}

constexpr float Reality::Vector2::operator^(const Vector2& rhs) const {
	return X * rhs.Y - rhs.X * Y;
}

constexpr Reality::Vector2& Reality::Vector2::operator+=(const Vector2& rhs) {
	X += rhs.X;
	Y += rhs.Y;
	return *this;
}

constexpr Reality::Vector2& Reality::Vector2::operator-=(const Vector2& rhs) {
	X -= rhs.X;
	Y -= rhs.Y;
	return *this;
}

constexpr Reality::Vector2& Reality::Vector2::operator*=(const Vector2& rhs) {
	X *= rhs.X;
	Y *= rhs.Y;
	return *this;
}

constexpr Reality::Vector2& Reality::Vector2::operator*=(float rhs) {
	X *= rhs;
	Y *= rhs;
	return *this;
}

constexpr Reality::Vector2& Reality::Vector2::operator/=(float rhs) {
	X /= rhs;
	Y /= rhs;
	return *this;
}

inline float Reality::Vector2::Angle(const Vector2& lhs, const Vector2& rhs) {
	return std::acos((lhs.X * rhs.X + lhs.Y * rhs.Y) / std::sqrt((lhs.X * lhs.X + lhs.Y * lhs.Y) *
		(rhs.X * rhs.X + rhs.Y * rhs.Y)));
}

inline float Reality::Vector2::Distance(const Vector2& lhs, const Vector2& rhs) {
	const auto X{ lhs.X - rhs.X }, Y{ lhs.Y - rhs.Y };
	return std::sqrt(X * X + Y * Y);
}

inline Reality::Vector2 Reality::Vector2::Normalize(const Vector2& u) {
	const auto k{ std::sqrt(u.X * u.X + u.Y * u.Y) };
	return { u.X / k, u.Y / k };
}

constexpr Reality::Vector2 Reality::Vector2::ClampMagnitude(const Vector2& u, float k) {
	const auto sqr{ u.X * u.X + u.Y * u.Y };
	if (sqr > k * k) {
		return u / std::sqrt(sqr) * k;
	}
	return u;
}

constexpr float Reality::Vector2::Cross(const Vector2& lhs, const Vector2& rhs) {
	return lhs.X * rhs.Y - lhs.Y * rhs.X;
}

constexpr float Reality::Vector2::Dot(const Vector2& lhs, const Vector2& rhs) {
	return lhs.X * rhs.X + lhs.Y * rhs.Y;
}

constexpr bool Reality::Vector2::Equals(const Vector2& lhs, const Vector2& rhs, float eps) {
	return Mathf::Approx(lhs.X, rhs.X, eps) && Mathf::Approx(lhs.Y, rhs.Y, eps);
}

constexpr Reality::Vector2 Reality::Vector2::Lerp(const Vector2& a, const Vector2& b, float t) {
	return a + (b - a) * t;
}

constexpr Reality::Vector2 Reality::Vector2::Scale(const Vector2& lhs, const Vector2& rhs) {
	return { lhs.X * rhs.X, lhs.Y * rhs.Y };
}

constexpr float Reality::Vector2::SqrDistance(const Vector2& lhs, const Vector2& rhs) {
	const auto X{ lhs.X - rhs.X }, Y{ lhs.Y - rhs.Y };
	return X * X + Y * Y;
}

inline float Reality::Vector2::GetMagnitude() const {
	return std::sqrt(X * X + Y * Y);
}

constexpr bool Reality::Vector2::IsNormalize() const {
	return Mathf::Approx(X * X + Y * Y, 1.f);
}

constexpr float Reality::Vector2::GetSqrMagnitude() const {
	return X * X + Y * Y;
}

constexpr Reality::Vector2& Reality::Vector2::Set(const float* xy) {
	X = xy[0];
	Y = xy[1];
	return *this;
}

constexpr Reality::Vector2& Reality::Vector2::Set(float x, float y) {
	X = x;
	Y = y;
	return *this;
}

constexpr Reality::Vector2& Reality::Vector2::Set(float xy) {
	X = Y = xy;
	return *this;
}