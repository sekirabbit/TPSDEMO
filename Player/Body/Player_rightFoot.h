#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_rightFoot :public ObjectBase
{
public:
	Player_rightFoot(GameScene* _gameScene);
	void Update()override;
};