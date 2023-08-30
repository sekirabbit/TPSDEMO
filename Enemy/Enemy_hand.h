#pragma once

#include"ObjectBase.h"
class GameScene;

class Enemy_hand :public ObjectBase
{
public:
	Enemy_hand(GameScene* _gameScene, Enemy* _enemy);
	void Update()override;
	void Draw()override;

private:
	GameScene* m_gameScene;
	Enemy* m_enemy;

};