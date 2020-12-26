// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/archives/json.hpp>
#include <fstream>

#include "Scene.h"

namespace reality {
	class SceneSerializer {
	public:
		static void Load(std::string_view path, Scene& scene);
		static void Save(std::string_view path, Scene& scene);
	};
}

inline void reality::SceneSerializer::Load(std::string_view path, Scene& scene) {
	std::ifstream file{ path };
	cereal::JSONInputArchive archive{ file };
	archive(scene);
}

inline void reality::SceneSerializer::Save(std::string_view path, Scene& scene) {
	std::ofstream file{ path };
	cereal::JSONOutputArchive archive{ file };
	archive(scene);
}