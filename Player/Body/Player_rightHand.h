#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_rightHand :public ObjectBase
{
public:
	Player_rightHand(GameScene* _gameScene);
	void Update()override;
};