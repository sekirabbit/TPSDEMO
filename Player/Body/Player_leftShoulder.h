#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_leftShoulder :public ObjectBase
{
public:
	Player_leftShoulder(GameScene* _gameScene);
	void Update()override;
	bool GetFireAnime()
	{
		return m_fireAnimeFlg;
	}
	bool GetLoadAnime()
	{
		return m_loadAnimeFlg;
	}
private:
	bool m_fireAnimeFlg;
	bool m_loadAnimeFlg; 
	
	int m_reloadTime;

};