// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"

namespace Reality {
	struct CMeshFilter : Component {
		RE_COMPONENT(CMeshFilter, Component)

	private:
		template <class Archive>
		void serialize(Archive& archive) {
		}
	};
}

CEREAL_REGISTER_TYPE_WITH_NAME(Reality::CMeshFilter, "MeshFilter");
CEREAL_REGISTER_POLYMORPHIC_RELATION(Reality::Component, Reality::CMeshFilter)