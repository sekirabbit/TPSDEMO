#include"Headers.h"

Tree::Tree(GameScene* _gameScene, const Math::Matrix& _mat)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Map/Tree.gltf");
	m_worldMat = _mat;
}

void Tree::Update()
{
	//重ねる防止（プレイヤー）
	if (m_gameScene->GetPlayerManager().GetPlayer().GetHitMapFlg() == true)
	{
		Math::Vector3 targetVec;
		targetVec = m_gameScene->GetPlayerManager().GetPlayer().GetMat().Translation() - m_worldMat.Translation();
		if (targetVec.Length() <= MapSetting::playerAwayTreeDistance)
		{
			float pushPow = MapSetting::playerAwayTreeDistance - targetVec.Length();
			Math::Vector3 moveVec = targetVec;
			moveVec.Normalize();
			moveVec *= pushPow;
			moveVec *= 0.5f;
			m_gameScene->GetPlayerManager().GetPlayer().AddPos(moveVec);
		}
	}
}

void Tree::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLightEnable(true);
}
