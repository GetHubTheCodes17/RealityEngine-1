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

		constexpr bool Approx(float x, float y, float epsilon = Epsilon);
		constexpr float Sign(float x);
	};
}

constexpr bool reality::Mathf::Approx(float x, float y, float epsilon) {
	const auto t{ x - y };
	return (t < 0 ? -t : t) < epsilon;
}

constexpr float reality::Mathf::Sign(float x) {
	return x < 0.f ? -1.f : 1.f;
}