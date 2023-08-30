#include"Headers.h"

Player_rightHand::Player_rightHand(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Player_rightHand/Player_rightHand.gltf");
}

void Player_rightHand::Update()
{
	PlayerManager& playerMan = m_gameScene->GetPlayerManager();
	Math::Matrix transMat = DirectX::XMMatrixTranslation(0, 1.0f, 0);
	m_worldMat = playerMan.GetPlayerRArm().GetMat();
	m_worldMat = transMat * m_worldMat;

}
