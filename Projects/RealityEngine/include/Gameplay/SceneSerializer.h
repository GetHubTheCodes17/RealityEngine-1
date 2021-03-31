// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/archives/json.hpp>
#include <fstream>

#include "Scene.h"

namespace Reality {
	class SceneSerializer {
	public:
		static void Load(std::string path, Scene& scene);
		static void Save(std::string path, const Scene& scene);
	};
}

inline void Reality::SceneSerializer::Load(std::string path, Scene& scene) {
	if (std::ifstream file{ path }) {
		cereal::JSONInputArchive archive{ file };
		archive(scene);
	}
}

inline void Reality::SceneSerializer::Save(std::string path, const Scene& scene) {
	if (std::ofstream file{ path }) {
		cereal::JSONOutputArchive archive{ file };
		archive(scene);
	}
}