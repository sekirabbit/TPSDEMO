#include"Headers.h"

Player_body::Player_body(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Player_body/Player_body.gltf");
	m_localMat = DirectX::XMMatrixTranslation(0, 0.6f, 0);
	m_animeFlg = true;
	m_animeFrame = 0;
	m_turnAng = -5;
	m_addTime = 0.1f;
}

void Player_body::Update()
{
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	m_worldMat = m_localMat * playerMan.GetPlayer().GetMat();
	Math::Matrix rotMat;
	//アニメーション================================
	if (m_animeFlg == true)
	{
		if (playerMan.GetPlayer().GetMoveFlg() == true)
		{
			rotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_turnAng));
			MoveMotion(rotMat, m_addTime);
		}
	}
	//===============================================

}

void Player_body::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
}

void Player_body::MoveMotion(const Math::Matrix& _mat, float& _addFrameTime)
{
	m_startMat = m_worldMat;
	m_endMat = _mat * m_startMat;
	if (m_animeFrame < 0)
	{
		m_animeFrame = 0;
		_addFrameTime = -_addFrameTime;
		m_turnAng = -m_turnAng;
	}
	if (m_animeFrame > 1)
	{
		m_animeFrame = 1;
		_addFrameTime = -_addFrameTime;
	}
	m_animeFrame += _addFrameTime;
	AnimeProc(m_startMat, m_endMat, m_animeFrame, m_worldMat);
}

