// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"

namespace reality {
	struct CMeshFilter : Component {
		RE_COMPONENT(CMeshFilter, Component)

	private:
		template <class Archive>
		void serialize(Archive& archive) {
		}
	};
}

CEREAL_REGISTER_TYPE_WITH_NAME(reality::CMeshFilter, "MeshFilter");
CEREAL_REGISTER_POLYMORPHIC_RELATION(reality::Component, reality::CMeshFilter)