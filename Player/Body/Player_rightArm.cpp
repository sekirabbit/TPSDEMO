#include"Headers.h"

Player_rightArm::Player_rightArm(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Player_rightShoulder/Player_rightShoulder.gltf");
}

void Player_rightArm::Update()
{
	m_worldMat = m_gameScene->GetPlayerManager().GetPlayerRShoulder().GetMat();

}





