// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <array>

#include "Core/Platform.h"
#include "Input.h"

struct GLFWwindow;

namespace Reality {
	class RE_CORE GlfwInput final : public Input {
	public:
		explicit GlfwInput(GLFWwindow* window = {});

		void PollEvents() const override;
		void WaitEvents() const override;
		bool GetKeyDown(Key Key) const override;
		bool GetKeyUp(Key Key) const override;
		bool GetMouseButton(Key button) const override;
		Vector2 GetCursorPos() const override;
		Vector2 GetRelativeMousePos() const override;
		Vector2 GetMouseScroll() const override;
		void SetCursorPos(float x, float y) const override;

	private:
		inline static std::array<bool, 512> s_KeysDown{};
		inline static std::array<bool, 20> s_MouseButtonsDown{};
		inline static Vector2 s_CursorPosition{};
		inline static Vector2 s_OldCursorPosition{};
		inline static Vector2 s_Scroll{};
	};
}