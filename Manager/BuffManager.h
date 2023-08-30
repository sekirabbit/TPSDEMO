#pragma once
#include"Headers.h"

class GameScene;

class BuffManager
{
public:
	BuffManager(GameScene* _gameScene);
	~BuffManager();

	void Update();

	void Add(BuffBase* _buff);

	std::vector<BuffBase*>& GetBuff()
	{
		return m_List;
	}
private:
	GameScene* m_gameScene;

	std::vector<BuffBase*> m_List;

};