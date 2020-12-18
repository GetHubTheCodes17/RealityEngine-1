// Copyright Reality Engine. All Rights Reserved.

#include "Windowing/GlfwWindow.h"

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include "Core/Tools/Logger.h"

reality::GlfwWindow::GlfwWindow(const WindowSettings& settings) {
	if (!s_Instances) {
		const auto success{ glfwInit() };
		RE_ASSERT(success != GLFW_FALSE, "Cannot compile glfw library");
	}
	s_Instances++;

	glfwSetErrorCallback([](int error, const char* description) noexcept {
			RE_LOG_ERROR("Error %s, code %d", description, error);
		}
	);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, (int)settings.Samples);
#if RE_DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
	m_Window = glfwCreateWindow(settings.Width, settings.Height, settings.Title, nullptr, nullptr);
	RE_ASSERT(m_Window, "Cannot create glfw window");
	glfwSetWindowUserPointer(m_Window, this);

	SetActiveWindow();
	SetVSync(1);
}

reality::GlfwWindow::~GlfwWindow() {
	glfwDestroyWindow(m_Window);
	s_Instances--;

	if (!s_Instances) {
		glfwTerminate();
	}
}

void reality::GlfwWindow::Minimize() const {
	glfwIconifyWindow(m_Window);
}

void reality::GlfwWindow::Maximize() const {
	glfwMaximizeWindow(m_Window);
}

void reality::GlfwWindow::HideCursor() const {
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void reality::GlfwWindow::HideAndLockCursor() const {
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void reality::GlfwWindow::ShowCursor() const {
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void reality::GlfwWindow::Close() const {
	glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

void reality::GlfwWindow::Focus() const {
	glfwFocusWindow(m_Window);
}

void reality::GlfwWindow::SwapBuffers() const {
	glfwSwapBuffers(m_Window);
}

bool reality::GlfwWindow::IsRunning() const {
	return glfwWindowShouldClose(m_Window) == GLFW_FALSE;
}

reality::Vector2 reality::GlfwWindow::GetPos() const {
	auto x{ 0 }, y{ 0 };
	glfwGetWindowPos(m_Window, &x, &y);
	return { (float)x, (float)y };
}

reality::Vector2 reality::GlfwWindow::GetSize() const {
	auto width{ 0 }, height{ 0 };
	glfwGetWindowSize(m_Window, &width, &height);
	return { (float)width, (float)height };
}

float reality::GlfwWindow::GetOpacity() const {
	return glfwGetWindowOpacity(m_Window);
}

void* reality::GlfwWindow::GetHandle() const {
	return m_Window;
}

void reality::GlfwWindow::SetTitle(const char* title) const {
	glfwSetWindowTitle(m_Window, title);
}

void reality::GlfwWindow::SetPos(Vector2 position) const {
	glfwSetWindowPos(m_Window, (int)position.X, (int)position.Y);
}

void reality::GlfwWindow::SetSize(Vector2 size) const {
	glfwSetWindowSize(m_Window, (int)size.X, (int)size.Y);
	if (m_ResizeCallback) {
		m_ResizeCallback(size);
	}
}

void reality::GlfwWindow::SetOpacity(float opacity) const {
	glfwSetWindowOpacity(m_Window, opacity);
}

void reality::GlfwWindow::SetAspectRatio(int num, int denom) const {
	glfwSetWindowAspectRatio(m_Window, num, denom);
}

void reality::GlfwWindow::SetActiveWindow() const {
	glfwMakeContextCurrent(m_Window);
}

void reality::GlfwWindow::SetVSync(int interval) const {
	glfwSwapInterval(interval);
}

void reality::GlfwWindow::SetSizeCallback(std::function<void(Vector2)> func) {
	m_ResizeCallback = func;
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) noexcept {
			reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_ResizeCallback({ (float)width, (float)height });
		}
	);
}

void reality::GlfwWindow::SetDropCallback(std::function<void(int, const char*[])> func) {
	m_DropCallback = func;
	glfwSetDropCallback(m_Window, [](GLFWwindow* window, int pathCount, const char* paths[]) noexcept {
			reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_DropCallback(pathCount, paths);
		}
	);
}