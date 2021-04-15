// Copyright Reality Engine. All Rights Reserved.

#include "Player.h"

#include "Core/Tools/Logger.h"

void Player::Update()
{
	int life = 13;
	RE_LOG_INFO("Life : %d", life);
}

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Player>("Player")
        .method("Instantiate", &Player::Instantiate);
}