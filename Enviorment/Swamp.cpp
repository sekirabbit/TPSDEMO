#include "Headers.h"


Swamp::Swamp(GameScene* _gameScene, const Math::Vector3& _pos,const float& _size, const bool _dieEnable)
{
	m_gameScene = _gameScene;
	m_model = RESOURCE.GetModel("Data/Ground/LSwamp.gltf");
	m_alpha = 1.0f;

	//è¡Ç∑Ç©Ç«Ç§Ç©
	m_dieEnable = _dieEnable;

	m_pos = _pos;
	m_size = _size;
	
	Math::Matrix transMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	Math::Matrix scalMat = DirectX::XMMatrixScaling(m_size, 1, m_size);
	m_worldMat = scalMat * transMat;
}

bool Swamp::Update()
{
	if (m_size < 1)
	{
		m_size += 0.01f;
		if (m_size > 1)
		{
			m_size = 1;
			m_afterEnemyDead = false;
		}
		Math::Matrix scalMat = DirectX::XMMatrixScaling(m_size, m_size, m_size);
		m_worldMat = scalMat * (DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	}

	//è¡Ç∑ÉtÉâÉOÇ…ÇÊÇ¡ÇƒÅAèàóùÇ∑ÇÈ
	if (m_dieEnable)
	{
		m_alpha -= 0.002f;
		if (m_alpha <= 0)
		{
			m_alpha = 0;
			return false;
		}
	}

	return true;
}

bool Swamp::CheckSwamp(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec)const
{
	if (ModelIntersects(*m_model, m_worldMat, _rayPos, _rayVec, _dis, _normalVec))
	{
		return true;
	}
	return false;
}

void Swamp::Draw()
{
	SHADER.m_standardShader.SetToDevice();
	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 0.2f,1.0f,0.2f }); 
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model, m_alpha);
	SHADER.m_standardShader.SetLightEnable(true);
	SHADER.m_standardShader.SetLimLightEnable(false);
}




