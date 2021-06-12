// Copyright Reality Engine. All Rights Reserved.

#include "Editor.h"

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "Gameplay/ComponentSystem.h"

Reality::Editor::Editor::Editor() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(g_Io->Window->GetHandle()), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	EditorTheme::RealityStyle();
	auto& io{ ImGui::GetIO() };
	io.Fonts->AddFontFromFileTTF("../../Projects/RealityEditor/Config/LucidaGrande.ttf", 12.f);
	io.IniFilename = "Config/imgui.ini";
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	g_Logger->Callback = [this](auto msg) { m_Log.AddLog(msg); };
	g_Io->Window->SetDropCallback([this](auto count, auto paths) {
		for (auto i{ 0 }; i < count; ++i) {
			m_Assets.DropResource(paths[i]);
		}
	});
	Run();
}

Reality::Editor::Editor::~Editor() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Reality::Editor::Editor::Run() {
	// Only one scene is allowed for now
	auto& activeScene{ *g_SceneManager->ActiveScene };
	while (g_Io->Window->IsRunning()) {
		if (g_Io->Input->GetKeyDown(Key::R)) {
			m_HotReload.Reload();
		}

		UpdateIo();
		m_Engine.Update();

		activeScene.Update();
		m_ComponentSystem.UpdateTransforms(activeScene);
		m_ComponentSystem.UpdateCameras(activeScene, m_Viewport.Size);
		m_ComponentSystem.UpdateLights(activeScene);
		m_ComponentSystem.UpdateMonoBehaviours(activeScene);

		Update();
		Render(m_Camera.GetViewMatrix());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		g_Io->Update();
	}
}

void Reality::Editor::Editor::Render(const Matrix4& view) const {
	GLContext::SetViewMatrix(view);

	m_Pipeline.BeginShadowPass();
	m_ComponentSystem.UpdateMeshesShadow(*g_SceneManager->ActiveScene);

	m_Pipeline.BeginScenePass(g_ResourceManager->Skyboxes.Get("Saturne"));
	m_ComponentSystem.UpdateMeshes(*g_SceneManager->ActiveScene);
	m_ComponentSystem.UpdateParticles(*g_SceneManager->ActiveScene, m_Camera.Position);

	m_Pipeline.BeginPostProcess();
	m_Pipeline.GetDefaultPass().Bind();
}

void Reality::Editor::Editor::Update() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();
	UpdateWindows();
}

void Reality::Editor::Editor::UpdateWindows() {
	ImGui::SliderFloat("Camera Speed", &m_Camera.MovementSpeed, 0.1f, 50.f);
	if (ImGui::Button("Hot Reload")) {
		m_HotReload.Reload();
	}

	m_Dock.Begin();
	m_Assets.Draw();
	m_Log.Draw();
	m_Menu.Draw();
	m_Hierarchy.Draw();
	m_Inspector.Draw(m_Hierarchy.GetSelected());
	m_Scene.Draw(m_Hierarchy.GetSelected());
	m_Dock.End();
}

void Reality::Editor::Editor::UpdateIo() {
	if (g_Io->Input->GetKeyDown(Key::F) && !m_Hierarchy.GetSelected().empty()) {
		m_Camera.Focus(m_Hierarchy.GetSelected().back());
	}
	m_Camera.UpdateFocus();

	if (g_Io->Input->GetMouseButton(Key::MouseButton_Right)) {
		if (!m_EnabledCamera && m_Scene.IsHovered()) {
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
			g_Io->Window->HideAndLockCursor();
			m_EnabledCamera = true;
		}
		if (m_EnabledCamera) {
			m_Camera.Update();
		}
	}
	else if (m_EnabledCamera) {
		ImGui::GetIO().ConfigFlags ^= ImGuiConfigFlags_NoMouse;
		g_Io->Window->ShowCursor();
		m_EnabledCamera = false;
	}
}