#pragma once

class Weak :public BaseState
{
public:
	Weak();
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;

private:
	int m_weakTime;
};
