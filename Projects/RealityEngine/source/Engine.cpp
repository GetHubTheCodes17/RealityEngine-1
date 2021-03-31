// Copyright Reality Engine. All Rights Reserved.

#include "Engine.h"

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

Reality::GameEngine::GameEngine() {
	g_SceneManager = new SceneManager;
	g_Logger = new Logger;
	g_AudioEngine = new AudioEngine;
	g_Randomizer = new Randomizer;
	g_PlayerPref = new PlayerPref;

	g_Io = new IO;
	g_Io->Window = std::make_unique<GlfwWindow>();
	g_Io->Input = std::make_unique<GlfwInput>();
	g_Io->Time = std::make_unique<GlfwTime>();

	GLContext::Init(reinterpret_cast<GLContext::ProcAddr>(glfwGetProcAddress));
	g_ShaderHelper = new GLShaderHelper;
	g_DebugDrawing = new GLDebugDrawing;
	g_MeshHelper = new GLMeshHelper;
	g_MeshHelper->Quad.Material = g_MeshHelper->Circle.Material = g_MeshHelper->Cube.Material =
		g_MeshHelper->Sphere.Material = &g_MeshHelper->Default;

	g_ResourceManager = new ResourceManager;

	g_Io->Window->SetTitle("Reality Engine");
	g_Io->Window->SetPos({ 250.f, 150.f });

	auto& scene{ g_SceneManager->CreateScene("Scene0") };
	SceneSerializer::Load("Resources/Scenes.json", scene);
}

Reality::GameEngine::~GameEngine() {
	SceneSerializer::Save("Resources/Scenes.json", *g_SceneManager->ActiveScene);

	delete g_ResourceManager;
	delete g_SceneManager;
	delete g_Logger;
	delete g_AudioEngine;
	delete g_ShaderHelper;
	delete g_MeshHelper;
	delete g_DebugDrawing;
	delete g_Randomizer;
	delete g_PlayerPref;
	delete g_Io;
}

void Reality::GameEngine::Update() {
	g_ResourceManager->Update();
}

RE_CORE Reality::PlayerPref* Reality::g_PlayerPref{};
RE_CORE Reality::Randomizer* Reality::g_Randomizer{};
RE_CORE Reality::Logger* Reality::g_Logger{};
RE_CORE Reality::SceneManager* Reality::g_SceneManager{};
RE_CORE Reality::AudioEngine* Reality::g_AudioEngine{};
RE_CORE Reality::GLShaderHelper* Reality::g_ShaderHelper{};
RE_CORE Reality::GLDebugDrawing* Reality::g_DebugDrawing{};
RE_CORE Reality::GLMeshHelper* Reality::g_MeshHelper{};
RE_CORE Reality::IO* Reality::g_Io{};
RE_CORE Reality::ResourceManager* Reality::g_ResourceManager{};

const Reality::Quaternion Reality::Quaternion::Identity{ 0.f, 0.f, 0.f, 1.f };

const Reality::Matrix4 Reality::Matrix4::Zero{};
const Reality::Matrix4 Reality::Matrix4::Identity{
	 1.f, 0.f, 0.f, 0.f,
	 0.f, 1.f, 0.f, 0.f,
	 0.f, 0.f, 1.f, 0.f,
	 0.f, 0.f, 0.f, 1.f  
};

const Reality::Vector4 Reality::Vector4::Back{ 0.f, 0.f, -1.f, 1.f };
const Reality::Vector4 Reality::Vector4::Down{ 0.f, -1.f, 0.f, 1.f };
const Reality::Vector4 Reality::Vector4::Forward{ 0.f, 0.f, 1.f, 1.f };
const Reality::Vector4 Reality::Vector4::Left{ -1.f, 0.f, 0.f, 1.f };
const Reality::Vector4 Reality::Vector4::One{ 1.f, 1.f, 1.f, 1.f };
const Reality::Vector4 Reality::Vector4::Right{ 1.f, 0.f, 0.f, 1.f };
const Reality::Vector4 Reality::Vector4::Up{ 0.f, 1.f, 0.f, 1.f };
const Reality::Vector4 Reality::Vector4::Zero{ 0.f, 0.f, 0.f, 0.f };

const Reality::Vector3 Reality::Vector3::Back{ 0.f, 0.f, -1.f };
const Reality::Vector3 Reality::Vector3::Down{ 0.f, -1.f, 0.f };
const Reality::Vector3 Reality::Vector3::Forward{ 0.f, 0.f, 1.f };
const Reality::Vector3 Reality::Vector3::Left{ -1.f, 0.f, 0.f };
const Reality::Vector3 Reality::Vector3::One{ 1.f, 1.f, 1.f };
const Reality::Vector3 Reality::Vector3::Right{ 1.f, 0.f, 0.f };
const Reality::Vector3 Reality::Vector3::Up{ 0.f, 1.f, 0.f };
const Reality::Vector3 Reality::Vector3::Zero{ 0.f, 0.f, 0.f };

const Reality::Vector2 Reality::Vector2::Down{ 0.f, -1.f };
const Reality::Vector2 Reality::Vector2::Left{ -1.f, 0.f };
const Reality::Vector2 Reality::Vector2::One{ 1.f, 1.f };
const Reality::Vector2 Reality::Vector2::Right{ 1.f, 0.f };
const Reality::Vector2 Reality::Vector2::Up{ 0.f, 1.f };
const Reality::Vector2 Reality::Vector2::Zero{ 0.f, 0.f };