#include "GameManager.h"

#include"Application/GameObject/Chara/Player/Player.h"

GameManager::GameManager()
{
	mp_player = std::make_unique<Player>();
	mp_player->Init();   // •K—v‚È‚ç
}
