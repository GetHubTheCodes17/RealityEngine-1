// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"

namespace reality {
	struct CMeshRenderer : Component {
		RE_COMPONENT(CMeshRenderer, Component)

		const struct GLModel* Model{};
	};
}