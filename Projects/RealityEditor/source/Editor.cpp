// Copyright Reality Engine. All Rights Reserved.

#include "Editor.h"

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "Gameplay/ComponentSystem.h"
#include "Gameplay/SceneSerializer.h"

reality::Editor::Editor() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	editorTheme::RealityStyle();
	ImGui::GetIO().Fonts->AddFontFromFileTTF("../../Projects/RealityEditor/Config/LucidaGrande.ttf", 12.f);
	ImGui::GetIO().IniFilename = "Config/imgui.ini";
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
	ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(g_Io->Window->GetHandle()), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	g_Io->Window->SetTitle("Reality Engine");
	g_Io->Window->SetPos({ 250.f, 150.f });
	g_Logger->Callback = [this](const char* msg) { m_Log.AddLog(msg); };
	g_Io->Window->SetDropCallback([this](int count, const char** paths) {
		for (auto i{ 0 }; i < count; ++i) {
			m_Assets.DropResource(paths[i]);
		}
	});
	g_ResourceManager = new ResourceManager;
	auto& scene{ g_SceneManager->CreateScene("Scene0") };
	SceneSerializer::Load("Resources/Scenes.json", scene);
}

reality::Editor::~Editor() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	SceneSerializer::Save("Resources/Scenes.json", *g_SceneManager->ActiveScene);
}

void reality::Editor::Run() {
	while (g_Io->Window->IsRunning() && !g_Io->Input->GetKeyDown(keycode::RE_KEY_ESCAPE)) {
		UpdateIo();
		g_ResourceManager->Update();

		if (auto activeScene{ g_SceneManager->ActiveScene }) {
			activeScene->FindGameObject("Camera")->Transform.SetPosition(m_Camera.Position);
			activeScene->Update();
			m_ComponentSystem.UpdateTransforms(*activeScene);
			m_ComponentSystem.UpdateCameras(*activeScene, m_ViewportSize);
			m_ComponentSystem.UpdateLights(*activeScene);
		}

		Update();

		if (g_SceneManager->ActiveScene) {
			Render();
		}
		g_Io->Update();
	}
}

void reality::Editor::CreateDefaultScene() const {
	g_ResourceManager->Skyboxes.Load("Saturne", {
		"Skyboxes/saturne/Left.png", "Skyboxes/saturne/Right.png", "Skyboxes/saturne/Up.png",
		"Skyboxes/saturne/Down.png", "Skyboxes/saturne/Front.png", "Skyboxes/saturne/Back.png"
	});
	g_ResourceManager->Fonts.Load("Arial", { "Fonts/Arial.ttf" });

	auto& scene{ g_SceneManager->CreateScene("Scene0") };

	auto& camera{ scene.CreateGameObject("Camera") };
	camera.AddComponent<CCamera>();

	auto& g0{ scene.CreateGameObject("Nanosuit") };
	g0.AddComponent<CMeshRenderer>()->SetModel("nanosuit");
	g0.Transform.Translate({ 0.f, -3.5f, 3.f });
	g0.Transform.Rotate({ 0.f, 180.f, 0.f });
	g0.Transform.SetScale(Vector3{ 0.15f });

	auto& g2{ scene.CreateGameObject("Child1") };
	auto& g1{ scene.CreateGameObject("Parent1") };
	g2.SetParent(g1);

	g2.Transform.Translate({ 0.f, -2.f, 7.f });
	g2.AddComponent<CMeshRenderer>()->SetModel("SciFi_Fighter");
	g2.Transform.Rotate({ 0.f, 180.f, 0.f });
	g2.Transform.SetScale(Vector3{ 0.1f });

	auto& c3{ scene.CreateGameObject("Child11") };
	c3.SetParent(g2);
	c3.Transform.Translate({ 0.f, -2.f, 7.f });
	c3.AddComponent<CMeshRenderer>()->SetModel("SciFi_Fighter");
	c3.Transform.Rotate({ 0.f, 180.f, 0.f });
	c3.Transform.SetScale(Vector3{ 0.6f });

	auto& g3{ scene.CreateGameObject("House") };
	g3.AddComponent<CMeshRenderer>()->SetModel("fantasy_game_inn");
	g3.Transform.Translate({ 1.1f, -2.2f, 3.5f });

	auto& g4{ scene.CreateGameObject("Crytek") };
	g4.AddComponent<CMeshRenderer>()->SetModel("crytek");
	g4.Transform.SetScale(Vector3{ 0.03f });
	g4.Transform.Rotate({ 0.f, 90.f, 0.f });
	g4.Transform.Translate({ 0.f, -4.f, 0.f });

	auto& g5{ scene.CreateGameObject("DirLight") };
	g5.Transform.SetRotation({ 122.f, 180.f });
	g5.AddComponent<CLight>()->Shadow = CLight::Shadow::Soft;

	auto& g6{ scene.CreateGameObject("PointLight") };
	g6.Transform.Translate({ 0.f, 0.f, 20.f });
	g6.AddComponent<CLight>()->Type = CLight::Type::Point;
	g6.GetComponent<CLight>()->Color = Vector4::Right;

	auto& g7 = scene.CreateGameObject("ParticleSystem");
	g7.Transform.Translate({ 0.f, -2.f, 20.f });
	g7.Transform.Rotate({ 90.f, 0.f, 0.f });
}

void reality::Editor::Render() const {
	m_Pipeline.BeginShadowPass();
	m_ComponentSystem.UpdateMeshesShadow(*g_SceneManager->ActiveScene);

	GLContext::SetViewMatrix(m_Camera.GetViewMatrix());
	m_Pipeline.BeginScenePass(g_ResourceManager->Skyboxes.Get("Saturne"));
	m_ComponentSystem.UpdateMeshes(*g_SceneManager->ActiveScene);
	m_ComponentSystem.UpdateParticles(*g_SceneManager->ActiveScene);

	// Draw Debug Cube with Default Material
	GLContext::SetModelMatrix(Matrix4::Translate({ 2.f, 0.f, 2.f }));
	g_MeshHelper->Cube.Material->Bind();
	g_MeshHelper->Cube.Draw();

	// Draw Debug Text
	g_ResourceManager->Fonts.Get("Arial")->Draw("Reality Engine !", { 0.1f, 0.1f, 0.5f, 0.5f }, m_ViewportSize);

	m_Pipeline.BeginPostProcess();
	m_Pipeline.GetDefaultPass().Bind();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void reality::Editor::Update() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();
	ImGui::SliderFloat("Camera Speed", &m_Camera.MovementSpeed, 0.1f, 50.f);
	m_Dock.Begin();
	ImGui::ShowDemoWindow();
	m_Assets.Draw();
	m_Log.Draw();
	m_Menu.Draw();
	m_Hierarchy.Draw(*g_SceneManager->ActiveScene);
	m_Inspector.Draw(m_Hierarchy.GetCurrents());
	m_Scene.Draw(m_Pipeline, m_Camera, m_ViewportSize, m_Hierarchy.GetCurrents());
	m_Dock.End();
}

void reality::Editor::UpdateIo() {
	if (g_Io->Input->GetKeyDown(keycode::RE_KEY_F)) {
		if (!m_Hierarchy.GetCurrents().empty()) {
			m_Camera.Focus(m_Hierarchy.GetCurrents().back());
		}
	}
	m_Camera.UpdateFocus();

	if (g_Io->Input->GetMouseButton(keycode::RE_MOUSE_BUTTON_RIGHT)) {
		if (!EnabledCamera && m_Scene.IsHovered()) {
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
			g_Io->Window->HideAndLockCursor();
			EnabledCamera = true;
		}
		if (EnabledCamera) {
			m_Camera.Update();
		}
	}
	else {
		if (EnabledCamera) {
			ImGui::GetIO().ConfigFlags ^= ImGuiConfigFlags_NoMouse;
			g_Io->Window->ShowCursor();
			EnabledCamera = false;
		}
	}
}