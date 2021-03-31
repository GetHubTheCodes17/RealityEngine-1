// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"

namespace Reality {
	struct CParticleSystem : Component {
		RE_COMPONENT(CParticleSystem, Component)

		class GLParticleSystem* System{};

	private:
		template <class Archive>
		void serialize(Archive& archive) {
		}
	};
}

CEREAL_REGISTER_TYPE_WITH_NAME(Reality::CParticleSystem, "ParticleSystem");
CEREAL_REGISTER_POLYMORPHIC_RELATION(Reality::Component, Reality::CParticleSystem)