#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_leftHand :public ObjectBase
{
public:
	Player_leftHand(GameScene* _gameScene);
	void Update()override;

};