// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Rendering/Opengl/GLPipeline.h"
#include "Gameplay/ComponentSystem.h"
#include "Core/Maths/Viewport.h"
#include "EditorAssets.h"
#include "EditorCamera.h"
#include "EditorLog.h"
#include "EditorMenu.h"
#include "EditorDocking.h"
#include "EditorScene.h"
#include "EditorHierarchy.h"
#include "EditorInspector.h"
#include "EditorTheme.h"
#include "Core/Tools/HotReload.h"

namespace Reality::Editor {
	class Editor final {
	public:
		Editor();
		~Editor();

	private:
		GameEngine m_Engine;
		HotReload m_HotReload{ g_DllPath };
		GLPipeline m_Pipeline;
		Viewport m_Viewport;
		ComponentSystem m_ComponentSystem;
		EditorAssets m_Assets;
		EditorCamera m_Camera;
		EditorLog m_Log;
		EditorMenu m_Menu;
		EditorDocking m_Dock;
		EditorScene m_Scene{ m_Pipeline, m_Camera, m_Viewport };
		EditorHierarchy m_Hierarchy;
		EditorInspector m_Inspector;
		bool m_EnabledCamera{};

		void Run();
		void Render(const Matrix4& view) const;
		void Update();
		void UpdateWindows();
		void UpdateIo();
	};
}