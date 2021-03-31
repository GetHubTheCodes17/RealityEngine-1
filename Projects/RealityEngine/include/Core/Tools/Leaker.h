// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <string_view>

#include "Core/Platform.h"

namespace Reality {
	class RE_CORE Leaker {
	public:
		explicit Leaker(std::string_view filename = "Logs/MemoryLeaks.txt");
		~Leaker();

	private:
		std::string m_FileName;
		char* m_TempLeak{};
	};
}