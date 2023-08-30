#include"Headers.h"


Ground::Ground()
{
	m_model = RESOURCE.GetModel("Data/Map/Ground.gltf");
}

void Ground::Draw()
{
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetDitherEnable(false);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);	//�\������
	SHADER.m_standardShader.SetDitherEnable(true);
	SHADER.m_standardShader.SetLightEnable(true);
}
