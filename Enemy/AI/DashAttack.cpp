#include "Headers.h"

DashAttack::DashAttack()
{
	m_moveDis = 0;

	m_speed = 0;
	m_acceleration = EnemySetting::attackSpeedAcceleration;
	m_maxSpeed = EnemySetting::attackMaxSpeed;
	m_moveAfterDis = EnemySetting::attackMoveDis;
	m_damege = EnemySetting::attackPower;
}

BaseState* DashAttack::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}
	PlayerManager& playerMan = _gameScene->GetPlayerManager();

	bool hit = AttackCheck(_enemy->GetMat().Translation(), playerMan.GetPlayer().GetPos(), EnemySetting::attackRange);
	
	m_speed += m_acceleration;
	Math::Matrix tmpMat = DirectX::XMMatrixTranslation(0, 0, m_speed);
	_enemy->MultMat(tmpMat);
	if (hit)
	{
		if (playerMan.GetPlayer().GetHurtEnable() == true)
		{
			playerMan.GetPlayer().HPChange(m_damege);
			playerMan.GetPlayer().SetHurtEnable(false);
			playerMan.GetPlayer().SetHurtCold(PlayerSetting::hitWaitTime);
			//enemyの攻撃方向にノックバック
			Math::Vector3 targetVec;
			targetVec = _enemy->GetMat().Translation() - _gameScene->GetPlayerManager().GetPlayer().GetMat().Translation();
			targetVec.y = 0;
			targetVec.Normalize();
			float backPow = EnemySetting::attackBackPower;
			playerMan.GetPlayer().SetKnockBack(true, -targetVec, backPow);

			auto se = _gameScene->GetSound().GetHurtSEInst();
			se->Play();
			
			_gameScene->SetBlurTime(PlayerSetting::blurTime);
			_gameScene->GetBuffManager().Add(new Bleed(_gameScene, ObjType::Player));
		}
	}
	m_moveDis += m_speed;
	
	//一定の距離で移動したら状態変換する
	if (m_moveDis >= m_moveAfterDis)
	{
		_enemy->SetStateType(EnemyState::Track);
		return new Track();
	}

	return nullptr;
}