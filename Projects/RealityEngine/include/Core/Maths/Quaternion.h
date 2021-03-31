// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Mathf.h"

namespace Reality {
	struct alignas(16) Quaternion {
		float X{}, Y{}, Z{}, W{ 1.f };

		RE_CORE static const Quaternion Zero, Identity;

		constexpr Quaternion() = default;
		explicit constexpr Quaternion(const float* xyzw);
		explicit Quaternion(float angle, const Vector3& axis);
		explicit Quaternion(const Vector3& eulerAngles);
		explicit Quaternion(const Vector3& from, const Vector3& to);
		explicit Quaternion(const Matrix4& rotation);
		constexpr Quaternion(const Vector3& xyz, float w);
		constexpr Quaternion(float x, float y, float z, float w = 1.f);

		constexpr bool operator==(const Quaternion& rhs) const;
		constexpr bool operator!=(const Quaternion& rhs) const;
		constexpr Quaternion operator+(const Quaternion& rhs) const;
		constexpr Quaternion operator-(const Quaternion& rhs) const;
		constexpr Quaternion operator-() const;
		constexpr Quaternion operator*(const Quaternion& rhs) const;
		constexpr Vector3 operator*(const Vector3& rhs) const;
		constexpr Quaternion operator*(float k) const;
		constexpr Quaternion operator/(float k) const;
		constexpr float operator|(const Quaternion& rhs) const;
		constexpr Quaternion& operator+=(const Quaternion& rhs);
		constexpr Quaternion& operator-=(const Quaternion& rhs);
		constexpr Quaternion& operator*=(const Quaternion& rhs);
		constexpr Quaternion& operator*=(float k);
		constexpr Quaternion& operator/=(float k);

		static Quaternion AxisAngle(float angle, const Vector3& axis);
		static Quaternion Difference(const Quaternion& lhs, const Quaternion& rhs);
		static Quaternion Euler(const Vector3& eulerAngles);
		static Quaternion FromToRotation(Vector3& from, Vector3& to);
		static Quaternion Normalize(const Quaternion& q);
		static Quaternion Slerp(const Quaternion& a, Quaternion b, float t);
		static constexpr Quaternion Conjugate(const Quaternion& q);
		static constexpr float Dot(const Quaternion& lhs, const Quaternion& rhs);
		static constexpr bool Equals(const Quaternion& q1, const Quaternion& q2, float eps = Mathf::Epsilon);
		static constexpr Quaternion Inverse(const Quaternion& q);
		static constexpr Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t);
		float GetAngle() const;
		Vector3 GetEulerAngles() const;
		float GetMagnitude() const;
		Quaternion& Set(float angle, const Vector3& axis);
		Quaternion& Set(const Vector3& eulerAngles);
		Quaternion& Set(const Vector3& from, const Vector3& to);
		Quaternion& Set(const Matrix4& rotation);
		constexpr bool IsIdentity() const;
		constexpr bool IsNormalized() const;
		constexpr Vector3 GetAxis() const;
		constexpr Matrix4 GetMatrix() const;
		constexpr float GetSqrMagnitude() const;
		constexpr Quaternion& Set(const float* xyzw);
		constexpr Quaternion& Set(const Vector3& xyz, float w);
		constexpr Quaternion& Set(float x, float y, float z, float w);
	};
}

constexpr Reality::Quaternion::Quaternion(const float* xyzw) :
	X{ xyzw[0] }, Y{ xyzw[1] }, Z{ xyzw[2] }, W{ xyzw[3] }
{}

inline Reality::Quaternion::Quaternion(float angle, const Vector3& axis) {
	Set(angle, axis);
}

inline Reality::Quaternion::Quaternion(const Vector3& eulerAngles) {
	Set(eulerAngles);
}

inline Reality::Quaternion::Quaternion(const Vector3& from, const Vector3& to) {
	Set(from, to);
}

inline Reality::Quaternion::Quaternion(const Matrix4& rotation) {
	Set(rotation);
}

constexpr Reality::Quaternion::Quaternion(const Vector3& xyz, float w) :
	X{ xyz.X }, Y{ xyz.Y }, Z{ xyz.Z }, W{ w } 
{}

constexpr Reality::Quaternion::Quaternion(float x, float y, float z, float w) :
	X{ x }, Y{ y }, Z{ z }, W{ w }
{}

constexpr bool Reality::Quaternion::operator==(const Quaternion& rhs) const {
	return Mathf::Approx(X, rhs.X) && Mathf::Approx(Y, rhs.Y) && Mathf::Approx(Z, rhs.Z) && Mathf::Approx(W, rhs.W);
}

constexpr bool Reality::Quaternion::operator!=(const Quaternion& rhs) const {
	return !Mathf::Approx(X, rhs.X) || !Mathf::Approx(Y, rhs.Y) || !Mathf::Approx(Z, rhs.Z) || !Mathf::Approx(W, rhs.W);
}

constexpr Reality::Quaternion Reality::Quaternion::operator+(const Quaternion& rhs) const {
	return { X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W };
}

constexpr Reality::Quaternion Reality::Quaternion::operator-(const Quaternion& rhs) const {
	return { X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W };
}

constexpr Reality::Quaternion Reality::Quaternion::operator-() const {
	return { -X, -Y, -Z, -W };
}

constexpr Reality::Quaternion Reality::Quaternion::operator*(const Quaternion& rhs) const {
	return { 
		W * rhs.X + rhs.W * X + Y * rhs.Z - Z * rhs.Y,
		W * rhs.Y + rhs.W * Y + Z * rhs.X - X * rhs.Z,
		W * rhs.Z + rhs.W * Z + X * rhs.Y - Y * rhs.X,
		W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z 
	};
}

constexpr Reality::Vector3 Reality::Quaternion::operator*(const Vector3& rhs) const {
	const Vector3 v{ X, Y, Z };
	return v * 2.f * (v | rhs) + rhs * (W * W - (v | v)) + (v ^ rhs) * 2.f * W;
}

constexpr Reality::Quaternion Reality::Quaternion::operator*(float k) const {
	return { X * k, Y * k, Z * k, W * k };
}

constexpr Reality::Quaternion Reality::Quaternion::operator/(float k) const {
	return { X / k, Y / k, Z / k, W / k };
}

constexpr float Reality::Quaternion::operator|(const Quaternion& rhs) const {
	return X * rhs.X + Y * rhs.Y + Z * rhs.Z + W * rhs.W;
}

constexpr Reality::Quaternion& Reality::Quaternion::operator+=(const Quaternion& rhs) {
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	W += rhs.W;
	return *this;
}

constexpr Reality::Quaternion& Reality::Quaternion::operator-=(const Quaternion& rhs) {
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	W -= rhs.W;
	return *this;
}

constexpr Reality::Quaternion& Reality::Quaternion::operator*=(const Quaternion& rhs) {
	X = W * rhs.X + rhs.W * X + Y * rhs.Z - Z * rhs.Y;
	Y = W * rhs.Y + rhs.W * Y + Z * rhs.X - X * rhs.Z;
	Z = W * rhs.Z + rhs.W * Z + X * rhs.Y - Y * rhs.X;
	W = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
	return *this;
}

constexpr Reality::Quaternion& Reality::Quaternion::operator*=(float k) {
	X *= k;
	Y *= k;
	Z *= k;
	W *= k;
	return *this;
}

constexpr Reality::Quaternion& Reality::Quaternion::operator/=(float k) {
	X /= k;
	Y /= k;
	Z /= k;
	W /= k;
	return *this;
}

inline Reality::Quaternion Reality::Quaternion::AxisAngle(float angle, const Vector3& axis) {
	const auto theta{ angle / 2.f };
	const auto sinTheta{ std::sin(theta) };
	return { axis.X * sinTheta, axis.Y * sinTheta, axis.Z * sinTheta, std::cos(theta) };
}

inline Reality::Quaternion Reality::Quaternion::Difference(const Quaternion& lhs, const Quaternion& rhs) {
	return rhs * Inverse(lhs);
}

inline Reality::Quaternion Reality::Quaternion::Euler(const Vector3& eulerAngles) {
	const auto x{ eulerAngles.X / 2.f }, y{ eulerAngles.Y / 2.f }, z{ eulerAngles.Z / 2.f };
	const auto cx{ std::cos(x) }, cy{ std::cos(y) }, cz{ std::cos(z) };
	const auto sx{ std::sin(x) }, sy{ std::sin(y) }, sz{ std::sin(z) };
	return {
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz - sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz - sx * sy * sz
	};
}

inline Reality::Quaternion Reality::Quaternion::FromToRotation(Vector3& from, Vector3& to) {
	const auto dotFromTo{ from.X * to.X + from.Y * to.Y + from.Z * to.Z };
	const auto sqrSizeFrom{ from.X * from.X + from.Y * from.Y + from.Z * from.Z };
	const auto sqrSizeTo{ to.X * to.X + to.Y * to.Y + to.Z * to.Z };
	const Vector3 axis{ from.Y * to.Z - to.Y * from.Z, from.Z * to.X - to.Z * from.X, from.X * to.Y - to.X * from.Y };
	const auto theta{ std::acos(dotFromTo / std::sqrt(sqrSizeFrom * sqrSizeTo)) / 2.f };
	const auto sinTheta{ std::sin(theta) };
	return { axis.X * sinTheta, axis.Y * sinTheta, axis.Z * sinTheta, std::cos(theta) };
}

inline Reality::Quaternion Reality::Quaternion::Normalize(const Quaternion& q) {
	const auto invSqr{ 1.f / std::sqrt(q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W) };
	return { q.X * invSqr, q.Y * invSqr, q.Z * invSqr, q.W * invSqr };
}

inline Reality::Quaternion Reality::Quaternion::Slerp(const Quaternion& a, Quaternion b, float t) {
	auto cosOmega{ Dot(a, b) };
	if (cosOmega < 0.f) {
		b.X = -b.X;
		b.Y = -b.Y;
		b.Z = -b.Z;
		b.W = -b.W;
		cosOmega = -cosOmega;
	}

	if (cosOmega > 0.9999f) {
		return a * (1.f - t) + b * t;
	}

	const auto sinOmega{ std::sqrt(1.f - cosOmega * cosOmega) };
	const auto omega{ std::atan2(sinOmega, cosOmega) };
	const auto invOmega{ 1.f / sinOmega };
	return a * std::sin((1.f - t) * omega) * invOmega + b * std::sin(t * omega) * invOmega;
}

constexpr Reality::Quaternion Reality::Quaternion::Conjugate(const Quaternion& q) {
	return { -q.X, -q.Y, -q.Z, q.W };
}

constexpr float Reality::Quaternion::Dot(const Quaternion& lhs, const Quaternion& rhs) {
	return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z + lhs.W * rhs.W;
}

constexpr bool Reality::Quaternion::Equals(const Quaternion& q1, const Quaternion& q2, float eps) {
	return Mathf::Approx(q1.X, q2.X, eps) && Mathf::Approx(q1.Y, q2.Y, eps) && 
		Mathf::Approx(q1.Z, q2.Z, eps) && Mathf::Approx(q1.W, q2.W, eps);
}

constexpr Reality::Quaternion Reality::Quaternion::Inverse(const Quaternion& q) {
	const auto sqr{ q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W };
	if (Mathf::Approx(sqr, 0.f)) {
		return { -q.X, -q.Y, -q.Z, q.W };
	}
	return { -q.X / sqr, -q.Y / sqr, -q.Z / sqr, q.W / sqr };
}

constexpr Reality::Quaternion Reality::Quaternion::Lerp(const Quaternion& a, const Quaternion& b, float t) {
	return Dot(a, b) < 0.f ? a + (-b - a) * t : a + (b - a) * t;
}

inline float Reality::Quaternion::GetAngle() const {
	return 2.f * std::acos(W);
}

inline Reality::Vector3 Reality::Quaternion::GetEulerAngles() const {
	const auto sqx{ X * X }, sqy{ Y * Y }, sqz{ Z * Z }, sqw{ W * W };
	const auto unit{ sqx + sqy + sqz + sqw };
	const auto test{ X * Y + Z * W };

	if (test > 0.499 * unit) {
		return { 0.f, 2.f * std::atan2(X, W) * Mathf::Rad2Deg, std::numbers::pi_v<float> * 0.5f * Mathf::Rad2Deg };
	}
	if (test < -0.499 * unit) {
		return { 0.f, -2.f * std::atan2(X, W) * Mathf::Rad2Deg, -std::numbers::pi_v<float> * 0.5f * Mathf::Rad2Deg };
	}
	return { 
		std::atan2(2.f * X * W - 2.f * Y * Z, -sqx + sqy - sqz + sqw) * Mathf::Rad2Deg,
		std::atan2(2.f * Y * W - 2.f * X * Z, sqx - sqy - sqz + sqw) * Mathf::Rad2Deg,
		std::asin(2.f * test / unit) * Mathf::Rad2Deg 
	};
}

inline float Reality::Quaternion::GetMagnitude() const {
	return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

inline Reality::Quaternion& Reality::Quaternion::Set(float angle, const Vector3& axis) {
	const auto theta{ angle / 2.f };
	const auto sinTheta{ std::sin(theta) };
	X = axis.X * sinTheta;
	Y = axis.Y * sinTheta;
	Z = axis.Z * sinTheta;
	W = std::cos(theta);
	return *this;
}

inline Reality::Quaternion& Reality::Quaternion::Set(const Vector3& eulerAngles) {
	const auto x{ eulerAngles.X / 2.f }, y{ eulerAngles.Y / 2.f }, z{ eulerAngles.Z / 2.f };
	const auto cx{ std::cos(x) }, cy{ std::cos(y) }, cz{ std::cos(z) };
	const auto sx{ std::sin(x) }, sy{ std::sin(y) }, sz{ std::sin(z) };
	X = sx * cy * cz - cx * sy * sz;
	Y = cx * sy * cz - sx * cy * sz;
	Z = cx * cy * sz - sx * sy * cz;
	W = cx * cy * cz - sx * sy * sz;
	return *this;
}

inline Reality::Quaternion& Reality::Quaternion::Set(const Vector3& from, const Vector3& to) {
	const auto dotFromTo{ from.X * to.X + from.Y * to.Y + from.Z * to.Z };
	const auto sqrSizeFrom{ from.X * from.X + from.Y * from.Y + from.Z * from.Z };
	const auto sqrSizeTo{ to.X * to.X + to.Y * to.Y + to.Z * to.Z };
	const Vector3 axis{ from.Y * to.Z - to.Y * from.Z, from.Z * to.X - to.Z * from.X, from.X * to.Y - to.X * from.Y };
	const auto theta{ std::acos(dotFromTo / std::sqrt(sqrSizeFrom * sqrSizeTo)) / 2.f };
	const auto sinTheta{ std::sin(theta) };
	X = axis.X * sinTheta;
	Y = axis.Y * sinTheta;
	Z = axis.Z * sinTheta;
	W = std::cos(theta);
	return *this;
}

inline Reality::Quaternion& Reality::Quaternion::Set(const Matrix4& rotation) {
	const auto fourXSquaredMinus1{ rotation.Array[0] - rotation.Array[5] - rotation.Array[10] };
	const auto fourYSquaredMinus1{ rotation.Array[5] - rotation.Array[0] - rotation.Array[10] };
	const auto fourZSquaredMinus1{ rotation.Array[10] - rotation.Array[0] - rotation.Array[5] };
	const auto fourWSquaredMinus1{ rotation.Array[0] + rotation.Array[5] + rotation.Array[10] };

	auto biggestIndex{ 0 };
	auto fourBiggestSquaredMinus1{ fourWSquaredMinus1 };

	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	const auto biggestVal{ std::sqrt(fourBiggestSquaredMinus1 + 1.f) * 0.5f };
	const auto mult{ 0.25f / biggestVal };
	switch (biggestIndex) {
	case 0:
		W = biggestVal;
		X = (rotation.Array[6] - rotation.Array[9]) * mult;
		Y = (rotation.Array[8] - rotation.Array[2]) * mult;
		Z = (rotation.Array[1] - rotation.Array[4]) * mult;
		break;
	case 1:
		X = biggestVal;
		W = (rotation.Array[6] - rotation.Array[9]) * mult;
		Y = (rotation.Array[1] + rotation.Array[4]) * mult;
		Z = (rotation.Array[8] + rotation.Array[2]) * mult;
		break;
	case 2:
		Y = biggestVal;
		W = (rotation.Array[8] - rotation.Array[2]) * mult;
		X = (rotation.Array[1] + rotation.Array[4]) * mult;
		Z = (rotation.Array[6] + rotation.Array[9]) * mult;
		break;
	case 3:
		Z = biggestVal;
		W = (rotation.Array[1] - rotation.Array[4]) * mult;
		X = (rotation.Array[8] + rotation.Array[2]) * mult;
		Y = (rotation.Array[6] + rotation.Array[9]) * mult;
		break;
	}
	return *this;
}

constexpr bool Reality::Quaternion::IsIdentity() const {
	return Mathf::Approx(X, 0.f) && Mathf::Approx(Y, 0.f) && Mathf::Approx(Z, 0.f) && Mathf::Approx(W, 1.f);
}

constexpr bool Reality::Quaternion::IsNormalized() const {
	return Mathf::Approx(X * X + Y * Y + Z * Z + W * W, 1.f);
}

constexpr Reality::Vector3 Reality::Quaternion::GetAxis() const {
	const auto sqr{ X * X + Y * Y + Z * Z };
	return { X / sqr, Y / sqr, Z / sqr };
}

constexpr Reality::Matrix4 Reality::Quaternion::GetMatrix() const {
	return {
		1.f - 2.f * Y * Y - 2.f * Z * Z, 2.f * X * Y - 2.f * W * Z, 2.f * X * Z + 2.f * W * Y, 0.f,
		2.f * X * Y + 2.f * W * Z, 1.f - 2.f * X * X - 2.f * Z * Z, 2.f * Y * Z - 2.f * W * X, 0.f,
		2.f * X * Z - 2.f * W * Y, 2.f * Y * Z + 2.f * W * X, 1.f - 2.f * X * X - 2.f * Y * Y, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

constexpr float Reality::Quaternion::GetSqrMagnitude() const {
	return X * X + Y * Y + Z * Z + W * W;
}

constexpr Reality::Quaternion& Reality::Quaternion::Set(const float* xyzw) {
	X = xyzw[0];
	Y = xyzw[1];
	Z = xyzw[2];
	W = xyzw[3];
	return *this;
}

constexpr Reality::Quaternion& Reality::Quaternion::Set(const Vector3& xyz, float w) {
	X = xyz.X;
	Y = xyz.Y;
	Z = xyz.Z;
	W = w;
	return *this;
}

constexpr Reality::Quaternion& Reality::Quaternion::Set(float x, float y, float z, float w) {
	X = x;
	Y = y;
	Z = z;
	W = w;
	return *this;
}