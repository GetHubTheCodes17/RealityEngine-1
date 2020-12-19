// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Time.h"

namespace reality {
	class RE_CORE GlfwTime final : public Time {
	public:
		void Update() override;
		float GetTime() const override;
		float GetDeltaTime() const override;
		float GetFps() const override;
		void SetTime(float time) const override;

	private:
		float m_PreviousTime{}, m_DeltaTime{};
	};
}

inline void reality::GlfwTime::Update() {
	const auto time{ GetTime() };
	m_DeltaTime = time - m_PreviousTime;
	m_PreviousTime = time;
}

inline float reality::GlfwTime::GetDeltaTime() const {
	return m_DeltaTime;
}

inline float reality::GlfwTime::GetFps() const {
	return 1.f / m_DeltaTime;
}