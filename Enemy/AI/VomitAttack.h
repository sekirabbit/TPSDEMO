#pragma once

class VomitAttack :public BaseState
{
public:
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;

private:
	float m_waitTime = 10.0f;
};