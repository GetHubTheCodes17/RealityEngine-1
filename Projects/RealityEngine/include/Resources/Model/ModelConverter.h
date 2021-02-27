// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Rendering/Opengl/GLModel.h"

namespace reality::loader {
	GLModel ConvertModel(GLMeshSettings& properties, const Model& resource);
}