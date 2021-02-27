// Copyright Reality Engine. All Rights Reserved.

#include "Editor.h"

#ifdef RE_WINDOWS_PLATFORM
extern "C" {
	// Ensure the use of the NVIDIA graphic card if available
	__declspec(dllexport) auto NvOptimusEnablement{ 1 }; 

	// Ensure the use of the AMD graphic card if available
	__declspec(dllexport) auto AmdPowerXpressRequestHighPerformance{ 1 };
}
#endif

int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int) {
	reality::editor::Editor editor;
}