// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/archives/json.hpp>
#include <fstream>

#include "Scene.h"

namespace reality {
	class SceneSerializer {
	public:
		static void Load(Scene& scene);
		static void Save(Scene& scene);
	};
}

inline void reality::SceneSerializer::Load(Scene& scene) {
	std::ifstream file{ "Resources/Scenes.json" };
	cereal::JSONInputArchive archive{ file };
	archive(scene);
}

inline void reality::SceneSerializer::Save(Scene& scene) {
	std::ofstream file{ "Resources/Scenes.json" };
	cereal::JSONOutputArchive archive{ file };
	archive(scene);
}