#pragma once

#include"EffectBase.h"

class DamageNum :public EffectBase
{
public:
	DamageNum(const Math::Vector3& _intPos,const float& _damage,bool _isWeakDamage = false);
	~DamageNum();
	void Draw()override;
	bool Update()override;
private:
	KdTexture* m_normalMath;
	KdTexture* m_weakMath;

	KdBuffer m_tenVb;
	KdBuffer m_uintVb;

	Math::Matrix m_TenMat;
	Math::Matrix m_UintMat;

	int m_transparentBeginTime;
	float m_damage;
	bool m_damageTenFlg;
	bool m_isWeakDamage;

};