#include"Headers.h"

GunBarrel::GunBarrel(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/ShotGun/ShotGunBarrel.gltf");
	m_localMat = DirectX::XMMatrixIdentity();
	Math::Matrix transMat = DirectX::XMMatrixTranslation(0, 0, 0);
	Math::Matrix scalMat = DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f);
	m_localMat = transMat;
}

void GunBarrel::Update()
{
	m_worldMat = m_localMat * m_gameScene->GetPlayerManager().GetGunHandle().GetMat();

}

void GunBarrel::Draw()
{
	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 0.2f,0.2f,1.0f });
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLimLightEnable(false);
}



