#pragma once

class DrugNova :public BaseState
{
public:
	DrugNova();
	BaseState* Action(Enemy* _enemy, GameScene* _gameScene)override;

private:
	float m_damege;
	float m_attackRange;
	float m_novaSize;
	float m_sizeChangePower;
	float m_novaAlpha;
	float m_alphaChangePower;

	int m_changeSizeWaitTime;

	float expandSizePower = 0.1f;
	float shrinkSizePower = -0.05f;;
};