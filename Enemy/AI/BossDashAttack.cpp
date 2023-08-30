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

	//ˆÚ“®
	if (_enemy->GetAngry())
	{
		m_acceleration = BossSetting::angryAcceleration;
	}
	m_speed += m_acceleration;
	Math::Matrix tmpMat = DirectX::XMMatrixTranslation(0, 0, m_speed);
	_enemy->MultMat(tmpMat);
	//“–‚½‚è”»’è
	bool hit = AttackCheck(_enemy->GetMat().Translation(), playerMan.GetPlayer().GetPos(), BossSetting::attackRange);
	if (hit)
	{
		if (playerMan.GetPlayer().GetHurtEnable() == true)
		{
			playerMan.GetPlayer().HPChange(m_damege);
			playerMan.GetPlayer().SetHurtEnable(false);
			playerMan.GetPlayer().SetHurtCold(PlayerSetting::hitWaitTime);
			
			//enemy‚ÌUŒ‚•ûŒü‚ÉƒmƒbƒNƒoƒbƒN
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
	//ˆÚ“®‚µ‚½‚Æ‚±‚ë‚É“Å‚ðŽc‚é
	if (_enemy->GetAngry())
	{
		if ((int)m_moveDis % 5 == 0)
		{
			//“Å’r‚ÌÝ’è
			float size = 2.0f;
			Math::Vector3 swampPos = _enemy->GetPos();
			_gameScene->GetEnviormentManager().AddSwamp(new Swamp(_gameScene, swampPos, size));
		}
	}
	//ˆê’è‚Ì‹——£‚ÅˆÚ“®‚µ‚½‚çó‘Ô•ÏŠ·‚·‚é
	if (m_moveDis >= m_moveAfterDis)
	{
		_enemy->SetStateType(EnemyState::Track);
		return new Track();
	}

	return nullptr;
}