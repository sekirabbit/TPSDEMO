#include"Headers.h"

Bilud::Bilud(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Map/Bilud.gltf");
}

void Bilud::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLightEnable(true);
}
