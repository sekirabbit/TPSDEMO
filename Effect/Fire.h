#pragma once

#include"EffectBase.h"

class Fire :public EffectBase
{
public:
	Fire(const Math::Vector3& _intPos);
	~Fire();
	void Draw()override;
	bool Update()override;
private:
	KdBuffer m_vb;

};