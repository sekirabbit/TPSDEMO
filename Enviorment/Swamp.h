#pragma once

class GameScene;

#include"EffectBase.h"

class Swamp :public EffectBase
{
public:
	Swamp(GameScene* _gameScene, const Math::Vector3& _vec, const float& _size = 1.0f, const bool _dieEnable = true);
	void Draw()override;
	bool Update()override;
	bool CheckSwamp(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normalVec)const;

	const float& GetSize()const
	{
		return m_size;
	}
	const float& GetAlpha()const
	{
		return m_alpha;
	}

private:
	bool m_dieEnable;
	bool m_afterEnemyDead;
};