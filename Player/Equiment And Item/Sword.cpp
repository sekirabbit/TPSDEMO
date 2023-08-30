#include"Headers.h"

Sword::Sword(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Sword/shortsword.gltf"); 
	m_localMat = DirectX::XMMatrixIdentity(); 
	m_localMat = DirectX::XMMatrixTranslation(0, 1.0f, 0);
}

void Sword::Update()
{
	Math::Matrix rotYMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90));
	m_worldMat = m_localMat * m_gameScene->GetPlayerManager().GetPlayerRHand().GetMat();
	m_worldMat = rotYMat * m_worldMat;
	m_pos = m_worldMat.Translation();
}

void Sword::Draw()
{
	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 0.2f,0.2f,1.0f });
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLimLightEnable(false);
}
