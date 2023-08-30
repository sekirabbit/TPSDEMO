#include"Headers.h";

Drug::Drug(GameScene* _gameScene, const ObjType& _taker)
{
	m_gameScene = _gameScene;
	//��b�̎�����ݒ肷��i�U�O�t���C����b�P�ʁj
	m_lifeTime = BuffSetting::drugLifeTime;
	m_currentLifeTime = m_lifeTime;
	m_buffTaker = _taker;
	m_buffName = BuffName::Drug;
	m_buff = RESOURCE.GetTexture("Data/Texture/UI/Buff_drug.png");
}

bool Drug::Update()
{
	if (m_buffTaker == ObjType::Player)
	{
		m_gameScene->GetPlayerManager().GetPlayer().HPChange(BuffSetting::drugDamage);
	}
	m_currentLifeTime--;
	if (m_currentLifeTime <= 0)
	{
		return false;
	}
	m_alpha = m_currentLifeTime / m_lifeTime;
	return true;
}
