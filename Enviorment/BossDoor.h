#pragma once

#include"ObjectBase.h"
class GameScene;

class BossDoor :public ObjectBase
{
public:
	BossDoor(GameScene* _gameScene);
	void Update()override;

private:
	Math::Vector3 m_swampPos;
	Math::Vector3 m_appearPos;

	int m_waitTime;
};