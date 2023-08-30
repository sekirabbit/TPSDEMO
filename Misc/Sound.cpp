#include "Headers.h"

Sound::Sound()
{
	//サウンドの読み込み===================================
	//音量調整(0ミュート１が最大(デフォルト))
	m_BGMPow = 0.25f;

	m_startSE = std::make_shared<KdSoundEffect>();
	m_startSE->Load("Data/Sound/Start.wav");
	m_startSEInst = m_startSE->CreateInstance(false);

	m_clearSE = std::make_shared<KdSoundEffect>();
	m_clearSE->Load("Data/Sound/Clear.wav");
	m_clearSEInst = m_clearSE->CreateInstance(false);

	m_playerHurtSE = std::make_shared<KdSoundEffect>();
	m_playerHurtSE->Load("Data/Sound/PlayerHurt.wav");
	m_playerHurtSEInst = m_playerHurtSE->CreateInstance(true);
	m_playerHurtSEInst->SetVolume(0.5f);

	m_playerDeadSE = std::make_shared<KdSoundEffect>();
	m_playerDeadSE->Load("Data/Sound/PlayerDead.wav");
	m_playerDeadSEInst = m_playerDeadSE->CreateInstance(true);
	m_playerDeadSEInst->SetVolume(0.5f);

	m_walkSE = std::make_shared<KdSoundEffect>();
	m_walkSE->Load("Data/Sound/SoftWalk.wav");
	m_walkSEInst = m_walkSE->CreateInstance(true);
	m_walkSEInst->SetPitch(0.5f);
	m_walkSEInst->SetVolume(0);
	m_walkSEInst->Play(true);

	m_readSE = std::make_shared<KdSoundEffect>();
	m_readSE->Load("Data/Sound/Read.wav");
	m_readSEInst = m_readSE->CreateInstance(true);
	m_readSEInst->SetVolume(0.5f);

	m_getItemSE = std::make_shared<KdSoundEffect>();
	m_getItemSE->Load("Data/Sound/Get.wav");
	m_getItemSEInst = m_getItemSE->CreateInstance(true);
	m_getItemSEInst->SetVolume(0.5f);

	m_itemOutSE = std::make_shared<KdSoundEffect>();
	m_itemOutSE->Load("Data/Sound/ItemOut.wav");
	m_itemOutSEInst = m_itemOutSE->CreateInstance(true);
	m_itemOutSEInst->SetVolume(0.5f);

	m_slashSE = std::make_shared<KdSoundEffect>();
	m_slashSE->Load("Data/Sound/SlashUnHit.wav");
	m_slashSEInst = m_slashSE->CreateInstance(true);
	m_slashSEInst->SetVolume(0.1f);

	m_slashHitSE = std::make_shared<KdSoundEffect>();
	m_slashHitSE->Load("Data/Sound/SlashHit.wav");
	m_slashHitSEInst = m_slashHitSE->CreateInstance(true);
	m_slashHitSEInst->SetVolume(0.1f);

	m_fireSE = std::make_shared<KdSoundEffect>();
	m_fireSE->Load("Data/Sound/Fire.wav");
	m_fireSEInst = m_fireSE->CreateInstance(true);
	m_fireSEInst->SetVolume(0.8f);

	m_reloadSE = std::make_shared<KdSoundEffect>();
	m_reloadSE->Load("Data/Sound/Reload.wav");
	m_reloadSEInst = m_reloadSE->CreateInstance(true);
	m_reloadSEInst->SetVolume(0.5f);

	m_lockSE = std::make_shared<KdSoundEffect>();
	m_lockSE->Load("Data/Sound/GunLock.wav");
	m_lockSEInst = m_lockSE->CreateInstance(true);
	m_lockSEInst->SetVolume(0.5f);

	m_drinkSE = std::make_shared<KdSoundEffect>();
	m_drinkSE->Load("Data/Sound/Drink.wav");
	m_drinkSEInst = m_drinkSE->CreateInstance(true);
	m_drinkSEInst->SetVolume(3.0f);

	m_zombieAwakeSE = std::make_shared<KdSoundEffect>();
	m_zombieAwakeSE->Load("Data/Sound/ZombieAttack.wav");
	m_zombieAwakeSEInst = m_zombieAwakeSE->CreateInstance(true);
	m_zombieAwakeSEInst->SetVolume(1.0f);

	m_zombieDeadSE = std::make_shared<KdSoundEffect>();
	m_zombieDeadSE->Load("Data/Sound/EnemyDead.wav");
	m_zombieDeadSEInst = m_zombieDeadSE->CreateInstance(true);
	m_zombieDeadSEInst->SetVolume(0.5f);

	m_vomitAttackSE = std::make_shared<KdSoundEffect>();
	m_vomitAttackSE->Load("Data/Sound/Vomit.wav");
	m_vomitAttackSEInst = m_vomitAttackSE->CreateInstance(true);
	m_vomitAttackSEInst->SetVolume(0.5f);

	m_novaSE = std::make_shared<KdSoundEffect>();
	m_novaSE->Load("Data/Sound/Nova.wav");
	m_novaSEInst = m_novaSE->CreateInstance(true);
	m_novaSEInst->SetVolume(1.0f);

	m_titleBgm = std::make_shared<KdSoundEffect>();
	m_titleBgm->Load("Data/Sound/TitleBGM.wav");
	m_titleBgmInst = m_titleBgm->CreateInstance(false);

	m_soundBgm = std::make_shared<KdSoundEffect>();
	m_soundBgm->Load("Data/Sound/BGM.wav");
	m_soundBgmInst = m_soundBgm->CreateInstance(false);

	m_bossSoundBgm = std::make_shared<KdSoundEffect>();
	m_bossSoundBgm->Load("Data/Sound/BossBGM.wav");
	m_bossSoundBgmInst = m_bossSoundBgm->CreateInstance(false);
}

bool Sound::GameCleanSE()
{
	m_BGMPow -= 0.0025f;
	m_bossSoundBgmInst->SetVolume(m_BGMPow);
	if (m_BGMPow <= 0.0f)
	{
		m_soundBgmInst->Stop();
		return true;
	}
	return false;
}
