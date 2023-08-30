#pragma once

class Awake :public BaseState
{
public:
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;
};

