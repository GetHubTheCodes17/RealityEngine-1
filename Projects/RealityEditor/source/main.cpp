// Copyright Reality Engine. All Rights Reserved.

#include "Editor.h"
#include "Core/Tools/Leaker.h"

extern "C" {
	__declspec(dllexport) auto NvOptimusEnablement{ 1 };
	__declspec(dllexport) auto AmdPowerXpressRequestHighPerformance{ 1 };
}

int WinMain()
{
	reality::Leaker leaker;
	reality::Editor editor;
	editor.Run();
}