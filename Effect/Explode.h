#pragma once

#include"EffectBase.h"
class GameScene;

class Explode :public EffectBase
{
public:
	Explode(GameScene* _gameScene);
	~Explode();

	void Draw()override;
	bool Update()override;
private:
	static const int texNum = 10;
	Math::Matrix m_slowMat[texNum];
	KdBuffer m_vb;

	float m_lifeTime;

};