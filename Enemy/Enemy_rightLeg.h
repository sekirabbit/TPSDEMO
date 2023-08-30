#pragma once

#include"ObjectBase.h"
class GameScene;

class Enemy_rightLeg :public ObjectBase
{
public:
	Enemy_rightLeg(GameScene* _gameScene, Enemy* _enemy);
	void Update()override;
	void Draw()override;

private:
	GameScene* m_gameScene;
	Enemy* m_enemy;
};