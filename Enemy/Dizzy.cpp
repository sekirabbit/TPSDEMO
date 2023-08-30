#include "Headers.h"

Dizzy::Dizzy(Enemy* _enemy)
{
	m_enemy = _enemy;

	m_model = RESOURCE.GetModel("Data/cube/dizzy.gltf");
	m_starModel = RESOURCE.GetModel("Data/cube/star.gltf");

	m_starMat[0] = DirectX::XMMatrixIdentity();
	m_starMat[1] = DirectX::XMMatrixIdentity();
	m_starMat[2] = DirectX::XMMatrixIdentity();

	m_angY = 0;
	m_addAngY = 0.1f;
	m_alpha = 1.0f;

	m_lifeTime = EnemySetting::weakTime;
	m_currentLifeTime = m_lifeTime;

	m_blendAlpha = D3D.CreateBlendState(KdBlendMode::Alpha);
	m_blendAdd = D3D.CreateBlendState(KdBlendMode::Add);
}

void Dizzy::Update()
{
	m_angY += m_addAngY;

	float size, high;
	if (m_enemy->GetEnemyType() == EnemyType::Boss)
	{
		size = 2.0f;
		high = 8.0f;
	}
	else
	{
		size = 1.0f;
		high = 4.0f;
	}
	Math::Matrix rotMat = DirectX::XMMatrixRotationRollPitchYaw(0, m_angY, 0);
	Math::Matrix scalMat = DirectX::XMMatrixScaling(size, size, size);
	Math::Matrix transMat = DirectX::XMMatrixTranslation(0, high, 0);
	// çáê¨
	m_worldMat = scalMat * transMat * m_enemy->GetMat();
	m_worldMat = rotMat * m_worldMat;

	//êØÇÃçsóÒÇê›íË
	m_starMat[0] = DirectX::XMMatrixTranslation(1, 0, 1);
	m_starMat[1] = DirectX::XMMatrixTranslation(0, 0, -1);
	m_starMat[2] = DirectX::XMMatrixTranslation(-1, 0, 1);
	for (int i = 0; i < 3; i++)
	{
		m_starMat[i] = m_starMat[i] * m_worldMat;
	}

	m_alpha = m_currentLifeTime / m_lifeTime;

	m_currentLifeTime--;
	if (m_currentLifeTime <= 0)
	{
		m_currentLifeTime = 0;
		m_currentLifeTime = m_lifeTime;
		m_aliveFlg = false;
	}
}

void Dizzy::Draw()
{
	if (m_enemy->GetAlive())
	{
		if (m_aliveFlg)
		{
			D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
			D3D.GetDevContext()->OMSetBlendState(m_blendAdd, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
			SHADER.m_standardShader.SetLightEnable(false);
			SHADER.m_cb7_Camera.Work().DistanceFogEnable = 0;
			SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
			SHADER.m_standardShader.DrawModel(m_model, m_alpha);
			for (int i = 0; i < 3; i++)
			{
				SHADER.m_standardShader.SetWorldMatrix(m_starMat[i]);
				SHADER.m_standardShader.DrawModel(m_starModel, m_alpha);
			}
			SHADER.m_cb7_Camera.Work().DistanceFogEnable = 1;
			SHADER.m_standardShader.SetLightEnable(true);
			D3D.GetDevContext()->OMSetBlendState(m_blendAlpha, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
			D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
		}
	}
	
}
