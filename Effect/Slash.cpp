#include "Headers.h"


Slash::Slash(GameScene* _gameScene, const Math::Vector3& _intPos)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Effect/Slash/slash.gltf");
	m_size = 1.5f;
	m_alpha = 3.0f;

	m_pos = _intPos;
}

bool Slash::Update()
{
	m_alpha -= 0.5f;
	if (m_alpha <= 0)
	{
		m_alpha = 0;
		return false;
	}

	return true;
}

void Slash::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
}




