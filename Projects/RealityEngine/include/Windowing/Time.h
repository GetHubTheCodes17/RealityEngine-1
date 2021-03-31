// Copyright Reality Engine. All Rights Reserved.

#pragma once

namespace Reality {
	class Time {
	public:
		static constexpr auto s_FixedDeltaTime{ 0.02f };

		virtual ~Time() = default;

		virtual void Update() = 0;
		virtual float GetTime() const = 0;
		virtual float GetDeltaTime() const = 0;
		virtual float GetFps() const = 0;
		virtual void SetTime(float time) const = 0;
	};
}