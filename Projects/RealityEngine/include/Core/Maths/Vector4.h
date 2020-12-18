// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Mathf.h"

namespace reality {
	struct Vector4 {
		float X{}, Y{}, Z{}, W{ 1.f };

		RE_CORE static const Vector4 Zero, One, Right, Left, Up, Down, Forward, Back;

		constexpr Vector4() = default;
		explicit constexpr Vector4(const float* xyzw);
		constexpr Vector4(float x, float y, float z = {}, float w = 1.f);
		explicit constexpr Vector4(float xyzw);
		constexpr Vector4& operator=(const float* xyzw);

		constexpr bool operator==(const Vector4& rhs) const;
		constexpr bool operator!=(const Vector4& rhs) const;
		constexpr Vector4 operator+(const Vector4& rhs) const;
		constexpr Vector4 operator-(const Vector4& rhs) const;
		constexpr Vector4 operator-() const;
		constexpr Vector4 operator*(const Vector4& rhs) const;
		constexpr Vector4 operator*(float rhs) const;
		constexpr Vector4 operator/(float rhs) const;
		constexpr Vector4& operator+=(const Vector4& rhs);
		constexpr Vector4& operator-=(const Vector4& rhs);
		constexpr Vector4& operator*=(const Vector4& rhs);
		constexpr Vector4& operator*=(float rhs);
		constexpr Vector4& operator/=(float rhs);

		static constexpr bool Equals(const Vector4& lhs, const Vector4& rhs, float eps = Mathf::Epsilon);
		static constexpr Vector4 Homogenize(const Vector4& u);
		static constexpr Vector4 Scale(const Vector4& lhs, const Vector4& rhs);
		constexpr bool IsHomogenize() const;
		constexpr Vector4& Set(const float* xyzw);
		constexpr Vector4& Set(float x, float y, float z, float w);
		constexpr Vector4& Set(float xyzw);
	};
}

constexpr reality::Vector4::Vector4(const float* xyzw) :
	X{ xyzw[0] }, Y{ xyzw[1] }, Z{ xyzw[2] }, W{ xyzw[3] } 
{}

constexpr reality::Vector4::Vector4(float x, float y, float z, float w) :
	X{ x }, Y{ y }, Z{ z }, W{ w }
{}

constexpr reality::Vector4::Vector4(float xyzw) :
	X{ xyzw }, Y{ xyzw }, Z{ xyzw }, W{ xyzw }
{}

constexpr reality::Vector4& reality::Vector4::operator=(const float* xyzw) {
	X = xyzw[0];
	Y = xyzw[1];
	Z = xyzw[2];
	W = xyzw[3];
	return *this;
}

constexpr bool reality::Vector4::operator==(const Vector4& rhs) const {
	return Mathf::Approx(X, rhs.X) && Mathf::Approx(Y, rhs.Y) && Mathf::Approx(Z, rhs.Z) && Mathf::Approx(W, rhs.W);
}

constexpr bool reality::Vector4::operator!=(const Vector4& rhs) const {
	return !Mathf::Approx(X, rhs.X) || !Mathf::Approx(Y, rhs.Y) || !Mathf::Approx(Z, rhs.Z) || !Mathf::Approx(W, rhs.W);
}

constexpr reality::Vector4 reality::Vector4::operator+(const Vector4& rhs) const {
	return { X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W };
}

constexpr reality::Vector4 reality::Vector4::operator-(const Vector4& rhs) const {
	return { X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W };
}

constexpr reality::Vector4 reality::Vector4::operator-() const {
	return { -X, -Y, -Z, -W };
}

constexpr reality::Vector4 reality::Vector4::operator*(const Vector4& rhs) const {
	return { X * rhs.X, Y * rhs.Y, Z * rhs.Z, W * rhs.W };
}

constexpr reality::Vector4 reality::Vector4::operator*(float rhs) const {
	return { X * rhs, Y * rhs, Z * rhs, W * rhs };
}

constexpr reality::Vector4 reality::Vector4::operator/(float rhs) const {
	return { X / rhs, Y / rhs, Z / rhs, W / rhs };
}

constexpr reality::Vector4& reality::Vector4::operator+=(const Vector4& rhs) {
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	W += rhs.W;
	return *this;
}

constexpr reality::Vector4& reality::Vector4::operator-=(const Vector4& rhs) {
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	W -= rhs.W;
	return *this;
}

constexpr reality::Vector4& reality::Vector4::operator*=(const Vector4& rhs) {
	X *= rhs.X;
	Y *= rhs.Y;
	Z *= rhs.Z;
	W *= rhs.W;
	return *this;
}

constexpr reality::Vector4& reality::Vector4::operator*=(float rhs) {
	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	W *= rhs;
	return *this;
}

constexpr reality::Vector4& reality::Vector4::operator/=(float rhs) {
	X /= rhs;
	Y /= rhs;
	Z /= rhs;
	W /= rhs;
	return *this;
}

constexpr bool reality::Vector4::Equals(const Vector4& lhs, const Vector4& rhs, float eps) {
	return Mathf::Approx(lhs.X, rhs.X, eps) && Mathf::Approx(lhs.Y, rhs.Y, eps) &&
		Mathf::Approx(lhs.Z, rhs.Z, eps) && Mathf::Approx(lhs.W, rhs.W, eps);
}

constexpr reality::Vector4 reality::Vector4::Homogenize(const Vector4& u) {
	return { u.X / u.W, u.Y / u.W, u.Z / u.W, 1.f };
}

constexpr reality::Vector4 reality::Vector4::Scale(const Vector4& lhs, const Vector4& rhs) {
	return { lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z, lhs.W * rhs.W };
}

constexpr bool reality::Vector4::IsHomogenize() const {
	return Mathf::Approx(W, 1.f);
}

constexpr reality::Vector4& reality::Vector4::Set(const float* xyzw) {
	X = xyzw[0];
	Y = xyzw[1];
	Z = xyzw[2];
	W = xyzw[3];
	return *this;
}

constexpr reality::Vector4& reality::Vector4::Set(float x, float y, float z, float w) {
	X = x;
	Y = y;
	Z = z;
	W = w;
	return *this;
}

constexpr reality::Vector4& reality::Vector4::Set(float xyzw) {
	X = Y = Z = W = xyzw;
	return *this;
}