#pragma once

class BossAngry :public BaseState
{
public:
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;
};