#include"Headers.h"

Player_head::Player_head(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Head/Head.gltf");
	m_localMat = DirectX::XMMatrixTranslation(0, 1.8f, -0.2f);
	m_rgb_g = 0.5f;
	m_colorChangePow = 0.01f;
	m_turnAng = -3.0f;
	m_addTime = 0.005f;
}

void Player_head::Update()
{
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	m_worldMat = m_localMat * m_gameScene->GetPlayerManager().GetPlayerBody().GetMat();
	if (playerMan.GetPlayer().GetMoveFlg() == false)
	{
		Math::Matrix rotMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_turnAng));
		BreathMotion(rotMat, m_addTime);
	}

	//íÜì≈èÛë‘ï\é¶
	m_rgb_g -= m_colorChangePow;
	if (m_rgb_g <= 0.3f || m_rgb_g >= 0.5f)
	{
		m_colorChangePow *= -1;
	}

}

void Player_head::Draw()
{
	//íÜì≈èÛë‘ÇÃï\åª
	BuffManager& buffMan = m_gameScene->GetBuffManager();
	for (UINT i = 0; i < buffMan.GetBuff().size(); i++)
	{
		if (buffMan.GetBuff()[i]->GetAlive() == true)
		{
			if (buffMan.GetBuff()[i]->GetBuffName() == BuffName::Drug)
			{
				SHADER.m_standardShader.SetColor(0.2f, m_rgb_g, 0.2f);
				SHADER.m_standardShader.SetColorEnable(true);
			}
			else
			{
				SHADER.m_standardShader.SetColorEnable(false);
			}
		}
	}

	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetDitherEnable(false);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetDitherEnable(true);
	SHADER.m_standardShader.SetColorEnable(false);

}

void Player_head::BreathMotion(const Math::Matrix& _mat, float& _addFrameTime)
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




