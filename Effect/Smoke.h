#pragma once


#include"EffectBase.h"

class Smoke :public EffectBase
{
public:
	Smoke(const Math::Vector3& _intPos,const Math::Color& _color = {1.0f,1.0f,1.0f,1.0f}, const float& _size = 2.0f);
	~Smoke();
	bool Update()override;
	void Draw()override;
	
private:
	KdBuffer m_vb;
	Math::Color m_color;
};