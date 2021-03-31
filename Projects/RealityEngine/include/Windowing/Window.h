// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <functional>

#include "Core/Maths/Vector2.h"

namespace Reality {
	struct WindowSettings {
		const int Width{ RE_WINDOW_WIDTH }, Height{ RE_WINDOW_HEIGHT };
		std::string_view Title{ "Untitled" };
		const unsigned Samples{ 4 };
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual void Minimize() const = 0;
		virtual void Maximize() const = 0;
		virtual void HideCursor() const = 0;
		virtual void HideAndLockCursor() const = 0;
		virtual void ShowCursor() const = 0;
		virtual void Close() const = 0;
		virtual void Focus() const = 0;
		virtual void SwapBuffers() const = 0;
		virtual void SetTitle(const char* title) const = 0;
		virtual void SetPos(Vector2 position) const = 0;
		virtual void SetSize(Vector2 size) const = 0;
		virtual void SetOpacity(float opacity) const = 0;
		virtual void SetAspectRatio(int num, int denom) const = 0;
		virtual void SetActiveWindow() const = 0;
		virtual void SetVSync(int interval) const = 0;
		virtual void SetSizeCallback(std::function<void(Vector2 size)> func) = 0;
		virtual void SetDropCallback(std::function<void(int pathCount, const char* paths[])>) = 0;
		virtual bool IsRunning() const = 0;
		virtual Vector2 GetPos() const = 0;
		virtual Vector2 GetSize() const = 0;
		virtual float GetOpacity() const = 0;
		virtual void* GetHandle() const = 0;

	protected:
		std::function<void(Vector2)> m_ResizeCallback;
		std::function<void(int, const char* [])> m_DropCallback;
	};
}