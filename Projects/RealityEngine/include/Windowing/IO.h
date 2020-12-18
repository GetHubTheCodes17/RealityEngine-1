// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <memory>

#include "Window.h"
#include "Input.h"
#include "Time.h"

namespace reality {
	class IO final {
	public:
		std::unique_ptr<Window> Window;
		std::unique_ptr<Input> Input;
		std::unique_ptr<Time> Time;

		void Update();
	};

	RE_CORE extern IO* g_Io;
}

inline void reality::IO::Update() {
	Input->PollEvents();
	Window->SwapBuffers();
	Time->Update();
}