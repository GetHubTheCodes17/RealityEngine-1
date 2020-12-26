// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"
#include "Core/Maths/MathsSerializer.h"

namespace reality {
	struct CLight : Component {
		RE_COMPONENT(CLight, Component)
		enum class Type { Directional, Point, Spot };
		enum class Shadow { None, Soft };

		float Range{ 20.f }, SpotAngle{ 30.f }, Intensity{ 1.f };
		Vector4 Color{ Vector4::One };
		Type Type{ Type::Directional };
		Shadow Shadow{ Shadow::None };

	private:
		template <class Archive>
		void serialize(Archive& archive) {
			archive(CEREAL_NVP(Range));
			archive(CEREAL_NVP(SpotAngle));
			archive(CEREAL_NVP(Intensity));
			archive(CEREAL_NVP(Color));
			archive(CEREAL_NVP(Type));
			archive(CEREAL_NVP(Shadow));
		}
	};
}

CEREAL_REGISTER_TYPE_WITH_NAME(reality::CLight, "Light");
CEREAL_REGISTER_POLYMORPHIC_RELATION(reality::Component, reality::CLight)