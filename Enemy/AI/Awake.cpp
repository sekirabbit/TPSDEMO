#include "Headers.h"

BaseState* Awake::Action(Enemy* _enemy, GameScene* _gameScene)
{
	_enemy->SetStateType(EnemyState::Awake);
	auto se = _gameScene->GetSound().GetEnemyAwakeSEInst();
	se->SetPos(_enemy->GetPos());
	se->Play(false);
	_enemy->SetStateType(EnemyState::Track);
	return new Track();
}