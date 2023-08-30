#include"Headers.h"

Player_leftShoulder::Player_leftShoulder(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Player_leftShoulder/Player_leftShoulder.gltf");
	Math::Matrix rotZMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(30));
	Math::Matrix transMat = DirectX::XMMatrixTranslation(-0.5f, 1.7f, -0.2f);
	m_localMat = rotZMat * transMat;
	m_animeFrame = 0;
	m_addTime = 0.15f;
	m_reloadTime = 0;
	m_fireAnimeFlg = false;
	m_loadAnimeFlg = false;
}

void Player_leftShoulder::Update()
{
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	m_worldMat = m_localMat * playerMan.GetPlayerBody().GetMat();

	//アニメーション================================

	if (playerMan.GetPlayer().GetReloadFlg() == true)
	{
		m_loadAnimeFlg = true;
		Math::Matrix rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90));
		m_startMat = m_worldMat;
		m_endMat = rotXMat * m_worldMat;
	}


	if (playerMan.GetPlayer().GetFireFlg() == true)
	{
		m_fireAnimeFlg = true;
		Math::Matrix rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(-30));
		m_startMat = m_worldMat;
		m_endMat = rotXMat * m_worldMat;
	}

	//リロード
	if (m_loadAnimeFlg == true)
	{
		if (m_animeFrame > 1)
		{
			m_animeFrame = 1;
			m_addTime = -m_addTime;
			if (playerMan.GetPlayer().GetFireEnableBulletNum() == 1)
			{
				if (playerMan.GetPlayer().GetTakeBulletNum() >= 1)
				{
					playerMan.GetPlayer().SetFireEnableBulletNum(1);
					playerMan.GetPlayer().SetTakeBulletNum(-1);
				}
			}
			if (playerMan.GetPlayer().GetFireEnableBulletNum() == 0)
			{
				if (playerMan.GetPlayer().GetTakeBulletNum() < 2)
				{
					playerMan.GetPlayer().SetFireEnableBulletNum(1);
					playerMan.GetPlayer().SetTakeBulletNum(-1);
				}
				if (playerMan.GetPlayer().GetTakeBulletNum() >= 2)
				{
					playerMan.GetPlayer().SetFireEnableBulletNum(2);
					playerMan.GetPlayer().SetTakeBulletNum(-2);
				}
				
			}
		}
		if (m_animeFrame < 0)
		{
			m_animeFrame = 0;
			m_addTime = -m_addTime;
			
			m_loadAnimeFlg = false;
			playerMan.GetPlayer().SetReload(false);
		}
		m_animeFrame += m_addTime / 3;
		AnimeProc(m_startMat, m_endMat, m_animeFrame, m_worldMat);
	}
	//ファイア
	if (m_fireAnimeFlg == true)
	{
		if (m_animeFrame > 1)
		{
			m_animeFrame = 1;
			m_addTime = -m_addTime;
		}
		if (m_animeFrame < 0)
		{
			m_animeFrame = 0;
			m_addTime = -m_addTime;
			playerMan.GetPlayer().SetFireEnableBulletNum(-1);
			m_fireAnimeFlg = false;
			playerMan.GetPlayer().SetFire(false);
		}
		m_animeFrame += m_addTime;
		AnimeProc(m_startMat, m_endMat, m_animeFrame, m_worldMat);
	}

	//===============================================

}





