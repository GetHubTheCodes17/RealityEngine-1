// Copyright Reality Engine. All Rights Reserved.

#include "Editor.h"

extern "C" {
	__declspec(dllexport) auto NvOptimusEnablement{ 1 };
	__declspec(dllexport) auto AmdPowerXpressRequestHighPerformance{ 1 };
}

int WinMain() {
	reality::Editor editor;
}