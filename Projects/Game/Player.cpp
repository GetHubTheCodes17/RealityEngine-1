// Copyright Reality Engine. All Rights Reserved.

#include "Player.h"
#include "Core/Tools/Logger.h"

void Player::Update()
{
	int data{ 42 };
	RE_LOG_INFO("Data : %d", data);
}

REFLECT(Player)