#include "Headers.h"

Enemy_hand::Enemy_hand(GameScene* _gameScene, Enemy* _enemy)
{
	m_gameScene = _gameScene;
	m_enemy = _enemy;

	m_worldMat = DirectX::XMMatrixIdentity();
	m_model = RESOURCE.GetModel("Data/Enemy/Zombie/Zombie_hand.gltf");
	m_localMat = DirectX::XMMatrixTranslation(0, 3.0f, 0);
	m_animeFlg = false;
	m_animeFrame = 0;
	m_turnAng = -60;
	m_addTime = 0.03f;
}

void Enemy_hand::Update()
{
	m_worldMat = m_enemy->GetMat();
	m_worldMat = m_localMat * m_worldMat;

	if (m_enemy->GetCurrentStateType() == EnemyState::AttackWait)
	{
		m_animeFlg = true;
	}
	else
	{
		m_animeFlg = false;
		m_animeFrame = 0;
	}
	//アニメーション================================
	if (m_animeFlg == true)
	{
		m_startMat = m_worldMat;
		Math::Matrix rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_turnAng));
		m_endMat = rotXMat * m_startMat;
		if (m_animeFrame > 1)
		{
			m_animeFrame = 1;
		}
		m_animeFrame += m_addTime;
		AnimeProc(m_startMat, m_endMat, m_animeFrame, m_worldMat);
	}

	//===============================================

}

void Enemy_hand::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
}
