// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Tools/Randomizer.h"
#include "Core/Tools/Logger.h"
#include "Windowing/IO.h"
#include "Windowing/GlfwInput.h"
#include "Windowing/GlfwTime.h"
#include "Windowing/GlfwWindow.h"
#include "Gameplay/PlayerPref.h"
#include "Gameplay/ComponentSystem.h"
#include "Rendering/Opengl/GLContext.h"
#include "Rendering/Opengl/GLShaderHelper.h"
#include "Rendering/Opengl/GLDebugDrawing.h"
#include "Rendering/Opengl/GLMeshHelper.h"
#include "Resources/ResourceLocator.h"
#include "Gameplay/SceneManager.h"
#include "Audio/AudioEngine.h"

namespace reality {
	class RE_CORE GameEngine final {
	public:
		GameEngine();
		~GameEngine();
	};
}