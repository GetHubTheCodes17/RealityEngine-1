// Copyright Reality Engine. All Rights Reserved.

#include "Windowing/GlfwTime.h"

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

float Reality::GlfwTime::GetTime() const {
	return (float)glfwGetTime();
}

void Reality::GlfwTime::SetTime(float time) const {
	glfwSetTime((double)time);
}