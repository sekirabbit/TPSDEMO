#include"Headers.h";

Heal::Heal(GameScene* _gameScene, const ObjType& _taker, const float& _healPow)
{
	m_gameScene = _gameScene;
	m_buffTaker = _taker;
	m_buffName = BuffName::Heal;
	m_buff = RESOURCE.GetTexture("Data/Texture/UI/Buff_heal.png");
	m_healPow = _healPow;
	m_lifeTime = BuffSetting::healLifeTime;
	m_currentLifeTime = m_lifeTime;
	m_addedHP = m_healPow / m_lifeTime;
}

bool Heal::Update()
{
	if (m_buffTaker == ObjType::Player)
	{
		//–ˆ‰ñ‚Ì‰ñ•œ’l
		m_gameScene->GetPlayerManager().GetPlayer().HPChange(m_addedHP);
		m_currentLifeTime--;
		if (m_currentLifeTime <= 0)
		{
			return false;
		}
		m_alpha = m_currentLifeTime / m_lifeTime;
	}

	return true;
}
