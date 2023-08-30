#pragma once

class AttackWait :public BaseState
{
public:
	AttackWait();
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;
private:
	float m_lastTime;
	int m_bloodNum;
	int m_attackModel;
};