#include "Headers.h"

DrugNova::DrugNova()
{
	m_damege = BossSetting::novaPower;
	m_attackRange = BossSetting::attackRange;
	m_novaSize = BossSetting::novaBaseSize;
	m_sizeChangePower = expandSizePower;
	m_novaAlpha = 0.1f;
	m_alphaChangePower = 0.01f;
	m_changeSizeWaitTime = 0;
}

BaseState* DrugNova::Action(Enemy* _enemy, GameScene* _gameScene)
{
	//bossがスキル使う初めにse使用
	if (m_novaAlpha == 0.1f)
	{
		auto se = _gameScene->GetSound().GetNovaSE();
		auto seInst = se->CreateInstance(false);
		seInst->Play();
	}

	PlayerManager& playerMan = _gameScene->GetPlayerManager();

	//たまモデルサイズ変更
	m_changeSizeWaitTime--;
	if (m_changeSizeWaitTime < 0)
	{
		m_changeSizeWaitTime = 0;
	}
	if (m_changeSizeWaitTime == 0)
	{
		m_novaSize += m_sizeChangePower;
		if (m_novaSize > BossSetting::novaBigestSize)
		{
			m_novaSize = BossSetting::novaBigestSize;
			m_sizeChangePower = shrinkSizePower;
			m_changeSizeWaitTime = 60;
		}
		if (m_novaSize < BossSetting::novaBaseSize)
		{
			m_novaSize = BossSetting::novaBaseSize;
			m_alphaChangePower = -0.01f;
		}
		//たまモデルアルファ値変更
		m_novaAlpha += m_alphaChangePower;
		if (m_novaAlpha > 1)
		{
			m_novaAlpha = 1;
		}
		if (m_novaAlpha < 0)
		{
			m_novaAlpha = 0;
			_enemy->SetStateType(EnemyState::Track);
			return new Track();
		}
	}
	
	_enemy->GetVomit().NovaModelUpdate(m_novaSize, m_novaAlpha);

	m_attackRange = m_novaSize;
	//当たり判定
	bool hit = AttackCheck(_enemy->GetMat().Translation(), playerMan.GetPlayer().GetPos(), m_attackRange);
	if (hit)
	{
		if (playerMan.GetPlayer().GetHurtEnable() == true)
		{
			playerMan.GetPlayer().HPChange(m_damege);
			playerMan.GetPlayer().SetHurtEnable(false);
			playerMan.GetPlayer().SetHurtCold(PlayerSetting::hitWaitTime);

			auto se = _gameScene->GetSound().GetHurtSEInst();
			se->Play();

			_gameScene->SetBlurTime(PlayerSetting::blurTime);
			_gameScene->GetBuffManager().Add(new Drug(_gameScene, ObjType::Player));
		}
	}

	return nullptr;
}