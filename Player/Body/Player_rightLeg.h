#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_rightLeg :public ObjectBase
{
public:
	Player_rightLeg(GameScene* _gameScene);
	void Update()override;
};