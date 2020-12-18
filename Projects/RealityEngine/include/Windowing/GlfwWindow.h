// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Window.h"

struct GLFWwindow;

namespace reality {
	class RE_CORE GlfwWindow final : public Window {
	public:
		explicit GlfwWindow(const WindowSettings& settings = {});
		~GlfwWindow() override;

		void Minimize() const override;
		void Maximize() const override;
		void HideCursor() const override;
		void HideAndLockCursor() const override;
		void ShowCursor() const override;
		void Close() const override;
		void Focus() const override;
		void SwapBuffers() const override;
		bool IsRunning() const override;
		Vector2 GetPos() const override;
		Vector2 GetSize() const override;
		float GetOpacity() const override;
		void* GetHandle() const override;
		void SetTitle(const char* title) const override;
		void SetPos(Vector2 position) const override;
		void SetSize(Vector2 size) const override;
		void SetOpacity(float opacity) const override;
		void SetAspectRatio(int num, int denom) const override;
		void SetActiveWindow() const override;
		void SetVSync(int interval) const override;
		void SetSizeCallback(std::function<void(Vector2 size)> func) override;
		void SetDropCallback(std::function<void(int pathCount, const char* paths[])>) override;

	private:
		inline static auto s_Instances{ 0u };

		GLFWwindow* m_Window{};
	};
}