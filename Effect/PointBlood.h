#pragma once

#include"EffectBase.h"

class PointBlood :public EffectBase
{
public:
	PointBlood(const Math::Vector3& _intPos,const Math::Vector3& _dirVec, const float& _aliveTime, const float& _alpha = 1.0f, const float& _size = 0.15f);
	~PointBlood();
	void Draw()override;
	bool Update()override;
private:
	KdBuffer m_vb;

	Math::Vector3 m_moveVec;
	float m_gravity;
	float m_aliveTime;
};