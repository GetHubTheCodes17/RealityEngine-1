// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"

namespace reality {
	class RE_CORE Leaker {
	public:
		explicit Leaker(const char* filename = "Logs/MemoryLeaks.txt");
		~Leaker();

	private:
		const char* m_FileName{};
		char* m_TempLeak{};
	};
}