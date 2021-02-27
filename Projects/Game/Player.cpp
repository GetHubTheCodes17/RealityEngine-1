// Copyright Reality Engine. All Rights Reserved.

#include "Player.h"

#include "Gameplay/GameObject.h"
#include "Core/Tools/Logger.h"

void Player::Update()
{
	RE_LOG_INFO("Hello Guys\n");
}

#include <rttr/registration>

RTTR_PLUGIN_REGISTRATION
{
    using namespace rttr;

    registration::class_<Player>("Player")
        .method("Instantiate", &Player::Instantiate);
}

CEREAL_REGISTER_TYPE_WITH_NAME(Player, "Player");
CEREAL_REGISTER_POLYMORPHIC_RELATION(reality::CMonoBehaviour, Player)