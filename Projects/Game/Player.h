// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Gameplay/Component/MonoBehaviour.h"

class RE_GAME Player : public Reality::CMonoBehaviour
{
	RE_COMPONENT(Player, Reality::CMonoBehaviour);

	virtual void Update() override;
};