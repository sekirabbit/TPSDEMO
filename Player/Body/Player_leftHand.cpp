#include"Headers.h"

Player_leftHand::Player_leftHand(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Player_leftHand/Player_leftHand.gltf");
	Math::Matrix rotXMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(30));
	Math::Matrix rotYMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(30));
	Math::Matrix transMat = DirectX::XMMatrixTranslation(-0.8f, 0, 0);
	m_localMat = transMat;
}

void Player_leftHand::Update()
{
	m_worldMat = m_localMat * m_gameScene->GetPlayerManager().GetPlayerLArm().GetMat();
}







