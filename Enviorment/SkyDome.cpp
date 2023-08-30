#include"Headers.h"

SkyDome::SkyDome()
{
	m_model = RESOURCE.GetModel("Data/SkyDome/SkyDome.gltf");
	float size = 3.0f;
	Math::Matrix ScalMat = DirectX::XMMatrixScaling(size, size, size);
	Math::Matrix transMat = DirectX::XMMatrixTranslation(-100,-70, 100);
	m_worldMat = ScalMat * transMat * m_worldMat;
}
void SkyDome::Update()
{
	Math::Matrix rotYMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.02f));
	m_worldMat = rotYMat * m_worldMat;
}

void SkyDome::Draw()
{
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLightEnable(true);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}







