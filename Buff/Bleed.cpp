#include"Headers.h";

Bleed::Bleed(GameScene* _gameScene, const ObjType& _taker)
{
	m_gameScene = _gameScene;
	//ˆê•b‚ÌŽõ–½‚ðÝ’è‚·‚éi‚U‚OƒtƒŒƒCƒ€ˆê•b’PˆÊj
	m_lifeTime = BuffSetting::bleedLifeTime;
	m_currentLifeTime = m_lifeTime;
	m_buffTaker = _taker;
	m_buffName = BuffName::Bleed;
	m_buff = RESOURCE.GetTexture("Data/Texture/UI/Buff_bleed.png");
}

bool Bleed::Update()
{
	if (m_buffTaker == ObjType::Player)
	{
		m_gameScene->GetPlayerManager().GetPlayer().HPChange(BuffSetting::bleedDamage);
	}
	m_currentLifeTime--;
	if (m_currentLifeTime <= 0)
	{
		return false;
	}
	m_alpha = m_currentLifeTime / m_lifeTime;

	return true;
}
