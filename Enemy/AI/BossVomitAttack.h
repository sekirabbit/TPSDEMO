#pragma once

class BossVomitAttack :public BaseState
{
public:
	BossVomitAttack();
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;

private:
	int m_outCubeNum;
	int m_lastTime;
};