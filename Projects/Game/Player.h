// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Gameplay/Component/MonoBehaviour.h"

using namespace Reality;

class RE_GAME Player : public CMonoBehaviour
{
	RE_COMPONENT(Player, CMonoBehaviour);

	virtual void Update() override;
};