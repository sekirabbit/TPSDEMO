#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_rightArm :public ObjectBase
{
public:
	Player_rightArm(GameScene* _gameScene);
	void Update()override;

};