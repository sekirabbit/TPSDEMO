#include "Headers.h"

BossDashAttack::BossDashAttack()
{
	m_moveDis = 0;
	m_speed = 0;
	m_acceleration = BossSetting::attackSpeedAcceleration;
	m_maxSpeed = BossSetting::attackMaxSpeed;
	m_moveAfterDis = BossSetting::attackMoveDis;
	m_damege = BossSetting::attackPower;
}

BaseState* BossDashAttack::Action(Enemy* _enemy, GameScene* _gameScene)
{
	if (_enemy->GetCurrentStateType() == EnemyState::Weak)
	{
		return new Weak();
	}
	PlayerManager& playerMan = _gameScene->GetPlayerManager();

	//移動
	if (_enemy->GetAngry())
	{
		m_acceleration = BossSetting::angryAcceleration;
	}
	m_speed += m_acceleration;
	Math::Matrix tmpMat = DirectX::XMMatrixTranslation(0, 0, m_speed);
	_enemy->MultMat(tmpMat);
	//当たり判定
	bool hit = AttackCheck(_enemy->GetMat().Translation(), playerMan.GetPlayer().GetPos(), BossSetting::attackRange);
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
			float backPow = BossSetting::attackBackPower;
			playerMan.GetPlayer().SetKnockBack(true, -targetVec, backPow);

			auto se = _gameScene->GetSound().GetHurtSEInst();
			se->Play();
			
			_gameScene->SetBlurTime(PlayerSetting::blurTime);
			_gameScene->GetBuffManager().Add(new Drug(_gameScene, ObjType::Player));
		}
	}
	m_moveDis += m_speed;
	//移動したところに毒を残る
	if (_enemy->GetAngry())
	{
		if ((int)m_moveDis % 5 == 0)
		{
			//毒池の設定
			float size = 2.0f;
			Math::Vector3 swampPos = _enemy->GetPos();
			_gameScene->GetEnviormentManager().AddSwamp(new Swamp(_gameScene, swampPos, size));
		}
	}
	//一定の距離で移動したら状態変換する
	if (m_moveDis >= m_moveAfterDis)
	{
		_enemy->SetStateType(EnemyState::Track);
		return new Track();
	}

	return nullptr;
}