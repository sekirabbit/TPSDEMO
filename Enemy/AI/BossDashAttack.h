#pragma once

class BossDashAttack :public DashAttack
{
public:
	BossDashAttack();
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;
};