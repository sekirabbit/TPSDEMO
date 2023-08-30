#include"Headers.h"

Hat::Hat(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Hat/Hat.gltf");
	m_localMat = DirectX::XMMatrixTranslation(0.15f, 0.6f, 0);
	Math::Matrix rotYMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(180));
	m_localMat = rotYMat * m_localMat;

}

void Hat::Update()
{
	m_worldMat = m_localMat * m_gameScene->GetPlayerManager().GetPlayerHead().GetMat();
}

void Hat::Draw()
{
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetDitherEnable(false);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetDitherEnable(true);
}





