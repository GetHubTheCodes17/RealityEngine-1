// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Component.h"

namespace reality {
	struct CBehaviour : Component {
		RE_INTERFACE(Component)
		bool Enabled{ true };

		virtual ~CBehaviour() = 0;
	};
}

inline reality::CBehaviour::~CBehaviour() = default;