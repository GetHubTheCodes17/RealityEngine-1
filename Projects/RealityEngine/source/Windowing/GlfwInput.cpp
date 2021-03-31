// Copyright Reality Engine. All Rights Reserved.

#include "Windowing/GlfwInput.h"

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

Reality::GlfwInput::GlfwInput(GLFWwindow* window) {
	auto currentWindow{ window ? window : glfwGetCurrentContext() };
	RE_ASSERT(currentWindow, "Trying to create GlfwInput class without any current glfw context");

	auto mousePosX{ 0. }, mousePosY{ 0. };
	glfwGetCursorPos(currentWindow, &mousePosX, &mousePosY);
	s_CursorPosition.X = (float)mousePosX;
	s_CursorPosition.Y = (float)mousePosY;
	s_OldCursorPosition = s_CursorPosition;

	glfwSetScrollCallback(currentWindow, [](GLFWwindow*, double x, double y) noexcept {
			s_Scroll.X = (float)x;
			s_Scroll.Y = (float)y;
		});
	glfwSetCursorPosCallback(currentWindow, [](GLFWwindow*, double x, double y) noexcept {
			s_CursorPosition.X = (float)x;
			s_CursorPosition.Y = (float)y;
		});
	glfwSetKeyCallback(currentWindow, [](GLFWwindow*, int key, int scancode, int action, int mods) noexcept {
			s_KeysDown[key] = (bool)action;
		});
	glfwSetMouseButtonCallback(currentWindow, [](GLFWwindow*, int button, int action, int mods) noexcept {
			s_MouseButtonsDown[button] = (bool)action;
		});
}

void Reality::GlfwInput::PollEvents() const {
	s_OldCursorPosition = s_CursorPosition;
	glfwPollEvents();
}

void Reality::GlfwInput::WaitEvents() const {
	s_OldCursorPosition = s_CursorPosition;
	glfwWaitEvents();
}

bool Reality::GlfwInput::GetKeyDown(int keycode) const {
	return s_KeysDown[keycode];
}

bool Reality::GlfwInput::GetKeyUp(int keycode) const {
	return s_KeysDown[keycode];
}

bool Reality::GlfwInput::GetMouseButton(int button) const {
	return s_MouseButtonsDown[button];
}

Reality::Vector2 Reality::GlfwInput::GetCursorPos() const {
	return s_CursorPosition;
}

Reality::Vector2 Reality::GlfwInput::GetRelativeMousePos() const {
	return s_CursorPosition - s_OldCursorPosition;
}

Reality::Vector2 Reality::GlfwInput::GetMouseScroll() const {
	return s_Scroll;
}

void Reality::GlfwInput::SetCursorPos(float x, float y) const {
	glfwSetCursorPos(glfwGetCurrentContext(), (double)x, (double)y);
}