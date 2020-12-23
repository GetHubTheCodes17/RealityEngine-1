// Copyright Reality Engine. All Rights Reserved.

#include "Engine.h"

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

reality::GameEngine::GameEngine() {
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
}

reality::GameEngine::~GameEngine() {
	delete g_ResourceLocator;
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

RE_CORE reality::PlayerPref* reality::g_PlayerPref{};
RE_CORE reality::Randomizer* reality::g_Randomizer{};
RE_CORE reality::Logger* reality::g_Logger{};
RE_CORE reality::SceneManager* reality::g_SceneManager{};
RE_CORE reality::AudioEngine* reality::g_AudioEngine{};
RE_CORE reality::GLShaderHelper* reality::g_ShaderHelper{};
RE_CORE reality::GLDebugDrawing* reality::g_DebugDrawing{};
RE_CORE reality::GLMeshHelper* reality::g_MeshHelper{};
RE_CORE reality::IO* reality::g_Io{};

RE_CORE reality::ResourceLocator* reality::g_ResourceLocator{};

const reality::Quaternion reality::Quaternion::Identity{ 0.f, 0.f, 0.f, 1.f };

const reality::Matrix4 reality::Matrix4::Zero{};
const reality::Matrix4 reality::Matrix4::Identity{
	 1.f, 0.f, 0.f, 0.f,
	 0.f, 1.f, 0.f, 0.f,
	 0.f, 0.f, 1.f, 0.f,
	 0.f, 0.f, 0.f, 1.f  
};

const reality::Vector4 reality::Vector4::Back{ 0.f, 0.f, -1.f, 1.f };
const reality::Vector4 reality::Vector4::Down{ 0.f, -1.f, 0.f, 1.f };
const reality::Vector4 reality::Vector4::Forward{ 0.f, 0.f, 1.f, 1.f };
const reality::Vector4 reality::Vector4::Left{ -1.f, 0.f, 0.f, 1.f };
const reality::Vector4 reality::Vector4::One{ 1.f, 1.f, 1.f, 1.f };
const reality::Vector4 reality::Vector4::Right{ 1.f, 0.f, 0.f, 1.f };
const reality::Vector4 reality::Vector4::Up{ 0.f, 1.f, 0.f, 1.f };
const reality::Vector4 reality::Vector4::Zero{ 0.f, 0.f, 0.f, 0.f };

const reality::Vector3 reality::Vector3::Back{ 0.f, 0.f, -1.f };
const reality::Vector3 reality::Vector3::Down{ 0.f, -1.f, 0.f };
const reality::Vector3 reality::Vector3::Forward{ 0.f, 0.f, 1.f };
const reality::Vector3 reality::Vector3::Left{ -1.f, 0.f, 0.f };
const reality::Vector3 reality::Vector3::One{ 1.f, 1.f, 1.f };
const reality::Vector3 reality::Vector3::Right{ 1.f, 0.f, 0.f };
const reality::Vector3 reality::Vector3::Up{ 0.f, 1.f, 0.f };
const reality::Vector3 reality::Vector3::Zero{ 0.f, 0.f, 0.f };

const reality::Vector2 reality::Vector2::Down{ 0.f, -1.f };
const reality::Vector2 reality::Vector2::Left{ -1.f, 0.f };
const reality::Vector2 reality::Vector2::One{ 1.f, 1.f };
const reality::Vector2 reality::Vector2::Right{ 1.f, 0.f };
const reality::Vector2 reality::Vector2::Up{ 0.f, 1.f };
const reality::Vector2 reality::Vector2::Zero{ 0.f, 0.f };