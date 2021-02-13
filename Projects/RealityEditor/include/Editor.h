// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "EditorHierarchy.h"
#include "EditorInspector.h"
#include "EditorDocking.h"
#include "EditorAssets.h"
#include "EditorCamera.h"
#include "EditorTheme.h"
#include "EditorScene.h"
#include "EditorMenu.h"
#include "EditorLog.h"
#include "Engine.h"

namespace reality {
	class Editor final {
	public:
		Editor();
		~Editor();

	private:
		GameEngine m_Engine;
		GLPipeline m_Pipeline;
		Viewport m_Viewport;
		ComponentSystem m_ComponentSystem;
		EditorAssets m_Assets;
		EditorCamera m_Camera;
		EditorLog m_Log;
		EditorMenu m_Menu;
		EditorDocking m_Dock;
		EditorScene m_Scene;
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