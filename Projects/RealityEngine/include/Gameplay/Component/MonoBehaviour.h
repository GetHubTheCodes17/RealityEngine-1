// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Behaviour.h"

namespace reality {
	struct CMonoBehaviour : CBehaviour {
		virtual ~CMonoBehaviour() = 0;

		virtual void Awake() {};
		virtual void Start() {};
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void OnEnable() {};
		virtual void OnDisable() {};
		virtual void SetEnable(bool enabled);
	};
}

inline reality::CMonoBehaviour::~CMonoBehaviour() = default;

inline void reality::CMonoBehaviour::SetEnable(bool enabled) {
	if (!Enabled && enabled) {
		OnEnable();
	}
	else if (Enabled && !enabled) {
		OnDisable();
	}
	Enabled = enabled;
}