#include"Headers.h"


River::River()
{
	m_model = RESOURCE.GetModel("Data/Map/DRiver.gltf");
}

void River::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{0.2f,1.0f,0.2f});
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetDitherEnable(false);
	SHADER.m_standardShader.SetNormalEnable(true);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model,1.0f);	
	SHADER.m_standardShader.SetNormalEnable(false);
	SHADER.m_standardShader.SetDitherEnable(true);
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetLimLightEnable(false);

}
