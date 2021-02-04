// Copyright Reality Engine. All Rights Reserved.

#include "Windowing/GlfwInput.h"

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

reality::GlfwInput::GlfwInput(GLFWwindow* window) {
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

void reality::GlfwInput::PollEvents() const {
	s_OldCursorPosition = s_CursorPosition;
	glfwPollEvents();
}

void reality::GlfwInput::WaitEvents() const {
	s_OldCursorPosition = s_CursorPosition;
	glfwWaitEvents();
}

bool reality::GlfwInput::GetKeyDown(int keycode) const {
	return s_KeysDown[keycode];
}

bool reality::GlfwInput::GetKeyUp(int keycode) const {
	return s_KeysDown[keycode];
}

bool reality::GlfwInput::GetMouseButton(int button) const {
	return s_MouseButtonsDown[button];
}

reality::Vector2 reality::GlfwInput::GetCursorPos() const {
	return s_CursorPosition;
}

reality::Vector2 reality::GlfwInput::GetRelativeMousePos() const {
	return s_CursorPosition - s_OldCursorPosition;
}

reality::Vector2 reality::GlfwInput::GetMouseScroll() const {
	return s_Scroll;
}

void reality::GlfwInput::SetCursorPos(float x, float y) const {
	glfwSetCursorPos(glfwGetCurrentContext(), (double)x, (double)y);
}