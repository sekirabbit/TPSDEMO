#pragma once

#include"EffectBase.h"

class Attention :public EffectBase
{
public:
	Attention(const ObjectBase* _obj);
	~Attention();
	void Draw()override;
	bool Update()override;
private:
	KdBuffer m_vb;

	const ObjectBase* m_obj;
};