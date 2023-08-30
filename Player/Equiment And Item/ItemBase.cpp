#include "Headers.h"

void ItemBase::Update()
{
	Math::Vector3 targetVec = m_gameScene->GetPlayerManager().GetPlayer().GetPos() - m_pos;
	float dist = targetVec.Length();
	if (dist < 1)
	{
		//アイテムゲットSE
		auto se = m_gameScene->GetSound().GetItemSE();
		auto seInst = se->CreateInstance(false);
		seInst->Play();
		if (m_itemType == ItemType::Potion)
		{
			m_gameScene->GetPlayerManager().GetPlayer().AddPotion(new Potion(m_gameScene, Math::Vector3::Zero));
		}
		if (m_itemType == ItemType::Ammo)
		{
			m_gameScene->GetPlayerManager().GetPlayer().HPChange(10);
			m_gameScene->GetPlayerManager().GetPlayer().SetTakeBulletNum(2);
		}
		m_aliveFlg = false;
	}
}

void ItemBase::Draw()
{
	SHADER.m_standardShader.SetLightEnable(false);
	SHADER.m_standardShader.SetLimLightEnable(true);
	SHADER.m_standardShader.SetLimLightColor(Math::Vector3{ 2, 2, 2 });
	SHADER.m_standardShader.SetWorldMatrix(m_worldMat);
	SHADER.m_standardShader.DrawModel(m_model);
	SHADER.m_standardShader.SetLimLightEnable(false);
	SHADER.m_standardShader.SetLightEnable(true);
}
