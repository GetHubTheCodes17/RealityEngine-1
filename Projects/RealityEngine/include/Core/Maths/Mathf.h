// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <numbers>
#include <cmath>

namespace reality {
	namespace Mathf {
		constexpr auto Deg2Rad{ 0.01745329251f };
		constexpr auto Epsilon{ 1.192092896e-07f };
		constexpr auto Rad2Deg{ 57.2957795131f };
		constexpr auto G{ 9.81f };

		float Acos(float x);
		float Asin(float x);
		float Atan(float x);
		float Atan2(float y, float x);
		float Cos(float x);
		float Exp(float x);
		float Ln(float x);
		float Pow(float x, float y);
		float Round(float x);
		float Sin(float x);
		float Sqrt(float x);
		float Tan(float x);
		constexpr float Abs(float x);
		constexpr bool Approx(float x, float y, float epsilon = Epsilon);
		constexpr float Ceil(float x);
		constexpr float Clamp(float x, float min, float max);
		constexpr float Floor(float x);
		constexpr float Lerp(float a, float b, float t);
		constexpr float Max(float a, float b);
		constexpr float Min(float a, float b);
		constexpr float Sign(float x);
	};
}

inline float reality::Mathf::Acos(float x) {
	return std::acos(x);
}

inline float reality::Mathf::Asin(float x) {
	return std::asin(x);
}

inline float reality::Mathf::Atan(float x) {
	return std::atan(x);
}

inline float reality::Mathf::Atan2(float y, float x) {
	return std::atan2(y, x);
}

inline float reality::Mathf::Cos(float x) {
	return std::cos(x);
}

inline float reality::Mathf::Exp(float x) {
	return std::exp(x);
}

inline float reality::Mathf::Ln(float x) {
	return std::log(x);
}

inline float reality::Mathf::Pow(float x, float y) {
	return std::pow(x, y);
}

inline float reality::Mathf::Round(float x) {
	return std::round(x);
}

inline float reality::Mathf::Sin(float x) {
	return std::sin(x);
}

inline float reality::Mathf::Sqrt(float x) {
	return std::sqrt(x);
}

inline float reality::Mathf::Tan(float x) {
	return std::tan(x);
}

constexpr float reality::Mathf::Abs(float x) {
	return x < 0 ? -x : x;
}

constexpr bool reality::Mathf::Approx(float x, float y, float epsilon) {
	const auto t{ x - y };
	return (t < 0 ? -t : t) < epsilon;
}

constexpr float reality::Mathf::Ceil(float x) {
	return (float)((int)x + 1);
}

constexpr float reality::Mathf::Clamp(float x, float min, float max) {
	return x < min ? min : (x > max ? max : x);
}

constexpr float reality::Mathf::Floor(float x) {
	return (float)((int)x);
}

constexpr float reality::Mathf::Lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

constexpr float reality::Mathf::Max(float a, float b) {
	return a > b ? a : b;
}

constexpr float reality::Mathf::Min(float a, float b) {
	return a < b ? a : b;
}

constexpr float reality::Mathf::Sign(float x) {
	return x < 0.f ? -1.f : 1.f;
}