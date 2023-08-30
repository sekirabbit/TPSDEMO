#pragma once

class Sound
{
public:
	Sound();

	bool GameCleanSE();
	//start
	const std::shared_ptr<KdSoundEffect>& GetStartSE()const
	{
		return m_startSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetStartSEInst()const
	{
		return m_startSEInst;
	}

	//clear
	const std::shared_ptr<KdSoundEffect>& GetClearSE()const
	{
		return m_clearSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetClearSEInst()const
	{
		return m_clearSEInst;
	}

	//Player==========================================

	//hurt
	const std::shared_ptr<KdSoundEffect>& GetHurtSE()const
	{
		return m_playerHurtSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetHurtSEInst()const
	{
		return m_playerHurtSEInst;
	}
	//dead
	const std::shared_ptr<KdSoundEffect>& GetDeadSE()const
	{
		return m_playerDeadSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetDeadSEInst()const
	{
		return m_playerDeadSEInst;
	}
	//walk
	const std::shared_ptr<KdSoundEffect>& GetWalkSE()const
	{
		return m_walkSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetWalkSEInst()const
	{
		return m_walkSEInst;
	}
	//getItem
	const std::shared_ptr<KdSoundEffect>& GetItemSE()const
	{
		return m_getItemSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetItemSEInst()const
	{
		return m_getItemSEInst;
	}
	//ItemOut
	const std::shared_ptr<KdSoundEffect>& GetItemOutSE()const
	{
		return m_itemOutSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetItemOutSEInst()const
	{
		return m_itemOutSEInst;
	}
	//read
	const std::shared_ptr<KdSoundEffect>& GetReadSE()const
	{
		return m_readSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetReadSEInst()const
	{
		return m_readSEInst;
	}
	//slash
	const std::shared_ptr<KdSoundEffect>& GetSlashSE()const
	{
		return m_slashSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetSlashSEInst()const
	{
		return m_slashSEInst;
	}
	//slashHit
	const std::shared_ptr<KdSoundEffect>& GetSlashHitSE()const
	{
		return m_slashHitSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetSlashHitSEInst()const
	{
		return m_slashHitSEInst;
	}
	//fire
	const std::shared_ptr<KdSoundEffect>& GetFireSE()const
	{
		return m_fireSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetFireSEInst()const
	{
		return m_fireSEInst;
	}
	//reload
	const std::shared_ptr<KdSoundEffect>& GetReloadSE()const
	{
		return m_reloadSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetReloadSEInst()const
	{
		return m_reloadSEInst;
	}
	//lock
	const std::shared_ptr<KdSoundEffect>& GetLockSE()const
	{
		return m_lockSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetLockSEInst()const
	{
		return m_lockSEInst;
	}
	//drink(E)
	const std::shared_ptr<KdSoundEffect>& GetDrinkSE()const
	{
		return m_drinkSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetDrinkSEInst()const
	{
		return m_drinkSEInst;
	}


	//Enemy===============================================

	//attention
	const std::shared_ptr<KdSoundEffect>& GetEnemyAwakeSE()const
	{
		return m_zombieAwakeSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetEnemyAwakeSEInst()const
	{
		return m_zombieAwakeSEInst;
	}
	//dead
	const std::shared_ptr<KdSoundEffect>& GetEnemyDeadSE()const
	{
		return m_zombieDeadSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetEnemyDeadSEInst()const
	{
		return m_zombieDeadSEInst;
	}
	//vomitAttack
	const std::shared_ptr<KdSoundEffect>& GetVomitAttackSE()const
	{
		return m_vomitAttackSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetVomitAttackSEInst()const
	{
		return m_vomitAttackSEInst;
	}
	//nova
	const std::shared_ptr<KdSoundEffect>& GetNovaSE()const
	{
		return m_novaSE;
	}
	const std::shared_ptr<KdSoundInstance>& GetNovaSEInst()const
	{
		return m_novaSEInst;
	}

	//titleBGM
	const std::shared_ptr<KdSoundInstance>& GetTitleBGMInst()const
	{
		return m_titleBgmInst;
	}
	//gameBGM
	const std::shared_ptr<KdSoundEffect>& GetBGM()const
	{
		return m_soundBgm;
	}
	const std::shared_ptr<KdSoundInstance>& GetBGMInst()const
	{
		return m_soundBgmInst;
	}
	//BossBGM
	const std::shared_ptr<KdSoundEffect>& GetBossBGM()const
	{
		return m_bossSoundBgm;
	}
	const std::shared_ptr<KdSoundInstance>& GetBossBgmInst()const
	{
		return m_bossSoundBgmInst;
	}

private:
	//サンウド関係
	//se用 
	//start
	std::shared_ptr<KdSoundEffect> m_startSE;
	std::shared_ptr<KdSoundInstance> m_startSEInst;
	//clear
	std::shared_ptr<KdSoundEffect> m_clearSE;
	std::shared_ptr<KdSoundInstance> m_clearSEInst;
	//playerHurt
	std::shared_ptr<KdSoundEffect> m_playerHurtSE;
	std::shared_ptr<KdSoundInstance> m_playerHurtSEInst;
	//playerDead
	std::shared_ptr<KdSoundEffect> m_playerDeadSE;
	std::shared_ptr<KdSoundInstance> m_playerDeadSEInst;
	//read
	std::shared_ptr<KdSoundEffect> m_readSE;
	std::shared_ptr<KdSoundInstance> m_readSEInst;
	// walk
	std::shared_ptr<KdSoundEffect> m_walkSE;
	std::shared_ptr<KdSoundInstance> m_walkSEInst;
	//itemGet
	std::shared_ptr<KdSoundEffect> m_getItemSE;
	std::shared_ptr<KdSoundInstance> m_getItemSEInst;
	//itemOut
	std::shared_ptr<KdSoundEffect> m_itemOutSE;
	std::shared_ptr<KdSoundInstance> m_itemOutSEInst;
	//slash
	std::shared_ptr<KdSoundEffect> m_slashSE;
	std::shared_ptr<KdSoundInstance> m_slashSEInst;
	//slashHitted
	std::shared_ptr<KdSoundEffect> m_slashHitSE;
	std::shared_ptr<KdSoundInstance> m_slashHitSEInst;
	//fire
	std::shared_ptr<KdSoundEffect> m_fireSE;
	std::shared_ptr<KdSoundInstance> m_fireSEInst;
	//reload
	std::shared_ptr<KdSoundEffect> m_reloadSE;
	std::shared_ptr<KdSoundInstance> m_reloadSEInst;
	//gunLock
	std::shared_ptr<KdSoundEffect> m_lockSE;
	std::shared_ptr<KdSoundInstance> m_lockSEInst;
	//drink
	std::shared_ptr<KdSoundEffect> m_drinkSE;
	std::shared_ptr<KdSoundInstance> m_drinkSEInst;
	//enemyAwakeSE
	std::shared_ptr<KdSoundEffect> m_zombieAwakeSE;
	std::shared_ptr<KdSoundInstance> m_zombieAwakeSEInst;
	//enemyDeadSE
	std::shared_ptr<KdSoundEffect> m_zombieDeadSE;
	std::shared_ptr<KdSoundInstance> m_zombieDeadSEInst;
	//vomitAttack and bossActionSE
	std::shared_ptr<KdSoundEffect> m_vomitAttackSE;
	std::shared_ptr<KdSoundInstance> m_vomitAttackSEInst;
	//novaSE
	std::shared_ptr<KdSoundEffect> m_novaSE;
	std::shared_ptr<KdSoundInstance> m_novaSEInst;
	//titlebgm
	std::shared_ptr<KdSoundEffect> m_titleBgm;
	std::shared_ptr<KdSoundInstance> m_titleBgmInst;
	//bgm
	std::shared_ptr<KdSoundEffect> m_soundBgm;
	std::shared_ptr<KdSoundInstance> m_soundBgmInst;
	//bossBgm
	std::shared_ptr<KdSoundEffect> m_bossSoundBgm;
	std::shared_ptr<KdSoundInstance> m_bossSoundBgmInst;
	//シェアードポインタ(スマートポインタ)

	float m_BGMPow;
};