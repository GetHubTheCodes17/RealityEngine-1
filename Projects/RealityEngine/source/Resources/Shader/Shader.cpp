// Copyright Reality Engine. All Rights Reserved.

#include "Resources/Shader/Shader.h"

#include <fstream>

#include "Core/Tools/Logger.h"

reality::Shader::Shader(ShaderSettings settings) {
	auto GetContentFromFile = [](const auto& source) -> std::string {
		if (std::ifstream file{ source }) {
			return { std::istreambuf_iterator<char>{ file }, std::istreambuf_iterator<char>{} };
		}
		RE_LOG_WARNING("Cannot load the Shader %s", source.c_str());
		return {};
	};

	if (!settings.VertexPath.empty()) {
		VertexSource = GetContentFromFile(settings.VertexPath);
	}
	if (!settings.FragmentPath.empty()) {
		FragmentSource = GetContentFromFile(settings.FragmentPath);
	}
	if (!settings.GeometryPath.empty()) {
		GeometrySource = GetContentFromFile(settings.GeometryPath);
	}
}