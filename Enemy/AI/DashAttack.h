#pragma once

class DashAttack :public BaseState
{
public:
	DashAttack();
	virtual BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;

protected:
	float m_moveDis;
	float m_moveAfterDis;
	float m_speed;
	float m_maxSpeed;
	float m_acceleration;
	float m_damege;
};