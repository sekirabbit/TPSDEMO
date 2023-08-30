#include "Headers.h"

WalkAround::WalkAround()
{
	//前進方向と行動時間を乱数で決める
	m_targetAng = (float)(rand() % 360);
	m_lastTime = (rand() % 5 + 1) * 60;
}

BaseState* WalkAround::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}
	Math::Matrix mat = _enemy->GetMat();
	float ang = TurnToAng(mat, m_targetAng, EnemySetting::turnAng);
	_enemy->SetMat(mat);
	if(ang == 0)
	{
		Math::Matrix transMat;
		transMat = DirectX::XMMatrixTranslation(0, 0, EnemySetting::speed);
		mat = transMat * mat;
		_enemy->SetMat(mat);
	}
	//残り行動時間
	m_lastTime--;
	Math::Vector3 targetVec = _gameScene->GetPlayerManager().GetPlayer().GetMat().Translation() - _enemy->GetMat().Translation();
	
	if (m_lastTime <= 0)
	{
		if (targetVec.Length() < EnemySetting::searchingRange)
		{
			_enemy->SetStateType(EnemyState::Track);
			return new Track();
		}
		_enemy->SetStateType(EnemyState::Walk);
		return new WalkAround();
	}

	return nullptr;
}
