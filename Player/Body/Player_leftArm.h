#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_leftArm :public ObjectBase
{
public:
	Player_leftArm(GameScene* _gameScene);
	void Update()override;

};