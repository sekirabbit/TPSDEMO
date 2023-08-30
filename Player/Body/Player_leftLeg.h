#pragma once

#include"ObjectBase.h"
class GameScene;

class Player_leftLeg :public ObjectBase
{
public:
	Player_leftLeg(GameScene* _gameScene);
	void Update()override;

};