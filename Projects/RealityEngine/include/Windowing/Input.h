// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Maths/Vector2.h"
#include "KeyCodes.h"

namespace Reality {
	class Input {
	public:
		virtual ~Input() = default;

		virtual void PollEvents() const = 0;
		virtual void WaitEvents() const = 0;
		virtual bool GetKeyDown(int key) const = 0;
		virtual bool GetKeyUp(int key) const = 0;
		virtual bool GetMouseButton(int button) const = 0;
		virtual Vector2 GetCursorPos() const = 0;
		virtual Vector2 GetRelativeMousePos() const = 0;
		virtual Vector2 GetMouseScroll() const = 0;
		virtual void SetCursorPos(float x, float y) const = 0;
	};
}