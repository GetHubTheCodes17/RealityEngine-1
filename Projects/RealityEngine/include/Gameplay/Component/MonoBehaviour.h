// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Behaviour.h"

namespace Reality {
	struct CMonoBehaviour : CBehaviour {
		RE_INTERFACE(CBehaviour)
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

inline Reality::CMonoBehaviour::~CMonoBehaviour() = default;

inline void Reality::CMonoBehaviour::SetEnable(bool enabled) {
	if (!Enabled && enabled) {
		OnEnable();
	}
	else if (Enabled && !enabled) {
		OnDisable();
	}
	Enabled = enabled;
}

#include <rttr/registration>

#define REFLECT(type) \
RTTR_REGISTRATION \
{ \
	rttr::registration::class_<type>(#type).method("Instantiate", &type::Instantiate); \
} 