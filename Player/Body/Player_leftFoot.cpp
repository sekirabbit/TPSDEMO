#include"Headers.h"

Player_leftFoot::Player_leftFoot(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Player_leftFoot/Player_leftFoot.gltf");
	m_animeFlg = false;
	m_animeFrame = 0;
	m_addTime = 0.1f;
	m_turnAng = -15;
}

void Player_leftFoot::Update()
{
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	m_worldMat = playerMan.GetPlayerLLeg().GetMat();
	if (playerMan.GetPlayer().GetMoveFlg() == true)
	{
		m_animeFlg = true;
	}
	else
	{
		m_animeFlg = false;
	}
	if (playerMan.GetPlayer().GetSlashFlg() == true)
	{
		if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash1 || playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash2)
		{
			Math::Matrix transMat = DirectX::XMMatrixTranslation(0, -0.1f, -0.2f);
			Math::Matrix rotMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(0));
			m_localMat = rotMat * transMat;
			m_worldMat = m_localMat * m_worldMat;
		}
		if (playerMan.GetPlayer().GetPlayerState() == PlayerState::Slash2)
		{
			Math::Matrix transMat = DirectX::XMMatrixTranslation(0, -0.1f, 0.2f);
			Math::Matrix rotMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(30));
			m_localMat = rotMat * transMat;
			m_worldMat = m_localMat * m_worldMat;
		}
	}
	m_startMat = m_worldMat;
	Math::Matrix rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_turnAng));
	m_endMat = rotXMat * m_startMat;
	//アニメーション================================
	if (m_animeFlg == true)
	{
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
