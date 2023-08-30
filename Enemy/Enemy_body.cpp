#include "Headers.h"

Enemy_body::Enemy_body(GameScene* _gameScene, Enemy* _enemy)
{
	m_gameScene = _gameScene;
	m_enemy = _enemy;
}

void Enemy_body::Update()
{
	m_worldMat = m_enemy->GetMat();
}

void Enemy_body::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
}
