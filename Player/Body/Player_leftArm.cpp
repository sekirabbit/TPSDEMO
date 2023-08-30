#include"Headers.h"

Player_leftArm::Player_leftArm(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Player_leftArm/Player_leftArm.gltf");
	Math::Matrix rotYMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(100));
	Math::Matrix rotZMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-30));
	Math::Matrix transMat = DirectX::XMMatrixTranslation(-0.5f, 0 ,0);
	m_localMat = rotYMat * rotZMat * transMat;
}

void Player_leftArm::Update()
{
	m_worldMat = m_localMat * m_gameScene->GetPlayerManager().GetPlayerLShoulder().GetMat();
}
