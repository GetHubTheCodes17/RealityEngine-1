// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Rendering/Opengl/GLModel.h"

namespace Reality::loader {
	GLModel ConvertModel(GLMeshSettings& properties, const Model& resource);
}