#include"Headers.h"

Bridge::Bridge(GameScene* _gameScene)
{
	m_gameScene = _gameScene;
	m_drawModel = RESOURCE.GetModel("Data/Map/Bridging.gltf");
	m_model = RESOURCE.GetModel("Data/Map/bridgeHit.gltf");
}

void Bridge::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_drawModel);
	SHADER.m_standardShader.SetLightEnable(true);
}
