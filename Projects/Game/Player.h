// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Core/Platform.h"
#include "Gameplay/Component/MonoBehaviour.h"

class RE_GAME Player : public reality::CMonoBehaviour
{
	RE_COMPONENT(Player, CMonoBehaviour)

	virtual void Update() override;

private:
	template <class Archive>
	void serialize(Archive& archive) {}
};