#include"Headers.h"

GunHandle::GunHandle(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/ShotGun/ShotGunHandle.gltf");
	m_localMat = DirectX::XMMatrixIdentity();
	Math::Matrix scalMat = DirectX::XMMatrixScaling(2.5f, 2.5f, 2.5f);
	Math::Matrix transMat = DirectX::XMMatrixTranslation(0, 0, 0);
	m_localMat = scalMat * transMat;
}

void GunHandle::Update()
{
	m_worldMat = m_localMat * m_gameScene->GetPlayerManager().GetPlayerLHand().GetMat();
}




