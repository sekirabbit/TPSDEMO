#pragma once

class Stay :public BaseState
{
public:
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;
private:
	float m_lastTime;
};