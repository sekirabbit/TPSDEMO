#include "Headers.h"

BaseState* BossAngry::Action(Enemy* _enemy, GameScene* _gameScene)
{
	_enemy->SetStateType(EnemyState::Nova);
	return new DrugNova();
}