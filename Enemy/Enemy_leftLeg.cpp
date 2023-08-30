#include "Headers.h"

Enemy_leftLeg::Enemy_leftLeg(GameScene* _gameScene, Enemy* _enemy)
{
	m_gameScene = _gameScene;
	m_enemy = _enemy;

	m_worldMat = DirectX::XMMatrixIdentity(); 
	m_model = RESOURCE.GetModel("Data/Enemy/Zombie/Zombie_left_leg.gltf");
	m_localMat = DirectX::XMMatrixTranslation(0, 2.2f, 0);
	m_animeFlg = false;
	m_animeFrame = 0;
	m_turnAng = -30;
	m_addTime = 0.07f;
}

void Enemy_leftLeg::Update()
{
	m_worldMat = m_enemy->GetMat();
	m_worldMat = m_localMat * m_worldMat;
	if (m_enemy->GetCurrentStateType() == EnemyState::Walk ||
		m_enemy->GetCurrentStateType() == EnemyState::Track||
		m_enemy->GetCurrentStateType() == EnemyState::AttackWait||
		m_enemy->GetCurrentStateType() == EnemyState::Attack)
	{
		m_animeFlg = true;
	}
	else
	{
		m_animeFlg = false;
	}

	//アニメーション================================
	if (m_animeFlg == true)
	{
		m_startMat = m_worldMat;
		Math::Matrix rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_turnAng));
		m_endMat = rotXMat * m_startMat;
		if (m_animeFrame < 0)
		{
			m_animeFrame = 0;
			m_addTime = -m_addTime;
			m_turnAng = -m_turnAng;
		}
		if (m_animeFrame > 1)
		{
			m_animeFrame = 1;
			m_addTime = -m_addTime;
		}
		m_animeFrame += m_addTime;
		AnimeProc(m_startMat, m_endMat, m_animeFrame, m_worldMat);
	}

	//===============================================

}

void Enemy_leftLeg::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
}
