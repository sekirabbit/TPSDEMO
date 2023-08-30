#pragma once

#include"ObjectBase.h"

class Dizzy :public ObjectBase
{
public:
	Dizzy(Enemy* _enemy);

	void Update()override;
	void Draw()override;

private:
	Enemy* m_enemy;
	KdModel* m_starModel;

	Math::Matrix m_starMat[3];


	float m_alpha;
	float m_angY;
	float m_addAngY;

	float m_lifeTime;
	float m_currentLifeTime;


	// ブレンドステート
	ID3D11BlendState* m_blendAlpha;
	ID3D11BlendState* m_blendAdd;
};