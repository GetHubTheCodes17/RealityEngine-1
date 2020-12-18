// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Rendering/Opengl/GLModel.h"
#include "Rendering/Opengl/GLMesh.h"
#include "Model.h"

namespace reality::loader {
	GLModel ConvertModel(GLMeshSettings& properties, const Model& resource);
}