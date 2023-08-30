#include"Headers.h"


EffectBase::EffectBase()
{
	m_worldMat = Math::Matrix::Identity;
	m_pos = { 0,0,0 };

	m_blendAlpha = D3D.CreateBlendState(KdBlendMode::Alpha);
	m_blendAdd = D3D.CreateBlendState(KdBlendMode::Add);
}

EffectBase::~EffectBase()
{
}

bool EffectBase::Update()
{
	return true;
}

void EffectBase::Draw()
{

}


