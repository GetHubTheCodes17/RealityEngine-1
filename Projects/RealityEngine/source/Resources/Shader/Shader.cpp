// Copyright Reality Engine. All Rights Reserved.

#include "Resources/Shader/Shader.h"

#include <fstream>

#include "Core/Tools/Logger.h"

reality::Shader::Shader(ShaderSettings settings) {
	if (!settings.VertexPath.empty()) {
		VertexSource = GetShaderFromFile(settings.VertexPath);
	}
	if (!settings.FragmentPath.empty()) {
		FragmentSource = GetShaderFromFile(settings.FragmentPath);
	}
	if (!settings.GeometryPath.empty()) {
		GeometrySource = GetShaderFromFile(settings.GeometryPath);
	}
}

std::string reality::Shader::GetShaderFromFile(std::string_view source) {
	if (std::ifstream file{ source.data() }) {
		return { std::istreambuf_iterator<char>{ file }, std::istreambuf_iterator<char>{} };
	}
	RE_LOG_WARNING("Cannot load the Shader %s", source.data());
	return {};
}

std::string reality::Shader::GetShaderFromEngineFile(std::string_view filename) {
	const std::string path{ "../../Projects/RealityEngine/include/Rendering/GLSLShaders/" };
	return GetShaderFromFile(path + filename.data());
}