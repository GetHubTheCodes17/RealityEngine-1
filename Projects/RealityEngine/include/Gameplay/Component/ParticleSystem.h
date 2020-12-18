// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"

namespace reality {
	struct CParticleSystem : Component {
		RE_COMPONENT(CParticleSystem, Component)

		class GLParticleSystem* System{};
	};
}