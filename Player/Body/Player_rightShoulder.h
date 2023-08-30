#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_rightShoulder :public ObjectBase
{
public:
	Player_rightShoulder(GameScene* _gameScene);
	void Update()override;
	void AttackWait();
	const bool GetAnimeFlg()const
	{
		return m_animeFlg;
	}
	const float GetAnimeFrame()const
	{
		return m_animeFrame;
	}
	const float GetSlashWaitTime()const
	{
		return m_slashWaitTime;
	}

private:
	float m_slashWaitTime;
	float m_animeWaitTime;
};