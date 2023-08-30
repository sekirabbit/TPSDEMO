#pragma once

#include"EffectBase.h"

class Blood :public EffectBase
{
public:
	Blood(const Math::Vector3& _intPos);
	~Blood();
	void Draw()override;
	bool Update()override;
private:
	KdBuffer m_vb;
};