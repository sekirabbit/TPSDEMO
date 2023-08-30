#pragma once

#include"EffectBase.h"
class GameScene;

class Bullet :public EffectBase
{
public:
	Bullet(GameScene* _gameScene, const Math::Vector3& _intPos, const Math::Vector3& _dir, const Math::Matrix& _rotMat);
	~Bullet();
	bool Update()override;
	void Draw()override;
	bool EnemyHit();
	const int GetLifeTime()const
	{
		return m_lifeTime;
	}
	void SetLifeTime(int _num)
	{
		m_lifeTime = _num;
	}
	const Math::Vector3& GetMoveVec()const
	{
		return m_moveVec;
	}
private:
	KdBuffer m_vb;
	Math::Vector3 m_moveVec;
	Math::Matrix m_rotMat;
	//Žõ–½
	int m_lifeTime;
};