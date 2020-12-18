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

	g_MeshManager = new std::unordered_map<std::string, reality::GLMesh>;
	g_MaterialManager = new std::unordered_map<std::string, reality::GLMaterial>;
	g_TextureManager = new ResourceManager<GLTexture, TextureSettings, GLTextureSettings, Texture>{ "Resources/Textures.json" };
	g_ModelManager = new ResourceManager<GLModel, ModelSettings, GLMeshSettings, Model>{ "Resources/Models.json" };
	g_SkyboxManager = new ResourceManager<GLCubeMap, SkyboxSettings, GLCubeMapSettings, Skybox>{ "Resources/Skyboxes.json" };
	g_ShaderManager = new ResourceManager<GLShader, ShaderSettings, GLShaderSettings, Shader>{ "Resources/Shaders.json" };
	g_FontManager = new ResourceManager<GLFont, FontSettings, GLFontSettings, Font>{ "Resources/Fonts.json" };
}

reality::GameEngine::~GameEngine() {
	delete g_ModelManager;
	delete g_MeshManager;
	delete g_MaterialManager;
	delete g_TextureManager;
	delete g_FontManager;
	delete g_ShaderManager;
	delete g_SkyboxManager;
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

RE_CORE std::unordered_map<std::string, reality::GLMesh>* reality::g_MeshManager{};
RE_CORE std::unordered_map<std::string, reality::GLMaterial>* reality::g_MaterialManager{};

RE_CORE reality::ResourceManager<reality::GLModel, reality::ModelSettings, reality::GLMeshSettings,
	reality::Model>* reality::g_ModelManager{};
RE_CORE reality::ResourceManager<reality::GLCubeMap, reality::SkyboxSettings, reality::GLCubeMapSettings,
	reality::Skybox>* reality::g_SkyboxManager{};
RE_CORE reality::ResourceManager<reality::GLTexture, reality::TextureSettings, reality::GLTextureSettings,
	reality::Texture>* reality::g_TextureManager{};
RE_CORE reality::ResourceManager<reality::GLShader, reality::ShaderSettings, reality::GLShaderSettings,
	reality::Shader>* reality::g_ShaderManager{};
RE_CORE reality::ResourceManager<reality::GLFont, reality::FontSettings, reality::GLFontSettings,
	reality::Font>* reality::g_FontManager{};

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